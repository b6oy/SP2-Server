#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "Message.h"
#include "TcpMessageHandler.h"

using namespace std;

class TcpServer
{
public:
	boost::signals2::signal<void (const TcpServer& source, const boost::system::error_code& error)> OnAcceptErrorOccurred;
	boost::signals2::signal<void (const TcpServer& source, TcpMessageHandler& socket)> OnAcceptSucceeded;
	boost::signals2::signal<void (const TcpServer& source, TcpMessageHandler& socket, const Message* message)> OnSocketMessageArrived;
    boost::signals2::signal<void (const TcpServer& source, const TcpMessageHandler& socket, const exception& ex)> OnSocketExceptionThrown;
	boost::signals2::signal<void (const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error)> OnSocketReceiveErrorOccurred;
	boost::signals2::signal<void (const TcpServer& source, const TcpMessageHandler& socket, const boost::system::error_code& error)> OnSocketSendErrorOccurred;
    TcpServer(boost::asio::io_service& ioService, unsigned short listenPort);
	const boost::asio::ip::tcp::acceptor& GetAcceptor() const;
	void StartListening();

private:
	void HandleAccept(boost::asio::ip::tcp::socket* socket, const boost::system::error_code& error);
    void HandleSocketMessageArrived(TcpMessageHandler& source, const Message* message) const;
	void HandleSocketExceptionThrown(const TcpMessageHandler& source, const exception& ex) const;
    void HandleSocketReceiveError(const TcpMessageHandler& source, const boost::system::error_code& error) const;
    void HandleSocketSendError(const TcpMessageHandler& source, const boost::system::error_code& error) const;
	void RaiseAcceptErrorOccurred(const boost::system::error_code& error) const;
	void RaiseAcceptSucceeded(TcpMessageHandler& socket) const;
	void RaiseSocketMessageArrived(TcpMessageHandler& socket, const Message* message) const;
	void RaiseSocketExceptionThrown(const TcpMessageHandler& socket, const exception& ex) const;
	void RaiseSocketReceiveErrorOccurred(const TcpMessageHandler& socket, const boost::system::error_code& error) const;
	void RaiseSocketSendErrorOccurred(const TcpMessageHandler& socket, const boost::system::error_code& error) const;
	void StartAccepting();

    boost::asio::io_service* ioService;
    boost::asio::ip::tcp::acceptor acceptor;

};

#endif // __TCPSERVER_H__
