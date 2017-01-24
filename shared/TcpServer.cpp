#include <boost/thread.hpp>

#include "TcpServer.h"

TcpServer::TcpServer(boost::asio::io_service& ioService, unsigned short listenPort)
	: acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), listenPort))
{
	this->ioService = &ioService;
}

const boost::asio::ip::tcp::acceptor& TcpServer::GetAcceptor() const
{
	return this->acceptor;
}

void TcpServer::StartListening()
{
    boost::thread acceptThread(&TcpServer::StartAccepting, this);
}

void TcpServer::StartAccepting()
{
	boost::asio::ip::tcp::socket* socket = new boost::asio::ip::tcp::socket(*this->ioService);
    this->acceptor.async_accept(*socket, boost::bind(&TcpServer::HandleAccept, this, socket, boost::asio::placeholders::error));
}

void TcpServer::HandleAccept(boost::asio::ip::tcp::socket* socket, const boost::system::error_code& error)
{
    if (error)
	{
		if (socket != 0)
			delete socket;
        RaiseAcceptErrorOccurred(error);
    }
	else
	{
		boost::shared_ptr<TcpMessageHandler> tcpHandler(new TcpMessageHandler(*socket));

		tcpHandler->OnMessageArrived.connect(boost::bind(&TcpServer::HandleSocketMessageArrived, this, _1, _2));
		tcpHandler->OnDataArrivalSystemErrorOccurred.connect(boost::bind(&TcpServer::HandleSocketReceiveError, this, _1, _2));
		tcpHandler->OnDataSendSystemErrorOccurred.connect(boost::bind(&TcpServer::HandleSocketSendError, this, _1, _2));
		tcpHandler->OnExceptionThrown.connect(boost::bind(&TcpServer::HandleSocketExceptionThrown, this, _1, _2));

		RaiseAcceptSucceeded(*tcpHandler);
		
		tcpHandler->StartReceiving();
	}
	StartAccepting();
}

void TcpServer::RaiseAcceptErrorOccurred(const boost::system::error_code& error) const
{
	this->OnAcceptErrorOccurred(*this, error);
}

void TcpServer::RaiseAcceptSucceeded(TcpMessageHandler& socket) const
{
	this->OnAcceptSucceeded(*this, socket);
}

void TcpServer::RaiseSocketMessageArrived(TcpMessageHandler& socket, const Message* message) const
{
	this->OnSocketMessageArrived(*this, socket, message);
}

void TcpServer::RaiseSocketExceptionThrown(const TcpMessageHandler& socket, const exception& ex) const
{
	this->OnSocketExceptionThrown(*this, socket, ex);
}

void TcpServer::RaiseSocketReceiveErrorOccurred(const TcpMessageHandler& socket, const boost::system::error_code& error) const
{
	this->OnSocketReceiveErrorOccurred(*this, socket, error);
}

void TcpServer::RaiseSocketSendErrorOccurred(const TcpMessageHandler& socket, const boost::system::error_code& error) const
{
	this->OnSocketSendErrorOccurred(*this, socket, error);
}

void TcpServer::HandleSocketMessageArrived(TcpMessageHandler& source, const Message* message) const
{
	RaiseSocketMessageArrived(source, message);
}

void TcpServer::HandleSocketExceptionThrown(const TcpMessageHandler& source, const exception& ex) const
{
	RaiseSocketExceptionThrown(source, ex);
}

void TcpServer::HandleSocketReceiveError(const TcpMessageHandler& source, const boost::system::error_code& error) const
{
	RaiseSocketReceiveErrorOccurred(source, error);
}

void TcpServer::HandleSocketSendError(const TcpMessageHandler& source, const boost::system::error_code& error) const
{
	RaiseSocketSendErrorOccurred(source, error);
}

