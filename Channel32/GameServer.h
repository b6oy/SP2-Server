#ifndef __GAMESERVER_H__
#define __GAMESERVER_H__
#define MAX_ROOMS 300
#include <vector>

#include <SpServer.h>
#include "MySQL.h"
#include "User.h"
#include "Room.h"

class GameServer : public SpServer
{
public:
	GameServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort, int type);
	int GetLastActivity();
	int GetTotalPlayers();
	void UpdateActiveUsers();
protected:
	virtual void PrepareStart();
	virtual void InitializeMessageHandlerFunctions();
	virtual void HandleClientDisconnected(const TcpMessageHandler& socket);

private:
	void BroadcastMessage(const Message* message, TcpMessageHandler* socket, bool Lobby);
	User* GetUserInstance(char name[13]);
	void UdpForwardMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint);
	void UdpHandShakeMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint);
	void UdpKeepAliveMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint);
	void HandleLoginMessage(const Message* message, TcpMessageHandler& socket);
	void HandleChatMessage(const Message* message, TcpMessageHandler& socket);
	void HandleShopJoinMessage(const Message* message, TcpMessageHandler& socket);
	void HandleShopBuyMessage(const Message* message, TcpMessageHandler& socket);
	void HandleShopSellMessage(const Message* message, TcpMessageHandler& socket);
	void HandleElementBuyMessage(const Message* message, TcpMessageHandler& socket);
	void HandleForceChargeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleEquipChangeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleUserInfoMessage(const Message* message, TcpMessageHandler& socket);
	void HandleItemUpgradeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleAddFriendMessage(const Message* message, TcpMessageHandler& socket);
	void HandleFriendListMessage(const Message* message, TcpMessageHandler& socket);
	void HandleConfirmIDMessage(const Message* message, TcpMessageHandler& socket);
	void HandleFindUserMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomExitMessage(const Message* message, TcpMessageHandler& socket);
	void HandleUserKickMessage(const Message* message, TcpMessageHandler& socket);
	void HandleTradeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleUserShopOpenMessage(const Message* message, TcpMessageHandler& socket);
	void HandleSearchShopBuyMessage(const Message* message, TcpMessageHandler& socket);
	void HandleUseScrollMessage(const Message* message, TcpMessageHandler& socket);
	void HandleScrollBuyOrSellMessage(const Message* message, TcpMessageHandler& socket);
	void HandlePickScrollMessage(const Message* message, TcpMessageHandler& socket);
	void HandleCardSearchMessage(const Message* message, TcpMessageHandler& socket);
	void HandleSendMemoMessage(const Message* message, TcpMessageHandler& socket);
	void HandleGiftVerifyIDMessage(const Message* message, TcpMessageHandler& socket);
	void HandleSendGiftMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomCreateMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomPlayerDataMessage(const Message* message, TcpMessageHandler& socket);
	void HandleInRoomMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomInfoMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomJoinMessage(const Message* message, TcpMessageHandler& socket);
	void HandleRoomTitleChangeMessage(const Message* message, TcpMessageHandler& socket);
	void HandleNpcListMessage(const Message* message, TcpMessageHandler& socket);
	void HandleNpcKillMessage(const Message* message, TcpMessageHandler& socket);
	void HandleUpdateQuestProgressMessage(const Message* message, TcpMessageHandler& socket);
	void HandleDeathMessage(const Message* message, TcpMessageHandler& socket);
	void HandleInGameMessage(const Message* message, TcpMessageHandler& socket);
	void HandleReviveMessage(const Message* message, TcpMessageHandler& socket);
	void HandleSymbolListMessage(const Message* message, TcpMessageHandler& socket);
	void HandleBMKOMessage(const Message* message, TcpMessageHandler& socket);
	void HandleBMListMessage(const Message* message, TcpMessageHandler& socket);
	void HandleMissionCountMessage(const Message* message, TcpMessageHandler& socket);
	void HandleMissionClearMessage(const Message* message, TcpMessageHandler& socket);
	void HandleCrystalEnterMessage(const Message* message, TcpMessageHandler& socket);
	void HandleGoalMessage(const Message* message, TcpMessageHandler& socket);
	void HandleHokeyMessage(const Message* message, TcpMessageHandler& socket);
	
	int ChannelType, LastActivity;
	std::vector<User*> users;
	Room rooms[MAX_ROOMS];
	Level level;
	boost::mutex lobbyLock;
	boost::mutex roomCreateLock;

	//Function Set1:
	void SendLobbyInfo(TcpMessageHandler& socket);
	void SendFriendListResponse(MySQL *MySql, MyCharInfo *Info, TcpMessageHandler& socket);
	void SendExitRoomResponse(TcpMessageHandler& socket);
	void SendExitRoomResponse(User* user);
};

#endif // __GAMESERVER_H__
