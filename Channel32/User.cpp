#include <cstring>

#include "User.h"

User::User(TcpMessageHandler& tcpSocket)
	: tcpSocket(&tcpSocket)
{
	for(int i = 0; i < 16; i++)
		LocalIP[i] = GlobalIP[i] = 0;

	strcpy(GlobalIP,tcpSocket.GetRemoteIp().to_string().c_str());
}

User::~User()
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
    return this->Info.usr_id;
}

void User::SetId(int id)
{
    this->Info.usr_id = id;
}

const char* User::GetName() const
{
	return this->Info.usr_name;
}

void User::SetName(const char* name)
{
    strcpy(this->Info.usr_name, name);
}

void User::SetCharInfo(MyCharInfo Info)
{
	this->Info = Info;
}

void User::GetCharInfo(MyCharInfo &Info)
{
	Info = this->Info;
}

void User::SetUdpInfo(char IP[16],boost::asio::ip::udp::endpoint remoteEndpoint)
{
	strcpy(LocalIP,IP);
	this->udpEndpoint = remoteEndpoint;
}

MyCharInfo* User::GetInfo()
{
	return &Info;
}

void User::SetInRoomData(int room,int ready,int slot,int character,int master,int mode,int team, int turn)
{
	Info.usr_room = room;
	Info.usr_ready = ready;
	Info.usr_slot = slot;
	Info.usr_char = character+Info.premium;
	Info.rm_master = master;
	Info.usr_mode = mode;
	Info.usr_team = team;
	Info.usr_turn = turn;
}

char* User::GetLocalIP()
{
	return LocalIP;
}

char* User::GetGlobalIP()
{
	return GlobalIP;
}