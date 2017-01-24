#ifndef __USER_H__
#define __USER_H__

#include <boost/asio.hpp>

#include <TcpMessageHandler.h>

// Represents a connected user.
class User
{
public:
	User(TcpMessageHandler& tcpSocket);
	TcpMessageHandler& GetTcpSocket() const;
	boost::asio::ip::udp::endpoint GetUdpEndpoint() const;
	void SetUdpEndpoint(boost::asio::ip::udp::endpoint udpEndpoint);
	int GetId() const;
    void SetId(int id);
    const char* GetName() const;
    void SetName(const char* name);
protected:

private:
	TcpMessageHandler* tcpSocket;
	boost::asio::ip::udp::endpoint udpEndpoint;
	int id;
    char name[13];
};

#endif // __USER_H__
