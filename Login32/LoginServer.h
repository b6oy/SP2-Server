#ifndef __LOGINSERVER_H__
#define __LOGINSERVER_H__

#include <vector>

#include "SpServer.h"
#include "MySQL.h"
#include "User.h"

class LoginServer : public SpServer
{
public:
	LoginServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort);

protected:
	virtual void PrepareStart();
	virtual void InitializeMessageHandlerFunctions();
	virtual void HandleClientDisconnected(const TcpMessageHandler& socket);

private:
	void HandleLoginMessage(const Message* message, TcpMessageHandler& socket);
	void HandleServerInfoRequestMessage(const Message* message, TcpMessageHandler& socket);
	void HandleAfterServerInfoMessage(const Message* message, TcpMessageHandler& socket);
	void HandleGuildMarkRequestMessage(const Message* message, TcpMessageHandler& socket);
	void HandleDefaultCharacterChangeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleTrainingCompleteMessage(const Message* message, TcpMessageHandler& socket);
	void HandleReconnectRequestMessage(const Message* message, TcpMessageHandler& socket);
	
	int IsCorrectLogin(const char* userId, const char* password, const char* ip, const char* hwid);
	void GetCharInfo(int userUniqueNumber, MyCharInfo &Info);
	void SetDefaultCharacter(Character DefaultCharacter);
	std::vector<User*> users;

	boost::mutex loginLock;
};

#endif // __LOGINSERVER_H__
