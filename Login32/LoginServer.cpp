#include <MessageTypes.h>
#include "LoginServer.h"
#include "messages/tcp/client/LoginMessage.h"
#include "messages/tcp/server/LoginResponseMessage.h"
#include "messages/tcp/client/ServerInfoRequestMessage.h"
#include "messages/tcp/server/ServerInfoMessage.h"
#include "messages/tcp/client/DefaultCharacterChangeMessage.h"
#include "messages/tcp/server/DefaultCharacterChangeResponseMessage.h"
#include "messages/tcp/client/TrainingCompleteMessage.h"
#include "messages/tcp/server/TrainingCompleteResponseMessage.h"
#include "messages/tcp/client/ReconnectMessage.h"
#include "messages/tcp/client/GuildMarkMessage.h"
#include "messages/tcp/server/GuildMarkResponseMessage.h"
#include "messages/tcp/server/UnknownResponseMessage.h"

#include "ini.h"

extern CIni config;

using namespace std;

LoginServer::LoginServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort)
	: SpServer(ioService, tcpListenPort, udpListenPort)
{
}

void LoginServer::PrepareStart()
{

}

void LoginServer::InitializeMessageHandlerFunctions()
{
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_LOGIN, (TcpMessageHandlerFunction)&LoginServer::HandleLoginMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SERVER_INFO_REQUEST, (TcpMessageHandlerFunction)&LoginServer::HandleServerInfoRequestMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_AFTER_SERVERINFO_REQ, (TcpMessageHandlerFunction)&LoginServer::HandleAfterServerInfoMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_AFTER_SERVERINFO_REQ, (TcpMessageHandlerFunction)&LoginServer::HandleGuildMarkRequestMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_DEFAULT_CHARACTER_CHANGE, (TcpMessageHandlerFunction)&LoginServer::HandleDefaultCharacterChangeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_TRAINING_COMPLETE, (TcpMessageHandlerFunction)&LoginServer::HandleTrainingCompleteMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_RECONNECT, (TcpMessageHandlerFunction)&LoginServer::HandleReconnectRequestMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_GUILD_MARK, (TcpMessageHandlerFunction)&LoginServer::HandleReconnectRequestMessage);
}

void LoginServer::HandleClientDisconnected(const TcpMessageHandler& socket)
{
	User* user = reinterpret_cast<User*>(socket.GetTag());
	if (user != 0)
	{
		//std::remove(this->users.begin(), this->users.end(), user);
		loginLock.lock();
		for(int i = 0; i < users.size(); i++)
			if(user == users.at(i)){
				users.erase(this->users.begin()+i);
				delete user;
				break;
			}
		loginLock.unlock();
	}
}

void LoginServer::HandleLoginMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const LoginMessage* msg = static_cast<const LoginMessage*>(message);

		//Log::out() << "Client trying to login with username: " << msg->userId << endl;

		int userUniqueNumber = IsCorrectLogin(msg->userId, msg->password, socket.GetRemoteIp().to_string().c_str(), msg->passwordHash);

		if (userUniqueNumber == 0)
		{
			socket.Send(LoginResponseMessage(WrongPasswd));
			return;
		}

		if (socket.GetTag() == 0) // client has just connected, this is the first message received
		{
			User* user = new User(socket);
			loginLock.lock();
			user->SetId(userUniqueNumber);
			socket.SetTag(user);
			bool alreadyIn = false;
			/*for (int i = 0; i < users.size(); i++)
			{
				if (users[i]->GetId() == userUniqueNumber)
				{
					socket.Send(LoginResponseMessage(AlreadyIn));
					alreadyIn = true;
					break;
				}
			}*/
			if (!alreadyIn)
				this->users.push_back(user);
			loginLock.unlock();
		}
		MySQL MySql;
		if (!MySql.IsUserActive(msg->userId))
		{
			MyCharInfo UsrInfo;
			GetCharInfo(userUniqueNumber, UsrInfo);
			socket.Send(LoginResponseMessage(CorrectPasswd, UsrInfo.UserType, UsrInfo.DefaultCharacter,
				UsrInfo.Level, UsrInfo.Points, UsrInfo.Code));
		}
		else
		{
			socket.Send(LoginResponseMessage(AlreadyIn));
		}
	}
	catch (...)
	{
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleLoginMessage." << endl;
		loginLock.unlock();
	}
}

void LoginServer::HandleServerInfoRequestMessage(const Message* message, TcpMessageHandler& socket)
{
	const ServerInfoRequestMessage* msg = static_cast<const ServerInfoRequestMessage*>(message);
		if(msg->channel == 1){
		/*config.SetSection("CHANNEL1");
		socket.Send(ServerInfoMessage(1,0,config.ReadString("ip", "192.168.1.67"),config.ReadInteger("port", 9303),0,
			config.ReadString("name", "Test Server X1"),config.ReadString("guild", "CaptureGuild"),30));*/
		socket.Send(ServerInfoMessage(1,0,"37.187.165.112",9300,10,"Beginner"," ----",10));
	}else if(msg->channel == 2){
		/*config.SetSection("CHANNEL2");
		socket.Send(ServerInfoMessage(2,0,config.ReadString("ip", "192.168.1.67"),config.ReadInteger("port", 9303),0,
			config.ReadString("name", "Test Server X4"),config.ReadString("guild", "CaptureGuild"),30));*/
		socket.Send(ServerInfoMessage(2,0,"37.187.165.112", 9301,20,"Hero"," ----",20));
	}else if(msg->channel == 3){
		/*config.SetSection("CHANNEL3");
		socket.Send(ServerInfoMessage(3,0,config.ReadString("ip", "192.168.1.67"),config.ReadInteger("port", 9303),0,
			config.ReadString("name", "Test Server X10"),config.ReadString("guild", "CaptureGuild"),30));
		config.SetSection("CHANNEL4");
		socket.Send(ServerInfoMessage(3,1,config.ReadString("ip", "192.168.1.67"),config.ReadInteger("port", 9303),0,
			config.ReadString("name", "Test Server X10"),config.ReadString("guild", "CaptureGuild"),30));*/
		socket.Send(ServerInfoMessage(3,0,"37.187.165.112", 9302,30,"English Only"," ----",30));
		socket.Send(ServerInfoMessage(3,1,"37.187.165.112", 9303,30,"Hong Kong Only"," ----",30));
		socket.Send(ServerInfoMessage(3,2,"37.187.165.112", 9304,30,"English 1"," ----",30));
		socket.Send(ServerInfoMessage(3,3,"37.187.165.112", 9305,30,"Hong Kong 1"," ----",30));
		//socket.Send(ServerInfoMessage(3,1,"95.211.178.168",9340,30,"Debug"," Test",30));
	}
	socket.Send(UnknownResponseMessage());
}

void LoginServer::HandleAfterServerInfoMessage(const Message* message, TcpMessageHandler& socket)
{
		//config.SetSection("CHANNEL3");
		//socket.Send(ServerInfoMessage(3,0,config.ReadString("ip", "192.168.1.67"),config.ReadInteger("port", 9303),0,
			//config.ReadString("name", "Test Server X10"),config.ReadString("guild", " CaptureGuild"),30));
	//socket.Send(ServerInfoMessage(3,0,"37.187.165.112", 9302,30,"English Only"," ----",30));
}

void LoginServer::HandleGuildMarkRequestMessage(const Message* message, TcpMessageHandler& socket)
{
		const GuildMarkMessage* msg = static_cast<const GuildMarkMessage*>(message);
		socket.Send(GuildMarkResponseMessage(msg->guildname));
}


void LoginServer::HandleDefaultCharacterChangeMessage(const Message* message, TcpMessageHandler& socket)
{
	//cout << "Changing Character" << endl;
	const DefaultCharacterChangeMessage* msg = static_cast<const DefaultCharacterChangeMessage*>(message);
	User* user = reinterpret_cast<User*>(socket.GetTag());
	if (user != 0){
	MySQL MySql;
	MySql.SetDefaultCharacter(user->GetId(),(Character)msg->character);
	socket.Send(DefaultCharacterChangeResponseMessage(msg->character));
	}
}

void LoginServer::HandleTrainingCompleteMessage(const Message* message, TcpMessageHandler& socket)
{
	const int t_items[] = {11204, 11203, 11202, 11201, 11101, 11102, 11103, 11104, 11301, 2910};
	User* user = reinterpret_cast<User*>(socket.GetTag());
	if (user != 0){
		MyCharInfo UsrInfo;
		GetCharInfo(user->GetId(), UsrInfo);
	srand((unsigned int)time(0));
	int r = rand() % 4 + 1;
	if (UsrInfo.eleType != 0)
		r = UsrInfo.eleType;
	Item items[10];
	MySQL MySql;
	for (int i = 0; i < 9; i++)
	{
		int Type = t_items[i] + (r*10);
		items[i].SetItem(i,Type,100,1,0);
		MySql.InsertNewItem(user->GetId(),i,Type,100,0,0);
	}
	items[9].SetItem(9,t_items[9]+r,30,1,0);
	MySql.InsertNewItem(user->GetId(),9,t_items[9]+r,30,0,0);
	Level level;
	MySql.GetExp(user->GetId(),50,ElementTypes[r],10,level.getLevel(50));
	socket.Send(TrainingCompleteResponseMessage(items));
	}
}

void LoginServer::HandleReconnectRequestMessage(const Message* message, TcpMessageHandler& socket)
{
	const ReconnectMessage* msg = static_cast<const ReconnectMessage*>(message);

	if (socket.GetTag() == 0) // client has just connected, this is the first message received
	{
		//Log::out() << "Client reconnecting with username: " << msg->userId << endl;
		MySQL MySql;
		int id = MySql.Login(msg->userId, socket.GetRemoteIp().to_string().c_str());
		if(id)
		{
			loginLock.lock();
			User* user = new User(socket);
			user->SetId(id);
			socket.SetTag(user);
			this->users.push_back(user);
			loginLock.unlock();
			/*MyCharInfo UsrInfo;
			GetCharInfo(id, UsrInfo);
			socket.Send(LoginResponseMessage(CorrectPasswd, UsrInfo.UserType, UsrInfo.DefaultCharacter,
				UsrInfo.Level, UsrInfo.Points, UsrInfo.Code));*/
		}
		else {
			socket.Disconnect();
		}
	}
}


int LoginServer::IsCorrectLogin(const char* userId, const char* password, const char* ip, const char* hwid)
{
	MySQL MySql;
	return MySql.Login(userId, password, ip, hwid);
}

void LoginServer::GetCharInfo(int userUniqueNumber, MyCharInfo &Info)
{
	MySQL MySql;
	MySql.GetUserInfo(userUniqueNumber, Info);
}