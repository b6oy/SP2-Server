#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "TcpMessageHandler.h"
#include "MessageValidator.h"

TcpMessageHandler::TcpMessageHandler(boost::asio::ip::tcp::socket& socket)
    : socket(&socket), socketBuffer(0), isDisconnected(false), messageBufferSize(0),
      isFragmented(false), tag(0), sendState(-1), receiveState(-1)
{
	//std::cout << "DEBUG: Created TcpMessageHandler @" << hex << (unsigned int)this << "." << std::endl;
}

TcpMessageHandler::TcpMessageHandler()
    : socket(0), socketBuffer(0), isDisconnected(true), messageBufferSize(0),
      isFragmented(false), tag(0), sendState(-1), receiveState(-1)
{
	//std::cout << "DEBUG: Created TcpMessageHandler @" << hex << (unsigned int)this << "." << std::endl;
}

TcpMessageHandler::~TcpMessageHandler()
{
	//std::cout << "DEBUG: TcpMessageHandler @" << hex << (unsigned int)this << " destroyed. PASSED (2/2)" << std::endl;
    if (this->socket != 0)
	{
		if(socketLock.lock_flag_bit)
			socketLock.unlock();
		if(sendLock.lock_flag_bit)
			sendLock.unlock();
		delete this->socket;
		this->socket = 0;
	}
	if (this->socketBuffer != 0)
	{
        delete this->socketBuffer;
		this->socketBuffer = 0;
	}
	if (this->isFragmented)
	{
        //delete[] this->messageBuffer;
		this->socketBuffer = 0;
	}
}

void TcpMessageHandler::HandleReceivedData(char* data, int dataLength)
{
    bool wasFragmented = this->isFragmented;
    char* rawPacket = 0;
    try
    {
        if (this->isFragmented && this->messageBufferSize > 0)
        {
            char* newData = new char[dataLength + this->messageBufferSize];
            std::copy(this->messageBuffer, this->messageBuffer + this->messageBufferSize, newData);
            std::copy(data, data + dataLength, newData + this->messageBufferSize);
            //delete [] this->messageBuffer; //..Heap Error
			//this->messageBuffer = 0;
            data = newData;
            dataLength += this->messageBufferSize;
            this->isFragmented = false;
        }
        int i = 0;
        while (i < dataLength)
        {
            int length = reinterpret_cast<Message*>(data + i)->size;

			if (!MessageValidator::GetInstance().IsValidMessageSize(length))
                throw MessageValidationException(reinterpret_cast<Message*>(data + i), "The size field in the received packet was invalid.");

            if (i + length > dataLength)
            {
                //this->messageBuffer = new char[dataLength - i];
                this->messageBufferSize = dataLength - i;
                std::copy(data, data + this->messageBufferSize, this->messageBuffer);
                this->isFragmented = true;
                if (wasFragmented)
                    delete data;
                return;
            }

            rawPacket = new char[length];
            
            std::copy(data + i, data + i + length, rawPacket);

			try
			{
				MessageValidator::GetInstance().DecryptMessage(reinterpret_cast<Message*>(rawPacket));
			}
			catch (MessageValidationException& ex)
			{
                delete rawPacket;
				rawPacket = 0;
                if (wasFragmented)
                    delete data;
                throw ex;
            }
            if (this->receiveState >= 0)
            {
                this->UpdateReceiveState();
				//Test later so security issue.
				int rcvState = reinterpret_cast<Message*>(rawPacket)->state;
                if (rcvState != this->receiveState && rcvState != -1)
                {
					this->receiveState = reinterpret_cast<Message*>(rawPacket)->state;
                    /*delete rawPacket;
					rawPacket = 0;
                    if (wasFragmented)
                        delete data;
                    throw std::runtime_error(string("Unexpected packet state."));*/
                }else if(rcvState == -1)
				{
					this->receiveState = -1;
				}
            }
            else
			{
                this->sendLock.lock();
                if (this->sendState >= 0)
                {
                    this->receiveState = reinterpret_cast<Message*>(rawPacket)->state;
                    this->UpdateReceiveState(this->receiveState);
                }
                else
                {
                    srand((unsigned int)time(0));
                    this->receiveState = 1000;//rand() % (RAND_MAX - 1) + 1;
                    this->sendState = this->receiveState;
                }
                this->sendLock.unlock();
			}
			socketLock.lock();
            if (this->isDisconnected){
				socketLock.unlock();
                return;
			}
            // Do not start this in a new thread.
            RaiseMessageArrived(reinterpret_cast<Message*>(rawPacket));
			socketLock.unlock();
            i += length;
        }
    }
    //ideally, this will only catch "low level" message validation errors,
	//which are thrown before raising the OnMessageArrived event.
	//all other exceptions should be handled by the server without arriving here.
    catch (exception& ex)
    {
        //if (wasFragmented)
            //delete data; //Crash
        if (rawPacket != 0)
            delete rawPacket;

        this->RaiseExceptionThrown(ex);
    }
}

void TcpMessageHandler::Send(Message& message)
{
	if (this->isDisconnected)
		return;
	if (message.size > 8192)
		return;
    //char* messageCopy = new char[message.size];
	char messageCopy[8192];
    std::copy(reinterpret_cast<char*>(&message), reinterpret_cast<char*>(&message) + message.size, messageCopy);
	__try {
    //this->sendLock.lock();
    reinterpret_cast<Message*>(messageCopy)->state = this->sendState;
    this->UpdateSendState();
    Message *msg = reinterpret_cast<Message*>(messageCopy);
    MessageValidator::GetInstance().EncryptMessage(msg);
	//Message *msg = reinterpret_cast<Message*>(messageCopy);
	SendToSocket(*msg);
	//this->sendLock.unlock();
	}__except(true){
		//if(this->sendLock.lock_flag_bit)
			//this->sendLock.unlock();
	}
    //delete messageCopy;
}

void TcpMessageHandler::SetTag(void* tag)
{
    this->tag = tag;
}

void* TcpMessageHandler::GetTag() const
{
	try {
		return this->tag;
	}
	catch (...) {
	
	}
	return 0;
}

void TcpMessageHandler::UpdateReceiveState()
{
    this->UpdateReceiveState(this->receiveState);
}

void TcpMessageHandler::UpdateReceiveState(int previousState)
{
    this->receiveState = this->ComputeNextState(previousState);
}

void TcpMessageHandler::UpdateSendState()
{
    this->UpdateSendState(this->sendState);
}

void TcpMessageHandler::UpdateSendState(int previousState)
{
    this->sendState = this->ComputeNextState(previousState);
}

int TcpMessageHandler::ComputeNextState(int previousState)
{
    return abs(((previousState = (~previousState + 0x14fb) * 0x1f) >> 16) ^ previousState);
}

void TcpMessageHandler::RaiseMessageArrived(const Message* message)
{
    if (!this->isDisconnected)
    {
        this->OnMessageArrived(*this, message);
    }
}

void TcpMessageHandler::RaiseExceptionThrown(const exception& ex)
{
    if (!this->isDisconnected)
    {
        this->isDisconnected = true;
        this->OnExceptionThrown(*this, ex);
    }
}

void TcpMessageHandler::RaiseDataArrivalSystemErrorOccurred(const boost::system::error_code& error)
{
    if (!this->isDisconnected)
    {
        this->isDisconnected = true;
        this->OnDataArrivalSystemErrorOccurred(*this, error);
    }
}

void TcpMessageHandler::RaiseDataSendSystemErrorOccurred(const boost::system::error_code& error)
{
    if (!this->isDisconnected)
    {
        this->isDisconnected = true;
        this->OnDataSendSystemErrorOccurred(*this, error);
    }
}

const boost::asio::ip::address TcpMessageHandler::GetRemoteIp() const
{
    return this->GetRemoteEndpoint().address();
}

unsigned short TcpMessageHandler::GetRemotePort() const
{
    return this->GetRemoteEndpoint().port();
}

const boost::asio::ip::tcp::endpoint TcpMessageHandler::GetRemoteEndpoint() const
{
	return this->socket->remote_endpoint();
}

void TcpMessageHandler::Connect(boost::asio::io_service& ioService, const string& remoteIp, unsigned short remotePort)
{
    this->socket = new boost::asio::ip::tcp::socket(ioService);
    boost::system::error_code error = boost::asio::error::host_not_found;

    this->socket->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(remoteIp, error), remotePort));
    
    if (error)
    {
        throw boost::system::system_error(error);
		return;
    }

    this->isDisconnected = false;

    if (this->socketBuffer != 0)
        delete this->socketBuffer;

    this->socketBuffer = new char[MessageValidator::MAX_BUFFER_SIZE];

    this->socket->async_read_some(boost::asio::buffer(this->socketBuffer, MessageValidator::MAX_BUFFER_SIZE), boost::bind(&TcpMessageHandler::HandleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpMessageHandler::HandleRead(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    if (this->isDisconnected)
        return;

    if (error)
    {
        RaiseDataArrivalSystemErrorOccurred(error);
		this->socket->close();
        return;
    }
    HandleReceivedData(this->socketBuffer, bytesTransferred);
	socketLock.lock();
    if (!this->isDisconnected)
        this->socket->async_read_some(boost::asio::buffer(this->socketBuffer, MessageValidator::MAX_BUFFER_SIZE), boost::bind(&TcpMessageHandler::HandleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	socketLock.unlock();
}

void TcpMessageHandler::SendToSocket(const Message& message)
{
	    if (this->isDisconnected)
        return;
		this->socket->async_send(boost::asio::buffer(&message, message.size), boost::bind(&TcpMessageHandler::HandleSend, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpMessageHandler::HandleSend(const boost::system::error_code& error, std::size_t bytesTransferred)
{
    if (error)
    {
        RaiseDataSendSystemErrorOccurred(error);
        return;
    }
}

void TcpMessageHandler::Disconnect()
{
	//socketLock.lock();
    this->isDisconnected = true;
    this->socket->close();
	//this->socket = 0;
	//socketLock.unlock();
}

void TcpMessageHandler::StartReceiving()
{
	socketLock.lock();
    if (!this->isDisconnected)
    {
		try {
        if (this->socketBuffer != 0)
            delete this->socketBuffer;

        this->socketBuffer = new char[MessageValidator::MAX_BUFFER_SIZE];
		}catch(...){
		if (this->socketBuffer != 0)
            delete this->socketBuffer;
		this->socketBuffer = new char[MessageValidator::MAX_BUFFER_SIZE];
		}

        this->socket->async_read_some(boost::asio::buffer(this->socketBuffer, MessageValidator::MAX_BUFFER_SIZE), boost::bind(&TcpMessageHandler::HandleRead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
	socketLock.unlock();
}
