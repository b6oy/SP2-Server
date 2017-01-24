#include "SpServer.h"

#define CALL_MEMBER_FN(objectPointer, functionPointer) ((objectPointer)->*(functionPointer))

SpServer::SpServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort)
	: ioService(&ioService),
	  tcpListenPort(tcpListenPort), tcpServer(ioService, tcpListenPort),
	  udpListenPort(udpListenPort), udpServer(ioService, udpListenPort)
{
	tcpServer.OnAcceptSucceeded.connect(boost::bind(&SpServer::HandleTcpAcceptSucceeded, this, _1, _2));
	tcpServer.OnAcceptErrorOccurred.connect(boost::bind(&SpServer::HandleTcpAcceptErrorOccurred, this, _1, _2));
	tcpServer.OnSocketMessageArrived.connect(boost::bind(&SpServer::HandleClientTcpMessageArrived, this, _1, _2, _3));
	tcpServer.OnSocketExceptionThrown.connect(boost::bind(&SpServer::HandleClientTcpException, this, _1, _2, _3));
	tcpServer.OnSocketReceiveErrorOccurred.connect(boost::bind(&SpServer::HandleClientTcpReceiveError, this, _1, _2, _3));
	tcpServer.OnSocketSendErrorOccurred.connect(boost::bind(&SpServer::HandleClientTcpSendError, this, _1, _2, _3));

	udpServer.OnMessageArrived.connect(boost::bind(&SpServer::HandleClientUdpMessageArrived, this, _1, _2, _3));
	udpServer.OnExceptionThrown.connect(boost::bind(&SpServer::HandleClientUdpException, this, _1, _2));
	udpServer.OnReceiveErrorOccurred.connect(boost::bind(&SpServer::HandleClientUdpReceiveError, this, _1, _2));
	udpServer.OnSendErrorOccurred.connect(boost::bind(&SpServer::HandleClientUdpSendError, this, _1, _2));
}

void SpServer::Start()
{
	this->PrepareStart();
	this->InitializeMessageHandlerFunctions();
	this->StartUdpServer();
	this->StartTcpServer();
}

void SpServer::PrepareStart()
{
	//this is for SQL and other stuff that needs to be initialized
}

void SpServer::StartTcpServer()
{
	tcpServer.StartListening();
	Log::out(LOG_TYPE_IMPORTANT) << "TCP server started." << endl;
}

void SpServer::StartUdpServer()
{
	udpServer.StartListening();
	Log::out(LOG_TYPE_IMPORTANT) << "UDP server started." << endl;
}

void SpServer::HandleClientTcpMessageArrived(const TcpServer& source, TcpMessageHandler& socket, const Message* message)
{
	map<MessageTypeRange, TcpMessageHandlerFunction>::iterator it = this->clientTcpMessageHandlerFunctions.find((MessageType)message->type);

	if (it == this->clientTcpMessageHandlerFunctions.end())
	{
		//Log::out(LOG_TYPE_IMPORTANT) << "No TCP message handler function for message type = 0x" << hex << (unsigned int)message->type << " (received from " << socket.GetRemoteIp().to_string() << ")." << endl;
		return;
	}

	CALL_MEMBER_FN(this, (*it).second)(message, socket);
}

void SpServer::HandleClientUdpMessageArrived(const UdpServer& source, const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	map<MessageTypeRange, UdpMessageHandlerFunction>::iterator it = this->clientUdpMessageHandlerFunctions.find((MessageType)message->type);

	if (it == this->clientUdpMessageHandlerFunctions.end())
	{
		//Log::out(LOG_TYPE_WARNING) << "No UDP message handler function for message type = 0x" << hex << (unsigned int)message->type << " (received from " << remoteEndpoint.address().to_string() << ")." << endl;
		return;
	}

	CALL_MEMBER_FN(this, (*it).second)(message, remoteEndpoint);
}

void SpServer::HandleClientTcpException(const TcpServer& source, const TcpMessageHandler& socket, const exception& ex)
{
	//Log::out(LOG_TYPE_WARNING) << "Client disconnected: An exception was thrown (" << ex.what() << ") ( " << socket.GetRemoteIp().to_string() << ")." << endl;
	this->HandleClientDisconnected(socket);
}

void SpServer::HandleClientTcpReceiveError(const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error)
{
	if (error.value() == 2) // this is 'end of file', which is received when the connection is reset by the remote peer
	{
		//Log::out() << "Client disconnected: Connection reset by remote peer (" << socket.GetRemoteIp().to_string() << ")." << endl;
	}
	else
	{
		//Log::out(LOG_TYPE_WARNING) << "Client disconnected: Error on TCP receive (" << boost::system::system_error(error).what() << ") ( " << socket.GetRemoteIp().to_string() << ")." << endl;
	}
	this->HandleClientDisconnected(socket);
}

void SpServer::HandleClientTcpSendError(const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error)
{
	//Log::out(LOG_TYPE_WARNING) << "Client disconnected: Error on TCP send (" << boost::system::system_error(error).what() << ") ( " << socket.GetRemoteIp().to_string() << ")." << endl;
	this->HandleClientDisconnected(socket);
}

void SpServer::HandleTcpAcceptSucceeded(const TcpServer& source, const TcpMessageHandler& socket)
{
	//Log::out() << "Connection request from " << socket.GetRemoteIp().to_string() << "." << endl;
}

void SpServer::HandleTcpAcceptErrorOccurred(const TcpServer& source, const boost::system::error_code& error)
{
	Log::out(LOG_TYPE_WARNING) << "Error on TCP accept (" << boost::system::system_error(error).what() << ")." << endl;
	ExitProcess(0);
}

void SpServer::HandleClientUdpException(const UdpServer& source, const exception& ex)
{
	//Log::out() << "An exception was thrown in the UDP server (" << ex.what() << ")." << endl;
}

void SpServer::HandleClientUdpReceiveError(const UdpServer& source, const boost::system::error_code& error)
{
	//Log::out(LOG_TYPE_WARNING) << "Error on UDP receive (" << boost::system::system_error(error).what() << ")." << endl;
}

void SpServer::HandleClientUdpSendError(const UdpServer& source, const boost::system::error_code& error)
{
	//Log::out(LOG_TYPE_WARNING) << "Error on UDP send (" << boost::system::system_error(error).what() << ")." << endl;
}

void SpServer::HandleClientDisconnected(const TcpMessageHandler& socket)
{
	// some cleanups, notifify other players, etc
}

void SpServer::SetTcpMessageHandlerFunction(MessageType messageType, TcpMessageHandlerFunction function)
{
	clientTcpMessageHandlerFunctions[MessageTypeRange(messageType)] = function;
}

void SpServer::SetTcpMessageHandlerFunction(MessageType first, MessageType last, TcpMessageHandlerFunction function)
{
    clientTcpMessageHandlerFunctions[MessageTypeRange(first, last)] = function;
}

void SpServer::SetUdpMessageHandlerFunction(MessageType messageType, UdpMessageHandlerFunction function)
{
	clientUdpMessageHandlerFunctions[messageType] = function;
}

void SpServer::SetUdpMessageHandlerFunction(MessageType first, MessageType last, UdpMessageHandlerFunction function)
{
    clientUdpMessageHandlerFunctions[MessageTypeRange(first, last)] = function;
}

UdpServer* SpServer::GetUdp()
{
	return &udpServer;
}

MessageTypeRange::MessageTypeRange(MessageType messageType)
{
    this->first = this->last = messageType;
}

MessageTypeRange::MessageTypeRange(MessageType first, MessageType last)
{
    this->first = first;
    this->last = last;
}

bool MessageTypeRange::Contains(MessageType messageType) const
{
    return (int)this->first <= messageType && messageType <= (int)this->last;
}

bool MessageTypeRange::operator==(const MessageTypeRange& other) const
{
    return (this->Contains(other.first) && this->Contains(other.last)) ||
           (other.Contains(this->first) && other.Contains(this->last));
}

bool MessageTypeRange::operator<(const MessageTypeRange& other) const
{
    return !(*this == other) && this->first < other.first;
}

