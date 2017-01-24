#ifndef __USER_H__
#define __USER_H__

#include <boost/asio.hpp>
#include "ServerEnum.h"
#include <TcpMessageHandler.h>

// Represents a connected user.
class User
{
public:
	User(TcpMessageHandler& tcpSocket);
	~User();
	TcpMessageHandler& GetTcpSocket() const;
	boost::asio::ip::udp::endpoint GetUdpEndpoint() const;
	void SetUdpEndpoint(boost::asio::ip::udp::endpoint udpEndpoint);
	int GetId() const;
    void SetId(int id);
    const char* GetName() const;
    void SetName(const char* name);
	void SetCharInfo(MyCharInfo Info);
	void GetCharInfo(MyCharInfo &Info);
	void SetUdpInfo(char IP[16],boost::asio::ip::udp::endpoint remoteEndpoint);
	MyCharInfo* GetInfo();
	void SetInRoomData(int room,int ready,int slot,int character,int master,int mode,int team, int turn);
	char* GetLocalIP();
	char* GetGlobalIP();
protected:

private:
	TcpMessageHandler* tcpSocket;
	boost::asio::ip::udp::endpoint udpEndpoint;
	char LocalIP[16];
	char GlobalIP[16];
	MyCharInfo Info;

};

#endif // __USER_H__
