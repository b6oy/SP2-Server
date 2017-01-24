#ifndef __SPSERVER_H__
#define __SPSERVER_H__

#include "TcpServer.h"
#include "UdpServer.h"
#include "Message.h"
#include "MessageTypes.h"
#include "Log.h"

class MessageTypeRange
{
public:
    MessageTypeRange(MessageType messageType);
    MessageTypeRange(MessageType first, MessageType last);
    bool Contains(MessageType messageType) const;
    bool operator==(const MessageTypeRange& other) const; // support for std::find
    bool operator<(const MessageTypeRange& other) const; // support for std::find

private:
    MessageType first;
    MessageType last;
};


class SpServer
{
public:
	void Start();

protected:
	typedef void (SpServer::* TcpMessageHandlerFunction)(const Message* message, TcpMessageHandler& socket);
	typedef void (SpServer::* UdpMessageHandlerFunction)(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint);
    SpServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort);
	virtual void PrepareStart();
	virtual void InitializeMessageHandlerFunctions() = 0;
	virtual void HandleClientDisconnected(const TcpMessageHandler& socket);
	void SetTcpMessageHandlerFunction(MessageType messageType, TcpMessageHandlerFunction function);
    void SetTcpMessageHandlerFunction(MessageType first, MessageType last, TcpMessageHandlerFunction function);
	void SetUdpMessageHandlerFunction(MessageType messageType, UdpMessageHandlerFunction function);
    void SetUdpMessageHandlerFunction(MessageType first, MessageType last, UdpMessageHandlerFunction function);
	UdpServer* GetUdp();
private:
    void HandleClientTcpMessageArrived(const TcpServer& source, TcpMessageHandler& socket, const Message* message);
    void HandleClientTcpException(const TcpServer& source, const TcpMessageHandler& socket, const exception& ex);
    void HandleClientTcpReceiveError(const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error);
    void HandleClientTcpSendError(const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error);
    void HandleTcpAcceptSucceeded(const TcpServer& source, const TcpMessageHandler& socket);
    void HandleTcpAcceptErrorOccurred(const TcpServer& source, const boost::system::error_code& error);
	void HandleClientUdpMessageArrived(const UdpServer& source, const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint);
    void HandleClientUdpException(const UdpServer& source, const exception& ex);
    void HandleClientUdpReceiveError(const UdpServer& source, const boost::system::error_code& error);
    void HandleClientUdpSendError(const UdpServer& source, const boost::system::error_code& error);
	void StartTcpServer();
	void StartUdpServer();

    boost::asio::io_service* ioService;
	TcpServer tcpServer;
	UdpServer udpServer;
	map<MessageTypeRange, TcpMessageHandlerFunction> clientTcpMessageHandlerFunctions;
	map<MessageTypeRange, UdpMessageHandlerFunction> clientUdpMessageHandlerFunctions;
	unsigned short tcpListenPort;
	unsigned short udpListenPort;
};

#endif // __SPSERVER_H__
