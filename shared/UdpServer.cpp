#include <boost/thread.hpp>

#include "UdpServer.h"
#include "MessageValidator.h"

UdpServer::UdpServer(boost::asio::io_service& ioService, unsigned short listenPort)
	: socket(ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), listenPort)), socketBuffer(0), sendState(-1)
{
	this->ioService = &ioService;
}

const boost::asio::ip::udp::socket& UdpServer::GetSocket() const
{
	return this->socket;
}

void UdpServer::StartListening()
{
	if (this->socketBuffer != 0)
		delete this->socketBuffer;
	this->socketBuffer = new char[MessageValidator::MAX_BUFFER_SIZE];
    boost::thread receiveThread(&UdpServer::StartReceiveFrom, this);
}

void UdpServer::StartReceiveFrom()
{
	this->socket.async_receive_from(boost::asio::buffer(this->socketBuffer, MessageValidator::MAX_BUFFER_SIZE), this->remoteEndpoint, boost::bind(&UdpServer::HandleReceiveFrom, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UdpServer::HandleReceiveFrom(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    if (error)
    {
        RaiseReceiveSystemErrorOccurred(error);
		// TODO: I'm not sure when this can happen
		// Since the function doesn't return here, it might lead to an infinite loop in specific cases:
		// StartReceiveFrom -> error -> HandleReceiveFrom -> StartReceiveFrom -> error -> ...
    }

	char* data = this->socketBuffer;
	int dataLength = bytesTransferred;

    try
    {
        int length = reinterpret_cast<Message*>(data)->size;

		if (!MessageValidator::GetInstance().IsValidMessageSize(length))
            throw MessageValidationException(reinterpret_cast<Message*>(data), "The size field in the received packet was invalid.");

        if (length > dataLength)
            throw MessageValidationException(reinterpret_cast<Message*>(data), "The size field in the received packet was higher than the size of the packet itself.");

        char* rawPacket = data;

		try
		{
			MessageValidator::GetInstance().DecryptMessage(reinterpret_cast<Message*>(rawPacket));
		}
		catch (MessageValidationException& ex)
		{
            throw ex;
        }

        // Do not start this in a new thread.
        RaiseMessageArrived(reinterpret_cast<Message*>(rawPacket), this->remoteEndpoint);
    }
    //ideally, this will only catch "low level" message validation errors,
	//which are thrown before raising the OnMessageArrived event.
	//all other exceptions should be handled by the server without arriving here.
    catch (exception& ex)
    {
        this->RaiseExceptionThrown(ex);
    }

    this->StartReceiveFrom();
}

void UdpServer::SendTo(Message& message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	if (message.size > 4096)
		return;
	char messageCopy[4096];
    //char* messageCopy = new char[message.size];
    std::copy(reinterpret_cast<char*>(&message), reinterpret_cast<char*>(&message) + message.size, messageCopy);

    reinterpret_cast<Message*>(messageCopy)->state = this->sendState;
    this->UpdateSendState();

    MessageValidator::GetInstance().EncryptMessage(reinterpret_cast<Message*>(messageCopy));

    this->socket.async_send_to(boost::asio::buffer(messageCopy, message.size), remoteEndpoint, boost::bind(&UdpServer::HandleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    //delete[] messageCopy;
}

void UdpServer::ForwardTo(Message& message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	if (message.size > 4096)
		return;
	char messageCopy[4096];
    //char* messageCopy = new char[message.size];
    std::copy(reinterpret_cast<char*>(&message), reinterpret_cast<char*>(&message) + message.size, messageCopy);

    MessageValidator::GetInstance().EncryptMessage(reinterpret_cast<Message*>(messageCopy));

    this->socket.async_send_to(boost::asio::buffer(messageCopy, message.size), remoteEndpoint, boost::bind(&UdpServer::HandleSendTo, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    //delete[] messageCopy;
}

void UdpServer::UpdateSendState()
{
    this->UpdateSendState(this->sendState);
}

void UdpServer::UpdateSendState(int previousState)
{
    this->sendState = this->ComputeNextState(previousState);
}

int UdpServer::ComputeNextState(int previousState)
{
    return abs(((previousState = (~previousState + 0x14fb) * 0x1f) >> 16) ^ previousState);
}

void UdpServer::HandleSendTo(const boost::system::error_code& error, std::size_t bytesTransferred)
{
	if (error)
    {
        RaiseSendSystemErrorOccurred(error);
        return;
    }
}

void UdpServer::RaiseMessageArrived(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint) const
{
	this->OnMessageArrived(*this, message, remoteEndpoint);
}

void UdpServer::RaiseExceptionThrown(const exception& ex) const
{
	this->OnExceptionThrown(*this, ex);
}

void UdpServer::RaiseReceiveSystemErrorOccurred(const boost::system::error_code& error) const
{
	this->OnReceiveErrorOccurred(*this, error);
}

void UdpServer::RaiseSendSystemErrorOccurred(const boost::system::error_code& error) const
{
	this->OnSendErrorOccurred(*this, error);
}
