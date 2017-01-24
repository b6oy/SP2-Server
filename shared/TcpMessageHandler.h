#ifndef __TCPMESSAGEHANDLER_H__
#define __TCPMESSAGEHANDLER_H__

#include <boost/signals2.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>

#include "Message.h"

using namespace std;

class TcpMessageHandler : public boost::enable_shared_from_this<TcpMessageHandler>
{
public:
	boost::signals2::signal<void (TcpMessageHandler& source, const Message* message)> OnMessageArrived;
	boost::signals2::signal<void (const TcpMessageHandler& source, const exception& ex)> OnExceptionThrown;
	boost::signals2::signal<void (const TcpMessageHandler& source, const boost::system::error_code& error)> OnDataArrivalSystemErrorOccurred;
	boost::signals2::signal<void (const TcpMessageHandler& source, const boost::system::error_code& error)> OnDataSendSystemErrorOccurred;
    TcpMessageHandler();
    TcpMessageHandler(boost::asio::ip::tcp::socket& socket);
    ~TcpMessageHandler();
    const boost::asio::ip::address GetRemoteIp() const;
    unsigned short GetRemotePort() const;
	const boost::asio::ip::tcp::endpoint GetRemoteEndpoint() const;
    void Connect(boost::asio::io_service& ioService, const string& remoteIp, unsigned short remotePort);
    void Disconnect();
    void StartReceiving();
	void* GetTag() const;
    void SetTag(void* tag);
    void Send(Message& message);
	bool isDisconnected;

protected:
    void SendToSocket(const Message& packet);

private:
    void HandleRead(const boost::system::error_code& error, std::size_t bytesTransferred);
    void HandleSend(const boost::system::error_code& error, std::size_t bytesTransferred);
	void HandleReceivedData(char* data, int length);
	void UpdateReceiveState();
    void UpdateReceiveState(int previousState);
    void UpdateSendState();
    void UpdateSendState(int previousState);
    static int ComputeNextState(int previousState);
	void RaiseMessageArrived(const Message* message);
	void RaiseExceptionThrown(const exception& ex);
	void RaiseDataArrivalSystemErrorOccurred(const boost::system::error_code& error);
	void RaiseDataSendSystemErrorOccurred(const boost::system::error_code& error);

	boost::asio::ip::tcp::socket* socket;
	int sendState;
    int receiveState;
	char* socketBuffer;
    //char* messageBuffer;
	char messageBuffer[8192];
    int messageBufferSize;
    bool isFragmented;
    void* tag;
    boost::mutex sendLock;
	boost::mutex socketLock;
	int times[30];
	int t_count;

};

#endif // __TCPMESSAGEHANDLER_H__
