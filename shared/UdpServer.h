#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "Message.h"
#include "TcpMessageHandler.h"

using namespace std;

class UdpServer
{
public:
	boost::signals2::signal<void (const UdpServer& source, const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint)> OnMessageArrived;
    boost::signals2::signal<void (const UdpServer& source, const exception& ex)> OnExceptionThrown;
	boost::signals2::signal<void (const UdpServer& source, const boost::system::error_code& error)> OnReceiveErrorOccurred;
	boost::signals2::signal<void (const UdpServer& source, const boost::system::error_code& error)> OnSendErrorOccurred;
    UdpServer(boost::asio::io_service& ioService, unsigned short listenPort);
	const boost::asio::ip::udp::socket& GetSocket() const;
	void StartListening();
	void SendTo(Message& message, boost::asio::ip::udp::endpoint remoteEndpoint);
    void ForwardTo(Message& message, boost::asio::ip::udp::endpoint remoteEndpoint);

private:
	void HandleReceiveFrom(const boost::system::error_code& error, std::size_t bytesTransferred);
    void HandleSendTo(const boost::system::error_code& error, std::size_t bytesTransferred);
    void HandleReceiveError(const boost::system::error_code& error) const;
    void HandleSendError(const boost::system::error_code& error) const;
	void RaiseMessageArrived(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint) const;
	void RaiseExceptionThrown(const exception& ex) const;
	void RaiseReceiveSystemErrorOccurred(const boost::system::error_code& error) const;
	void RaiseSendSystemErrorOccurred(const boost::system::error_code& error) const;
	void StartReceiveFrom();
    void UpdateSendState();
    void UpdateSendState(int previousState);
    static int ComputeNextState(int previousState);

    boost::asio::io_service* ioService;
    boost::asio::ip::udp::socket socket;
	boost::asio::ip::udp::endpoint remoteEndpoint;
	char* socketBuffer;
    int sendState;
};

#endif // __UDPSERVER_H__
