#include <cstring>

#include "User.h"

User::User(TcpMessageHandler& tcpSocket)
	: tcpSocket(&tcpSocket)
{
}

TcpMessageHandler& User::GetTcpSocket() const
{
	return *this->tcpSocket;
}

boost::asio::ip::udp::endpoint User::GetUdpEndpoint() const
{
	return this->udpEndpoint;
}

void User::SetUdpEndpoint(boost::asio::ip::udp::endpoint udpEndpoint)
{
	this->udpEndpoint = udpEndpoint;
}

int User::GetId() const
{
    return this->id;
}

void User::SetId(int id)
{
    this->id = id;
}

const char* User::GetName() const
{
    return this->name;
}

void User::SetName(const char* name)
{
    strcpy(this->name, name);
}
