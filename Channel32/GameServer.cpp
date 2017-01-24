#include "GameServer.h"
#include "all_messages.h"
#include "GameServerFS1.h"
using namespace std;
ExpCalculator ExpCalc(10);
GameServer::GameServer(boost::asio::io_service& ioService, unsigned short tcpListenPort, unsigned short udpListenPort, int type)
	: SpServer(ioService, tcpListenPort, udpListenPort)
{
	srand(time(0));
	ChannelType = type;
	LastActivity = clock();
	rooms[0].SetChannelType(type);
}

void GameServer::PrepareStart()
{

}

int GameServer::GetLastActivity()
{
	return LastActivity;
}

int GameServer::GetTotalPlayers()
{
	return users.size();
}

void GameServer::UpdateActiveUsers()
{
	MySQL MySql;
	//lobbyLock.lock();
	try {
		for (int i = 0; i < users.size(); i++) {
			User* user = users.at(i);
			if (user) {
				if (!user->GetInfo())
				{
					continue;
				}
				MySql.UpdateTime(user->GetInfo()->usr_name);
			}
		}
	}
	catch (...) {
		
	}
	//lobbyLock.unlock();
}

void GameServer::InitializeMessageHandlerFunctions()
{
	this->SetUdpMessageHandlerFunction(MESSAGE_TYPE_UDP_FORWARD_FIRST,MESSAGE_TYPE_UDP_FORWARD_LAST,(UdpMessageHandlerFunction)&GameServer::UdpForwardMessage);
	this->SetUdpMessageHandlerFunction(MESSAGE_TYPE_UDP_HANDSHAKE,(UdpMessageHandlerFunction)&GameServer::UdpHandShakeMessage);
	this->SetUdpMessageHandlerFunction(MESSAGE_TYPE_UDP_KEEPALIVE,(UdpMessageHandlerFunction)&GameServer::UdpKeepAliveMessage);

	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SERVER_JOIN, (TcpMessageHandlerFunction)&GameServer::HandleLoginMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_CHAT_MESSAGE, (TcpMessageHandlerFunction)&GameServer::HandleChatMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SHOP_JOIN, (TcpMessageHandlerFunction)&GameServer::HandleShopJoinMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SHOP_BUY, (TcpMessageHandlerFunction)&GameServer::HandleShopBuyMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SHOP_SELL, (TcpMessageHandlerFunction)&GameServer::HandleShopSellMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ELEMENT_BUY, (TcpMessageHandlerFunction)&GameServer::HandleElementBuyMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_FORCE_CHARGE, (TcpMessageHandlerFunction)&GameServer::HandleForceChargeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_EQUIP_CHANGE, (TcpMessageHandlerFunction)&GameServer::HandleEquipChangeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_USER_INFO, (TcpMessageHandlerFunction)&GameServer::HandleUserInfoMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ITEM_UPGRADE, (TcpMessageHandlerFunction)&GameServer::HandleItemUpgradeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ADD_FRIEND, (TcpMessageHandlerFunction)&GameServer::HandleAddFriendMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_FRIEND_LIST, (TcpMessageHandlerFunction)&GameServer::HandleFriendListMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_CONFIRM_ID, (TcpMessageHandlerFunction)&GameServer::HandleConfirmIDMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_FIND_USER, (TcpMessageHandlerFunction)&GameServer::HandleFindUserMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_EXIT, (TcpMessageHandlerFunction)&GameServer::HandleRoomExitMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_QUIT, (TcpMessageHandlerFunction)&GameServer::HandleRoomExitMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_USER_KICK, (TcpMessageHandlerFunction)&GameServer::HandleUserKickMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_TRADE, (TcpMessageHandlerFunction)&GameServer::HandleTradeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_OPEN_USER_SHOP, (TcpMessageHandlerFunction)&GameServer::HandleUserShopOpenMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SEARCHSHOP_BUY, (TcpMessageHandlerFunction)&GameServer::HandleSearchShopBuyMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_USE_SCROLL, (TcpMessageHandlerFunction)&GameServer::HandleUseScrollMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_BUY_SCROLL, (TcpMessageHandlerFunction)&GameServer::HandleScrollBuyOrSellMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_PICK_SCROLL, (TcpMessageHandlerFunction)&GameServer::HandlePickScrollMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_CARD_SEARCH, (TcpMessageHandlerFunction)&GameServer::HandleCardSearchMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SEND_MEMO, (TcpMessageHandlerFunction)&GameServer::HandleSendMemoMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_GIFT_VERIFY_ID, (TcpMessageHandlerFunction)&GameServer::HandleGiftVerifyIDMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SEND_GIFT, (TcpMessageHandlerFunction)&GameServer::HandleSendGiftMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_CREATE, (TcpMessageHandlerFunction)&GameServer::HandleRoomCreateMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_PLAYERDATA, (TcpMessageHandlerFunction)&GameServer::HandleRoomPlayerDataMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_IN_ROOM, (TcpMessageHandlerFunction)&GameServer::HandleInRoomMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_INFO_REQ, (TcpMessageHandlerFunction)&GameServer::HandleRoomInfoMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_ROOM_JOIN, (TcpMessageHandlerFunction)&GameServer::HandleRoomJoinMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_CHANGE_ROOMTITLE, (TcpMessageHandlerFunction)&GameServer::HandleRoomTitleChangeMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_NPC_LIST, (TcpMessageHandlerFunction)&GameServer::HandleNpcListMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_NPC_KILL, (TcpMessageHandlerFunction)&GameServer::HandleNpcKillMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_QUEST_PROG, (TcpMessageHandlerFunction)&GameServer::HandleUpdateQuestProgressMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_DEATH_MSG, (TcpMessageHandlerFunction)&GameServer::HandleDeathMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_IN_GAME_MSG, (TcpMessageHandlerFunction)&GameServer::HandleInGameMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_REVIVE_REQ, (TcpMessageHandlerFunction)&GameServer::HandleReviveMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SYMBOL_LIST, (TcpMessageHandlerFunction)&GameServer::HandleSymbolListMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_BIGBATTLE_NPC_KO, (TcpMessageHandlerFunction)&GameServer::HandleBMKOMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_BIGBATTLE_NPC_LIST, (TcpMessageHandlerFunction)&GameServer::HandleBMListMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_START_COUNT_DOWN, (TcpMessageHandlerFunction)&GameServer::HandleMissionCountMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_MISSION_COMPLETE, (TcpMessageHandlerFunction)&GameServer::HandleMissionClearMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_CRYSTAL_ENTER, (TcpMessageHandlerFunction)&GameServer::HandleCrystalEnterMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_SOCCER_GOAL, (TcpMessageHandlerFunction)&GameServer::HandleGoalMessage);
	this->SetTcpMessageHandlerFunction(MESSAGE_TYPE_HOKEY_GOAL, (TcpMessageHandlerFunction)&GameServer::HandleHokeyMessage);
}

void GameServer::UdpForwardMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	try {
		const UdpForward* msg = static_cast<const UdpForward*>(message);
		int n = msg->room;
		int source = msg->source;
		int dest = msg->dest;
		if(n >= 0 && n < MAX_ROOMS)
			if(rooms[n].IsOpen())
				rooms[n].SendTo(message,dest,GetUdp());
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in UdpForwardMessage." << endl;
	}
}

void GameServer::BroadcastMessage(const Message* message, TcpMessageHandler* socket, bool Lobby)
{
	try {
		LastActivity = clock();
		lobbyLock.lock();
		for(int i = 0; i < users.size(); i++){
			User* user = users.at(i);
			MyCharInfo *Info = user->GetInfo();
			if(user){
				if(!Info)
				{
					continue;
				}
			}else continue;
			TcpMessageHandler& usocket = user->GetTcpSocket();
			if(socket){
				if(usocket.GetTag() != socket->GetTag()){
					if(Lobby){
						if(Info->usr_room == -1)usocket.Send((Message &)*message);
					}else usocket.Send((Message &)*message);
				}
			}else if(Lobby){
				if(Info->usr_room == -1)usocket.Send((Message &)*message);
			}else usocket.Send((Message &)*message);
		}
		lobbyLock.unlock();
	}catch(...){
		if(lobbyLock.lock_flag_bit)
			lobbyLock.unlock();
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in BroadcastMessage." << endl;
	}
}

User* GameServer::GetUserInstance(char name[13])
{
	try {
		for(int i = 0; i < users.size(); i++){
			User* user = users.at(i);
			if(strcmp(user->GetInfo()->usr_name,name) == 0)return user;
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in GetUserInstance." << endl;
	}
	return 0;
}

void GameServer::HandleClientDisconnected(const TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		User* user = reinterpret_cast<User*>(socket.GetTag());
		if (user != 0)
		{
			MyCharInfo uInfo;
			user->GetCharInfo(uInfo);
			if(uInfo.usr_room == -1)
				BroadcastMessage(&LobbyInfoMessage(uInfo.usr_name,uInfo.Level,uInfo.gender,uInfo.Mission,false),(TcpMessageHandler*)&socket,true);
			else if(uInfo.usr_room >= 0 && uInfo.usr_room < MAX_ROOMS)SendExitRoomResponse(user);
			lobbyLock.lock();
			for(int i = 0; i < users.size(); i++)
				if(user == users.at(i)){
					users.erase(this->users.begin()+i);
					delete user;
					break;
				}
				lobbyLock.unlock();
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleClientDisconnected." << endl;
	}
}

void GameServer::UdpHandShakeMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	try {
		LastActivity = clock();
		const UdpHandShake* msg = static_cast<const UdpHandShake*>(message);
		char name[16],IP[16];
		strcpy(name,(char*)&msg->unk01);
		strcpy(IP,(char*)&msg->unk05);
		for(int i = 0; i < users.size(); i++){
			User* user = users.at(i);
			MyCharInfo uInfo;
			user->GetCharInfo(uInfo);
			if(strcmp(uInfo.usr_name,name) == 0)
			{
				user->SetUdpInfo(IP,remoteEndpoint);
				break;
			}
		}
		GetUdp()->SendTo(UdpHandShake(),remoteEndpoint);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in UdpHandShakeMessage." << endl;
	}
}

void GameServer::UdpKeepAliveMessage(const Message* message, boost::asio::ip::udp::endpoint remoteEndpoint)
{
	try {
		LastActivity = clock();
		GetUdp()->SendTo(UdpKeepAlive(clock()),remoteEndpoint);
		/*char name[16];
		strcpy(name, (const char*)(message + 0x14));
		MySQL MySql;
		if(strlen(name) > 2)
			MySql.UpdateTime(name);*/
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in UdpKeepAliveMessage." << endl;
	}
}

void GameServer::HandleLoginMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const ServerJoinMessage* msg = static_cast<const ServerJoinMessage*>(message);
		cout << "Joining Server : " << msg->username << endl;
		/*if(strcmp("42.2.124.51",(char*)socket.GetRemoteIp().to_string().c_str()) == 0)
		{
			socket.Disconnect();
			return;
		}*/
		bool VisitRewards = false;
		MySQL MySql;
		if(!MySql.Login(msg->username,socket.GetRemoteIp().to_string().c_str(), VisitRewards))
		{
			socket.Disconnect();
		}else if (socket.GetTag() == 0) // client has just connected, this is the first message received
		{
			MyCharInfo Info;
			MySql.GetUserInfo((char*)msg->username,Info);
			if (ChannelType == 2 && Info.Level < 12)
			{
				socket.Disconnect();
				return;
			}
			if (ChannelType == 3 && Info.Level < 17)
			{
				socket.Disconnect();
				return;
			}
			if (Info.Code < 0 || Info.Code > 1000000000 || Info.Water < 0 || Info.Water > 20000 || Info.Fire < 0 || Info.Fire > 20000 || Info.Earth < 0 || Info.Earth > 20000 || Info.Wind < 0 || Info.Wind > 20000 || Info.nSlots == 0)
			{
				socket.Disconnect();
				return;
			}
			srand(time(0));
			MySql.GetScrolls(&Info);
			lobbyLock.lock();
			MySql.SetUserIP(Info.usr_name,(char*)socket.GetRemoteIp().to_string().c_str());
			User* user = new User(socket);
			socket.SetTag(user);
			bool found = false;
			for (int i = 0; i < users.size(); i++) {
				bool conflict = strcmp(Info.ip, users.at(i)->GetInfo()->ip) == 0 && strcmp(Info.hwid, users.at(i)->GetInfo()->hwid) == 0;
				if (Info.usr_id == users.at(i)->GetInfo()->usr_id || conflict) {
					found = true;
					if (users.at(i)->GetTcpSocket().isDisconnected) {
						found = false;
						users.erase(this->users.begin() + i);
					}
					
					break;
				}
			}
			if(!found)
				this->users.push_back(user);
			lobbyLock.unlock();
			if(!found)
			{
			socket.Send(ServerJoinResponseMessage());
			socket.Send(MissionLevelMessage(Info.Mission + 1));
			bool bMyCard[96];
			int IDMyCard[96];
			int TypeMyCard[96];
			int GFMyCard[96];
			int LevelMyCard[96];
			int SkillMyCard[96];
			for(int i = 0; i < 96; i++)
			{
				bMyCard[i] = false;
				IDMyCard[i] = 0; TypeMyCard[i] = 0; GFMyCard[i] = 0; LevelMyCard[i] = 0; SkillMyCard[i] = 0;
			}
			MySql.GetUserItems(Info.usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
			int FreeSlots = 0;
			for(int i = 0; i < Info.nSlots; i++){
				if(bMyCard[i] == false)
					FreeSlots++;
			}
			Info.nFreeSlots = FreeSlots;
			Info.nFriend = MySql.GetFriendList(Info.usr_id,Info.Friend);
			MySql.GetScrolls(&Info);
			user->SetCharInfo(Info);
			int eleType = 0, eleBase = 0, eleMul = 0, code = 0;
			if (VisitRewards)
			{
				eleType = (rng100() % 4) + 1;
				eleBase = (rng100() % 5) + 1;
				if (ChannelType == 1)
					eleBase = 1;
				if (ChannelType == 2)
					eleBase = 2;
				if (ChannelType == 3 && eleBase < 3)
					eleBase = 3;
				eleMul = (rng100() % 20) + 1;
				code = rng1000() * 100;
				int cash = rng1000() / 2 + 10;
				MySql.GetBonus(Info.usr_id, code, cash, ElementTypes[eleType], eleBase*eleMul);
				MySql.GetScrolls(&Info);
				user->SetCharInfo(Info);
			}
			
			socket.Send(ServerJoinUserDataMessage(Info.Points,Info.Points,Info.Code,Info.Coins,Info.Level,Info.Level,Info.gender,Info.scrolls,
				Info.Water,Info.Fire,Info.Earth,Info.Wind,Info.UserType,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,
				Info.nSlots,ChannelType, code, eleType, eleBase, eleMul,0,MAX_ROOMS));
			SendLobbyInfo(socket);
			MySql.AddUserToActiveList(Info.usr_name);
			if(Info.nFriend)SendFriendListResponse(&MySql,&Info,socket);
			}else {
			
				socket.Disconnect();
			}
		}
	}catch(...){
		if(lobbyLock.lock_flag_bit)
			lobbyLock.unlock();
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleLoginMessage." << endl;
	}
}

void GameServer::HandleChatMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const ChatMessageMessage* msg = static_cast<const ChatMessageMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		if(Info->CanChat() >= 5)
		{
			socket.Disconnect();
		}else {
			int len = strlen(msg->msg);
			if(len > 4)
			{
				if(strncmp(msg->msg,"@/gm ",5) == 0)
				{
					ChatMessageArrivalMessage ChatMessage(6,"gm",(char*)msg->recieverId,(char*)(msg->msg+5));
					BroadcastMessage(&ChatMessage,0,false);
					return;
				}else if(strncmp(msg->msg,"@/ski11 ",7) == 0)
				{
					User* user = reinterpret_cast<User*>(socket.GetTag());
					user->GetInfo()->GM_new_skill = atoi(msg->msg+8);
					return;
				}else if(strncmp(msg->msg,"/male",5) == 0)
				{
					MySQL MySql;
					User* user = reinterpret_cast<User*>(socket.GetTag());
					MyCharInfo *Info = user->GetInfo();
					Info->gender = 1;
					MySql.SetGender(Info->usr_id, Info->gender);
					return;
				}else if(strncmp(msg->msg,"/female",7) == 0)
				{
					MySQL MySql;
					User* user = reinterpret_cast<User*>(socket.GetTag());
					MyCharInfo *Info = user->GetInfo();
					Info->gender = 0;
					MySql.SetGender(Info->usr_id, Info->gender);
					return;
				}else if(strncmp(msg->msg,"$$Gift ",6) == 0)
				{
					MySQL MySql;
					lobbyLock.lock();
					User *admin = reinterpret_cast<User*>(socket.GetTag());
					int room = admin->GetInfo()->usr_room;
					if(room == -1)
					{
						for(int i = 0; i < users.size(); i++)
						{
							User *user = users.at(i);
							if(user)
							{
								MyCharInfo *Info = user->GetInfo();
								int type = atoi(msg->msg+7);
								int level = atoi(msg->msg+7+5);
								int skill = atoi(msg->msg+7+5+2);
								int slot = MySql.InsertNewItem(Info,type,999,level,skill);
								user->GetTcpSocket().Send(GiftReceiveMessage(slot,type,999,level,skill));
								user->GetTcpSocket().Send(ItemReceiveMessage("Admin",7,slot));
							}

						}
					}else if(room >= 0 && room <= MAX_ROOMS){
						if(rooms[room].IsOpen())
						{

							for(int i = 0; i < rooms[room].GetCapacity(); i++)
							{
								User *user = rooms[room].GetUser(i);
								if(user)
								{
									MyCharInfo *Info = user->GetInfo();
									int type = atoi(msg->msg+7);
									int level = atoi(msg->msg+7+5);
									int skill = atoi(msg->msg+7+5+2);
									int slot = MySql.InsertNewItem(Info,type,999,level,skill);
									user->GetTcpSocket().Send(GiftReceiveMessage(slot,type,999,level,skill));
									user->GetTcpSocket().Send(ItemReceiveMessage("Admin",7,slot));
								}

							}
						}
					}
					lobbyLock.unlock();
					return;
				}else if(strncmp(msg->msg,"@/power ",7) == 0)
				{
					int power = atoi(msg->msg+8);
					User* user = reinterpret_cast<User*>(socket.GetTag());
					MyCharInfo *Info = user->GetInfo();
					Info->usr_power = power;
				}
			}
			ChatMessageArrivalMessage ChatMessage(msg->chatType,(char*)msg->senderId,(char*)msg->recieverId,(char*)msg->msg);
			if(msg->chatType == 1){
				User *user = GetUserInstance((char*)msg->recieverId);
				if(user)
					if(user->GetInfo())
						user->GetTcpSocket().Send(ChatMessage);
			}else BroadcastMessage(&ChatMessage,&socket,true);
		}
		//ChatMessageArrivalMessage ChatMessage(6,"gm","","Royal-thison9jai all are on9 noobs");
		//BroadcastMessage(&ChatMessage,0,false);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleChatMessage." << endl;
	}
}

void GameServer::HandleShopJoinMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		User* user = reinterpret_cast<User*>(socket.GetTag());
		int cash;
		MySQL MySql;
		MySql.GetMoneyAmmount(user->GetInfo()->usr_id,&cash,0);
		socket.Send(ShopJoinMessage(cash));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleShopJoinMessage." << endl;
	}
}

void GameServer::HandleShopBuyMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const GameShopItemBuyMessage* msg = static_cast<const GameShopItemBuyMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		int codecost = 0,cashcost = 0, cash = 0;
		MySql.UpdateUserInfo(*Info);
		MySql.GetShopItemCost(msg->item,msg->gf,msg->level,codecost,cashcost);
		if (codecost > Info->Code || cashcost > Info->Coins)
		{
			socket.Disconnect();
		}
		if(cashcost == 0 && codecost == 0)
		{
			//socket.Disconnect();
			cashcost = 10000;
			codecost = 1000000;
		}else {
		MySql.GetMoneyAmmount(Info->usr_id,(int*)&cash,&Info->Code,'-',cashcost,(unsigned __int64)codecost);

		MySql.InsertNewItem(Info,msg->item,msg->gf,msg->level,0);
		bool bMyCard[96];
		int TypeMyCard[96];
		int GFMyCard[96];
		int LevelMyCard[96];
		int SkillMyCard[96];
		MySql.GetUserItems(Info->usr_id,bMyCard,0,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
		int FreeSlots = 0;
		for(int i = 0; i < Info->nSlots && i < 96; i++){
			if(!bMyCard[i])
				FreeSlots++;
		}
		Info->nFreeSlots = FreeSlots;
		socket.Send(ShopBuyResponseMessage(1,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,Info->nSlots,Info->Code,cash,Info->Coins));
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleShopBuyMessage." << endl;
	}
}

void GameServer::HandleShopSellMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const GameShopItemSellMessage* msg = static_cast<const GameShopItemSellMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		MySql.DeleteItem(Info->usr_id,msg->item_slot);
		socket.Send(ShopSellResponseMessage(msg->item_slot,Info->Code));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleShopSellMessage." << endl;
	}
}

void GameServer::HandleElementBuyMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ElementBuyMessage* msg = static_cast<const ElementBuyMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		if (!user)
			return;
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		MySql.UpdateUserInfo(*Info);
		int buy = MySql.BuyElements(Info,msg->item_id,msg->amount);
		socket.Send(ElementBuyResponseMessage(buy,Info->Code,Info->Water,Info->Fire,Info->Earth,Info->Wind));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleElementBuyMessage." << endl;
	}
}

void GameServer::HandleForceChargeMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ForceChargeMessage* msg = static_cast<const ForceChargeMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;

		bool bMyCard[96];
		int IDMyCard[96];
		int TypeMyCard[96];
		int GFMyCard[96];
		int LevelMyCard[96];
		int SkillMyCard[96];
		for(int i = 0; i < 96; i++)
		{
			bMyCard[i] = false;
			IDMyCard[i] = 0; TypeMyCard[i] = 0; GFMyCard[i] = 0; LevelMyCard[i] = 0; SkillMyCard[i] = 0;
		}
		MySql.GetUserItems(Info->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);


		MySql.ChargeForce(Info->usr_id,msg->item_slot,msg->item_type, GFMyCard[msg->item_slot] ,msg->gf_slot,msg->gf_type);
		socket.Send(ForceChargeResponseMessage(1,msg->item_slot,msg->item_type,msg->gf_slot));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleForceChargeMessage." << endl;
	}
}

void GameServer::HandleEquipChangeMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const EquipmentChangeMessage* msg = static_cast<const EquipmentChangeMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		if (Info)
		{
			MySQL MySql;
			MySql.ChangeEquips(Info->usr_id, msg->mag, msg->wpn, msg->arm, msg->pet, msg->foot, msg->body, msg->hand1, msg->hand2, msg->face, msg->hair, msg->head);
			if (Info->usr_room >= 0 && Info->usr_room < MAX_ROOMS)
				rooms[Info->usr_room].SendPlayerData(&MySql, Info->usr_slot);
		}

	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleEquipChangeMessage." << endl;
	}
}

void GameServer::HandleUserInfoMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const UserInfoRequestMessage* msg = static_cast<const UserInfoRequestMessage*>(message);
		MySQL MySql;
		UserInfoResponse UIR;
		strcpy(UIR.username,msg->username);
		MySql.GetUserData(&UIR);
		int maxLevel = 8;
		if (ChannelType == 2)
			maxLevel = 5;
		if (ChannelType == 1)
			maxLevel = 3;
		if (UIR.magiclevel > maxLevel)
			UIR.magic = UIR.magicskill = UIR.magicgf = UIR.magiclevel = 0;
		if (UIR.weaponlevel > maxLevel)
			UIR.weapon = UIR.weaponskill = UIR.weapongf = UIR.weaponlevel = 0;
		if (UIR.armourlevel > maxLevel)
			UIR.armour = UIR.armourskill = UIR.armourgf = UIR.armourlevel = 0;

		socket.Send(UserInfoMessage(UIR.username,level.getLevel(UIR.Points),UIR.gender,UIR.defaultcharacter,UIR.Points,UIR.wins,UIR.losses,UIR.KO,
			UIR.Down,UIR.Codes,UIR.Coins,UIR.magic,UIR.weapon,UIR.armour,UIR.pet,UIR.magicgf,UIR.weapongf,UIR.armourgf,UIR.petgf,UIR.magiclevel,
			UIR.weaponlevel,UIR.armourlevel,UIR.petlevel,UIR.magicskill,UIR.weaponskill,UIR.armourskill,UIR.petskill,UIR.mission,UIR.foot,UIR.body,UIR.hand1,UIR.hand2,UIR.face,UIR.hair,UIR.head));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleUserInfoMessage." << endl;
	}
}

void GameServer::HandleItemUpgradeMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ItemUpgradeMessage* msg = static_cast<const ItemUpgradeMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		if(!user)
			return;
		MySQL MySql;
		CardUpgradeResponse CUR;
		if (CUR.Level > 6 && ChannelType != 3)
		{
			socket.Disconnect();
			return;
		}
		CUR.Slot = msg->Slot;
		CUR.UpgradeType = msg->UpgradeType; //1 = Lvl, 2 = Skill
		CUR.Upgraded = msg->UpgradeType; //1 lvl, 5 skill
		if(CUR.Upgraded != 1)
			CUR.Upgraded = 5; //1 lvl, 5 skill
		CUR.UpgradeType2 = msg->UpgradeType;
		MyCharInfo *Info = user->GetInfo();
		MySql.UpdateUserInfo(*Info);

		if (Info->Code < 0 || Info->Code > 1000000000 || Info->Water < 0 || Info->Water > 20000 || Info->Fire < 0 || Info->Fire > 20000 || Info->Earth < 0 || Info->Earth > 20000 || Info->Wind < 0 || Info->Wind > 20000 || Info->nSlots == 0)
		{
			socket.Disconnect();
			return;
		}

		if(MySql.UpgradeCard(user->GetInfo(),&CUR) && CUR.Level > 7){
			UdpItemUpgrade ItemUpgrade(user->GetInfo()->usr_name,CUR.Type,CUR.Level);
			for(int i = 0; i < users.size(); i++){
				User* user = users.at(i);
				GetUdp()->SendTo(ItemUpgrade,user->GetUdpEndpoint());
			}
		}
		
		//socket.Send(ElementSpawnMessage());

		int n = user->GetInfo()->usr_room;
		int slot = user->GetInfo()->usr_slot;
		if(n >= 0 && n < MAX_ROOMS)
			rooms[n].Send(&ItemUpgradeResponseMessage(CUR.Slot,CUR.UpgradeType,CUR.Upgraded,CUR.Level,CUR.Skill,CUR.Type,CUR.GF,slot,CUR.UpgradeType2,
			CUR.Code,CUR.WaterElements,CUR.FireElements,CUR.EarthElements,CUR.WindElements, CUR.Returned));
		else socket.Send(ItemUpgradeResponseMessage(CUR.Slot,CUR.UpgradeType,CUR.Upgraded,CUR.Level,CUR.Skill,CUR.Type,CUR.GF,slot,CUR.UpgradeType2,
			CUR.Code,CUR.WaterElements,CUR.FireElements,CUR.EarthElements,CUR.WindElements, CUR.Returned));
		//if(Info.usr_room != -1)RoomList.ProdcastInRoomUpgrade(this,&Card_Upgrade_Response,Info.usr_room);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleItemUpgradeMessage." << endl;
	}
}

void GameServer::HandleAddFriendMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const AddFriendMessage* msg = static_cast<const AddFriendMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		bool Add = msg->unk2 == 1;
		if(Add){
			if(Info->nFriend < 24)MySql.AddFriend(Info->usr_id,(char*)msg->username);
		}else MySql.DeleteFriend(Info->usr_id,(char*)msg->username);
		socket.Send(AddFriendResponseMessage((char*)msg->username,1));
		Info->nFriend = MySql.GetFriendList(Info->usr_id,Info->Friend);
		SendFriendListResponse(&MySql,Info,socket);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleAddFriendMessage." << endl;
	}
}

void GameServer::HandleFriendListMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const AddFriendMessage* msg = static_cast<const AddFriendMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MySQL MySql;
		SendFriendListResponse(&MySql,user->GetInfo(),socket);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleFriendListMessage." << endl;
	}
}

void GameServer::HandleConfirmIDMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ConfirmIDMessage* msg = static_cast<const ConfirmIDMessage*>(message);
		MySQL MySql;
		socket.Send(ConfirmIDResponseMessage(MySql.CheckId((char*)msg->username)));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleConfirmIDMessage." << endl;
	}
}

void GameServer::HandleFindUserMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const FindUserMessage* msg = static_cast<const FindUserMessage*>(message);
		User *user = GetUserInstance((char*)msg->username);
		if(user)
			socket.Send(FindUserResponseMessage((char*)msg->username,user->GetInfo()->usr_room+1));
		else socket.Send(FindUserResponseMessage((char*)msg->username,-1));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleFindUserMessage." << endl;
	}
}

void GameServer::HandleRoomExitMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		SendExitRoomResponse(socket);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomExitMessage." << endl;
	}
}

void GameServer::HandleUserKickMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const RoomUserKickMessage* msg = static_cast<const RoomUserKickMessage*>(message);
		User *user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS)
		{
			if(Info->usr_slot == rooms[n].GetMaster())
			{
				User *kicked = rooms[n].GetUser(msg->slot);
				if(kicked)
					SendExitRoomResponse(kicked);
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomExitMessage." << endl;
	}
}

void GameServer::HandleTradeMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const TradeStateChangeMessage* msg = static_cast<const TradeStateChangeMessage*>(message);
		User *user1 = GetUserInstance((char*)msg->username);
		User *user2 = GetUserInstance((char*)msg->username2);
		if(user1 && user2){
			TradeStateChangeMessage response_msg = *msg;
			MyCharInfo *Info1 = user1->GetInfo();
			MyCharInfo *Info2 = user2->GetInfo();

			if(Info1 && Info2)
			{
				if (Info1->Code < 0 || Info1->Code > 1000000000 || Info1->Water < 0 || Info1->Water > 20000 || Info1->Fire < 0 || Info1->Fire > 20000 || Info1->Earth < 0 || Info1->Earth > 20000 || Info1->Wind < 0 || Info1->Wind > 20000 || Info1->nSlots == 0)
				{
					socket.Disconnect();
					return;
				}
				if (msg->Code > Info1->Code)
				{
					SendExitRoomResponse(socket);
					return;
				}
				response_msg.availableslots = Info2->nFreeSlots;
				MySQL MySql;
				for(int i = 0; i < 4; i++)
				{
					if(response_msg.itemType[i] > 0 && response_msg.itemType[i] < 10000){
						if(!MySql.ItemCheck(Info1->usr_id,response_msg.itemType[i],response_msg.itemLevel[i],response_msg.itemSkill[i]))
						{
							SendExitRoomResponse(socket);
							return;
						}
					}else if(response_msg.itemType[i] == -1 && response_msg.itemID[i] > 0){
						if(!MySql.ElementCheck(Info1->usr_id,response_msg.itemID[i]))
						{
							SendExitRoomResponse(socket);
							return;
						}
					}
				}
				if(Info2->TradeProgress && response_msg.confirm == 1){
					response_msg.confirm = 14;
					user1->GetTcpSocket().Send(response_msg);
					Info1->TradeProgress = 0;
				} else {
					Info1->TradeProgress = response_msg.confirm;
					user1->GetTcpSocket().Send(response_msg);
					response_msg.availableslots = Info1->nFreeSlots;
					user2->GetTcpSocket().Send(response_msg);
					if(Info1->usr_room != Info2->usr_room){
						SendExitRoomResponse(socket);
						//socket.Disconnect();
						return;
					}
					if(response_msg.confirm == 14 || response_msg.confirm == 5)
					{
						Info1->TradeProgress = 0;
						Info2->TradeProgress = 0;
					}
					if(Info1->TradeProgress == 9)
					{
						Info1->TS.Code = response_msg.Code;
						for(int i = 0; i < 4; i++)
						{
							Info1->TS.itemID[i] = response_msg.itemID[i];
							Info1->TS.itemType[i] = response_msg.itemType[i];
							Info1->TS.itemGF[i] = response_msg.itemGF[i];
							Info1->TS.itemLevel[i] = response_msg.itemLevel[i];
							Info1->TS.itemSkill[i] = response_msg.itemSkill[i];
						}
						if(Info2->TradeProgress == 9)
						{
							MySql.IssueTrade(&Info1->TS,&Info2->TS,Info1->usr_id,Info2->usr_id);
							bool bMyCard[96];
							int IDMyCard[96];
							int TypeMyCard[96];
							int GFMyCard[96];
							int LevelMyCard[96];
							int SkillMyCard[96];
							MySql.GetUserItems(Info1->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
							int FreeSlots = 0;
							for(int i = 0; i < Info1->nSlots && i < 96; i++){
								if(!bMyCard[i])
									FreeSlots++;
							}
							Info1->nFreeSlots = FreeSlots;
							MySql.UpdateUserInfo(*Info1);
							Info1->TradeProgress = 0;
							user1->GetTcpSocket().Send(TradeSuccessResponseMessage(Info1->usr_name,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,Info1->Code,Info1->Water,Info1->Fire,Info1->Earth,Info1->Wind));
							MySql.GetUserItems(Info2->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
							MySql.UpdateUserInfo(*Info2);
							FreeSlots = 0;
							for(int i = 0; i < Info2->nSlots && i < 96; i++){
								if(!bMyCard[i])
									FreeSlots++;
							}
							Info2->nFreeSlots = FreeSlots;
							Info2->TradeProgress = 0;
							user2->GetTcpSocket().Send(TradeSuccessResponseMessage(Info2->usr_name,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,Info2->Code,Info2->Water,Info2->Fire,Info2->Earth,Info2->Wind));
						}
					}
				}
			}else {
				response_msg.confirm = 14;
				user1->GetTcpSocket().Send(response_msg);
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleTradeMessage." << endl;
	}
}

void GameServer::HandleUserShopOpenMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const UserShopOperationMessage* msg = static_cast<const UserShopOperationMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		UserShopOperationMessage OpenUserShop = *msg;
		MySQL MySql;
		if(OpenUserShop.shoprequest == 2)
		{
			User *user1 = GetUserInstance((char*)msg->username);
			if(user1){
				MyCharInfo *info = user1->GetInfo();
				MySql.UpdateUserInfo(*info);
				for(int i = 0; i < 4; i++)OpenUserShop.items[i] = info->Shop_Items[i];
				strcpy(OpenUserShop.title,info->Shop_Title);
				MySql.GetFromShop(info,(OpenUserShopRequest*)&OpenUserShop);
			}
		}else if(OpenUserShop.shoprequest == 4)
		{
			MyCharInfo *Info = user->GetInfo();
			MySql.UpdateUserInfo(*Info);
			strcpy(Info->Shop_Title,OpenUserShop.title);
			for(int i = 0; i < 4; i++)Info->Shop_Items[i] = OpenUserShop.items[i];
			MySql.AddToShop(Info,(OpenUserShopRequest*)&OpenUserShop);
			int n = Info->usr_room;
			if(n >= 0 && n < MAX_ROOMS){
				rooms[n].Send(&OpenUserShopResponseMessage(OpenUserShop.username,OpenUserShop.title),-1,Info->usr_slot);
			}
			Info->usershop_open = true;
		}else if(OpenUserShop.shoprequest == 5){
			MyCharInfo *Info = user->GetInfo();
			for(int i = 0; i < 4; i++)OpenUserShop.items[i] = Info->Shop_Items[i];
			MySql.GetFromShop(Info,(OpenUserShopRequest*)&OpenUserShop);
			MySql.RemoveItems(Info);
			for(int i = 0; i < 4; i++)Info->Shop_id[i] = -1;
			Info->usershop_open = false;
			bool bMyCard[96];
			int IDMyCard[96];
			int TypeMyCard[96];
			int GFMyCard[96];
			int LevelMyCard[96];
			int SkillMyCard[96];
			MySql.GetUserItems(Info->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
			int n = Info->usr_room;
			if(n >= 0 && n < MAX_ROOMS){
				rooms[n].Send(&UserShopResponseMessage(Info->usr_name,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,Info->Code,Info->Water,Info->Fire,Info->Earth,Info->Wind,3,-1));
			}
		}else if(OpenUserShop.shoprequest == 3){
			User *user1 = GetUserInstance((char*)OpenUserShop.username);
			if(user1){
				MyCharInfo *Info = user->GetInfo();
				MyCharInfo *info = user1->GetInfo();
				MySql.UpdateUserInfo(*Info);
				MySql.UpdateUserInfo(*info);
				MySql.IssueUserShopBuy(info, Info, (OpenUserShopRequest*)&OpenUserShop);
				user1->GetTcpSocket().Send(UserShopBuyResponseMessage());
				bool bMyCard[96];
				int IDMyCard[96];
				int TypeMyCard[96];
				int GFMyCard[96];
				int LevelMyCard[96];
				int SkillMyCard[96];
				MySql.GetUserItems(info->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
				int FreeSlots = 0;
				for(int i = 0; i < info->nSlots && i < 96; i++){
					if(!bMyCard[i])
						FreeSlots++;
				}
				info->nFreeSlots = FreeSlots;
				MySql.UpdateUserInfo(*info);
				user1->GetTcpSocket().Send(UserShopResponseMessage(info->usr_name,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,info->Code,info->Water,info->Fire,info->Earth,info->Wind,1,0));
				socket.Send(UserShopBuyResponseMessage());
				MySql.GetUserItems(Info->usr_id,bMyCard,IDMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard);
				FreeSlots = 0;
				for(int i = 0; i < Info->nSlots && i < 96; i++){
					if(!bMyCard[i])
						FreeSlots++;
				}
				Info->nFreeSlots = FreeSlots;
				MySql.UpdateUserInfo(*Info);
				socket.Send(UserShopResponseMessage(Info->usr_name,bMyCard,TypeMyCard,GFMyCard,LevelMyCard,SkillMyCard,Info->Code,Info->Water,Info->Fire,Info->Earth,Info->Wind,2,-1));
			}
			return;
		}
		socket.Send(OpenUserShop);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleUserShopOpenMessage." << endl;
	}
}

void GameServer::HandleSearchShopBuyMessage(const Message* message, TcpMessageHandler& socket)
{

}
void GameServer::HandleUseScrollMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ScrollUseMessage* msg = static_cast<const ScrollUseMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		int slot = msg->slot;
		if(slot >= 0 && slot < 3){
			if(msg->unk2 == 2)
			{
				MyCharInfo *Info = user->GetInfo();
				Info->scrolls[slot] = 0;
				MySQL MySql;
				MySql.UpdateScrolls(Info->usr_id,slot,0);
			}else if(msg->unk2 == 1 || msg->unk2 == 4)
			{
				MyCharInfo *Info = user->GetInfo();
				int eleType = msg->slot;
				int n = Info->usr_room;
				if(n >= 0 && n < MAX_ROOMS)
					rooms[n].Send(&ElementCapturedMessage(Info->usr_slot,eleType,5,5));

			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleUseScrollMessage." << endl;
	}
}

void GameServer::HandleScrollBuyOrSellMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ScrollBuyOrSellMessage* msg = static_cast<const ScrollBuyOrSellMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		MySql.GetScrolls(Info);
		int unk2 = 0;
		if(msg->buy == 1){
			Info->scrolls[msg->scrollid] = 0;
			MySql.UpdateScrolls(Info->usr_id,msg->scrollid,0);
			unk2 = msg->scrollid;
		}else {
			for(int i = 0; i < 3; i++)
				if(Info->scrolls[i] == 0){
					Info->scrolls[i] = msg->scrollid;
					MySql.UpdateScrolls(Info->usr_id,i,msg->scrollid+1);
					unk2 = i;
					break;
				}
		}
		socket.Send(ScrollBuyOrSellResponseMessage(msg->buy,unk2,msg->scrollid+1,Info->Code));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleScrollBuyOrSellMessage." << endl;
	}
}

void GameServer::HandlePickScrollMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ScrollPickMessage* msg = static_cast<const ScrollPickMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		MySql.UpdateScrolls(Info->usr_id,msg->slot,msg->scroll);
		socket.Send(ScrollPickResponseMessage(msg->scroll,msg->slot));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandlePickScrollMessage." << endl;
	}
}

void GameServer::HandleCardSearchMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const UserShop2SearchMessage* msg = static_cast<const UserShop2SearchMessage*>(message);
		CardSearchResponse CSR;
		MySQL MySql;
		MySql.SearchShop(&CSR,(SearchType)msg->searchtype);
		socket.Send(UserShop2SearchResponseMessage(CSR.total,CSR.rooms,CSR.name,CSR.levels,CSR.gender,CSR.price,CSR.card,CSR.gf,CSR.level,CSR.skill));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleCardSearchMessage." << endl;
	}
}

void GameServer::HandleSendMemoMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const MemoMessage* msg = static_cast<const MemoMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		if(!MySql.CheckId((char*)msg->username)){
			socket.Send(ConfirmIDResponseMessage(0));
		}else {
			User* receiver = GetUserInstance((char*)msg->username);
			if(receiver){
				MySql.SaveMemo(Info->usr_name,(char*)msg->username,(char*)msg->msg,true);
				receiver->GetTcpSocket().Send(MemoReceiveMessage(Info->usr_name,msg->unk3,(char*)msg->msg));
			}else MySql.SaveMemo(Info->usr_name,(char*)msg->username,(char*)msg->msg,false);
			socket.Send(MemoResponseMessage(1,(char*)msg->username));
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleSendMemoMessage." << endl;
	}
}

void GameServer::HandleGiftVerifyIDMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		socket.Send(GiftVerifyIDMessage(1));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleGiftVerifyIDMessage." << endl;
	}
}

void GameServer::HandleSendGiftMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const GiftMessage* msg = static_cast<const GiftMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		socket.Send(SendGiftResponseMessage(2,(char*)msg->username,msg->gift_type,msg->slot));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleSendGiftMessage." << endl;
	}
}

void GameServer::HandleRoomCreateMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const RoomCreationMessage* msg = static_cast<const RoomCreationMessage*>(message);
		if(msg->map == 29 && msg->mode != 28)
			socket.Disconnect();
		else if(msg->map == 10 && msg->mode != 8)
			socket.Disconnect();
		else if(msg->map == 30 && msg->mode != 29)
			socket.Disconnect();
		else if(msg->map == 35 && msg->mode != 41)
			socket.Disconnect();
		else if(msg->capacity > 8)
			socket.Disconnect();
		else if (msg->mode == INFINITY_SURVIVAL || msg->mode == INFINITY_SYMBOL || msg->mode == INFINITY_KING || msg->mode == HERO_MODE || msg->mode == BB_SURVIVAL || msg->mode == BM_AUTO || msg->mode == CRYSTAL_MODE || msg->mode == MISSION_TRAINING || (msg->mode == BM_DEATH_MATCH && ChannelType == 1))
		{
			socket.Send(RoomCreationResponseMessage(1, 0, (char*)msg->roomname, msg->mode, msg->map, (char*)msg->password, msg->capacity, msg->allowscrolls, msg->autoteam, 10, msg->maxcardlevel, msg->allowcritsheild));
		}
		else {
		User* user = reinterpret_cast<User*>(socket.GetTag());
		int roomnumber = msg->roomnumber;
		if(roomnumber < 0 || roomnumber > MAX_ROOMS)roomnumber = 0;
		
		if(user->GetInfo()->usr_room == -1){
			this->roomCreateLock.lock();
		if(rooms[roomnumber].Create(user,roomnumber,(char*)msg->roomname,(char*)msg->password, msg->mode, msg->map, msg->capacity, msg->allowscrolls, msg->autoteam, msg->maxcardlevel, msg->allowcritsheild) == false)
			for(roomnumber = 0; roomnumber < MAX_ROOMS; roomnumber++)
				if(rooms[roomnumber].Create(user,roomnumber,(char*)msg->roomname,(char*)msg->password, msg->mode, msg->map, msg->capacity, msg->allowscrolls, msg->autoteam, msg->maxcardlevel, msg->allowcritsheild))
					break;
		this->roomCreateLock.unlock();
		}else {
			socket.Disconnect();
			return;
		}
		
		if(roomnumber < MAX_ROOMS && user->GetInfo()->usr_room != -1)
		{
			socket.Send(RoomCreationResponseMessage(2, roomnumber,(char*)msg->roomname,rooms[roomnumber].GetMode(), rooms[roomnumber].GetMap(), (char*)msg->password, rooms[roomnumber].GetCapacity(), rooms[roomnumber].IsAllowScrolls(), msg->autoteam, user->GetInfo()->DefaultCharacter+user->GetInfo()->premium,msg->maxcardlevel, rooms[roomnumber].IsAllowCritShield()));
			BroadcastMessage(&RoomBasicInfoUpdateMessage(1,roomnumber,(char*)msg->roomname,rooms[roomnumber].GetMode(), rooms[roomnumber].GetMap(),rooms[roomnumber].GetCapacity(),rooms[roomnumber].IsPassworded(), rooms[roomnumber].IsPotion(),rooms[roomnumber].IsClosed(),rooms[roomnumber].IsPremium(),rooms[roomnumber].GetChars()),0,true);
			MyCharInfo *Info = user->GetInfo();
			BroadcastMessage(&LobbyInfoMessage(Info->usr_name,Info->Level,Info->gender,Info->Mission,false),0,true);
			MySQL MySql;
			rooms[Info->usr_room].GetPlayerData(&MySql,user,0);
		}else {
			socket.Send(RoomJoinResponseMessage(3,roomnumber,(char*)msg->roomname,msg->mode,msg->map,0,0,0,0));
		}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomCreateMessage." << endl;
	}
}

void GameServer::HandleRoomPlayerDataMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const RoomUserDataRequestMessage* msg = static_cast<const RoomUserDataRequestMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		if(Info->usr_room >= 0 && Info->usr_room < MAX_ROOMS)
			for(int i = 0; i < 8; i++)
				rooms[Info->usr_room].GetPlayerData(&MySql,user,i);
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomPlayerDataMessage." << endl;
	}
}

void GameServer::HandleInRoomMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const RoomUserStateChangeMessage* msg = static_cast<const RoomUserStateChangeMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		MySQL MySql;
		Info->usr_team = msg->team;
		int n = Info->usr_room;
		bool wasNotStarted = !rooms[n].IsStarted();
		bool wasReady = Info->usr_ready;
		if(msg->GameStart == 0)
		{
			if(n >= 0 && n < MAX_ROOMS && (Info->usr_char != msg->Character || Info->usr_team != msg->team )){
				Info->usr_char = msg->Character;
				Info->usr_team = msg->team;
				if(rooms[n].IsOpen())BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
			}
		}
		else if(msg->GameStart == 2)
		{
			Info->usr_ready = (BYTE)msg->Ready;
		}
		if(rooms[n].GetMode() == BB_SURVIVAL)
			socket.Send(BigBattleNpcMultiplierResponseMessage(rooms[n].GetBBX()));
		if(n >= 0 && n < MAX_ROOMS){
			rooms[n].SendPlayerData(&MySql,Info->usr_slot,wasReady);
			Info->usr_life = rooms[n].GetUserGameLife(Info->questlife);
			if(rooms[n].IsStarted()){
				if(rooms[n].IsVSMode())
					BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
				if(rooms[n].IsKingMode()){
					if(wasNotStarted)socket.Send(NewKingResponseMessage(Info->usr_slot));
					else socket.Send(NewKingResponseMessage(rooms[n].GetKing()));
				}
				if (rooms[n].GetMode() == INFINITY_SURVIVAL || rooms[n].GetMode() == MISSION_MODE)
				{
					rooms[n].Send(&MissionPassageCrossResponseMessage(time(0), clock()));
					int slots[] = { 0,0,0,0,0,0,0,0 };
					rooms[n].GetSlots(slots);
					rooms[n].Send(&SpawnResponseMessage(slots, Info->usr_slot));
					BroadcastMessage(&RoomBasicInfoUpdateMessage(1, n, rooms[n].GetTitle(), rooms[n].GetMode(), rooms[n].GetMap(), rooms[n].GetCapacity(), rooms[n].IsPassworded(), rooms[n].IsPotion(), rooms[n].IsClosed(), rooms[n].IsPremium(), rooms[n].GetChars()), 0, true);
				}

			}
			if(rooms[n].GetMode() == COMMUNITY_MODE)
				rooms[n].GetOpenShops(user);
			if(rooms[n].GetMode() == SOCCER_MODE || rooms[n].GetMode() == HOKEY_MODE)
				rooms[n].Send(&GoalResponseMessage(3,0,0));
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleInRoomMessage." << endl;
	}
}

void GameServer::HandleRoomInfoMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const RoomInfoRequestMessage* msg = static_cast<const RoomInfoRequestMessage*>(message);
		int n = msg->roomnumber;
		if(n >= 0 && n < MAX_ROOMS)
			socket.Send(RoomInfoMessage(rooms[n].GetLevels(),rooms[n].GetGenders(),rooms[n].GetUsernames(),rooms[n].GetMaster()));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomInfoMessage." << endl;
	}
}

void GameServer::HandleRoomJoinMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const RoomJoinMessage* msg = static_cast<const RoomJoinMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		int n = msg->roomnumber;
		int join = 0;
		if(n >= 0 && n < MAX_ROOMS){
			if(user->GetInfo()->usr_room != -1)
				socket.Disconnect();
			else {
				join = rooms[n].Join(user,(char*)msg->roompw);
				socket.Send(RoomJoinResponseMessage(join,n,rooms[n].GetTitle(),rooms[n].GetMode(),rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsAllowScrolls(),user->GetInfo()->usr_slot,rooms[n].IsAllowCritShield()));
				if(join == 0){
					MyCharInfo *Info = user->GetInfo();
					BroadcastMessage(&LobbyInfoMessage(Info->usr_name,Info->Level,Info->gender,Info->Mission,false),0,true);
					MySQL MySql;
					if(Info->usr_room >= 0 && Info->usr_room < MAX_ROOMS){
						for(int i = 0; i < 8; i++)
							if(i != Info->usr_slot){
								rooms[Info->usr_room].GetPlayerData(&MySql,user,i);
								socket.Send(NewMasterResponseMessage(rooms[Info->usr_room].GetMaster()));
							}
							rooms[Info->usr_room].SendPlayerData(&MySql,Info->usr_slot);
							BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
					}
				}
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomJoinMessage." << endl;
	}
}

void GameServer::HandleRoomTitleChangeMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const RoomTitleChangeMessage* msg = static_cast<const RoomTitleChangeMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		int n = msg->room;
		if(n >= 0 && n < MAX_ROOMS)
			if(rooms[n].IsOpen()){
				rooms[n].SetTitle((char*)msg->title);
				rooms[n].Send(&RoomTitleChangeResponseMessage(rooms[n].GetTitle()));
				BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
			}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleRoomTitleChangeMessage." << endl;
	}
}

void GameServer::HandleNpcListMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const NpcListMessage* msg = static_cast<const NpcListMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			rooms[n].SendNpcListMsg(msg);
		}
		short NpcLevels[33];
		for(int i = 0; i < 33; i++)
			NpcLevels[i] = msg->npc[i].level;
		socket.Send(NpcListResponseMessage(NpcLevels));
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleNpcListMessage." << endl;
	}
}

void GameServer::HandleNpcKillMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		srand(0);
		const NpcKillMessage* msg = static_cast<const NpcKillMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		int slot = Info->usr_slot;
		if (slot < 0 || slot > 8) {
			socket.Disconnect();
			return;
		}
		ExpGain exp;
		int levels[16];
		ExpCalc.Calculate(msg->npcType,(ExpCalculator::ExpGain*)&exp,(int*)msg->damages);
		int divider = 1;
		if(ChannelType == 1)
			divider = 5;
		else if(ChannelType == 2)
			divider = 3;

		for(int i = 0; i < 8; i++)
			if(exp.exp[i] > 0)
				exp.exp[i] = exp.exp[i] / divider;

		for(int i = 0; i < 16; i++){
			if(i == Info->usr_slot){
				Level lvl;
				int l = lvl.getLevel(Info->Points+(exp.cpMul[i]*exp.exp[i]));
				if(l > Info->Level){
					levels[i] = l;
					//Info->Level = l;
				}else levels[i] = -1;
			}else levels[i] = -1;
		}
		int eleType = (rng100()%4)+1;
		int eleBase = (rng100()%5)+1;
		int eleMul = (rng100()%4)+1;
		int nerf = rng100();

		if(nerf%3 || (msg->damages[Info->usr_slot] < 200 && rng100()%5))
		{
			eleType = 0;
			eleBase = 0;
			eleMul = 0;
		}
		if (rng100() % 4 && eleBase > 1) {
			eleBase /= 2;
		}
		if(rng100()%5 && eleMul > 5){
			eleMul /= 2;
		}
		if (eleBase > 0 && ChannelType == 1)
		{
			eleBase = 1;
			eleMul = eleMul / 2 + 1;
		}
		if (eleBase > 0 && ChannelType == 2)
		{
			eleBase = 3;
			eleMul = eleMul / 2 + 1;
		}
		int tot_dmg = 0;
		for (int i = 0; i < 8; i++)
		{
			tot_dmg += msg->damages[i];
		}
		if (clock() - Info->usr_last_element < 5000)
		{
			eleBase = 0;
			eleType = 0;
			eleMul = 0;
			exp.exp[slot] /= 3;
		}
		else {
			Info->usr_last_element = clock();
		}

		if(n >= 0 && n < MAX_ROOMS) {

			if (msg->damages[Info->usr_slot] > 500 && rooms[n].GetProgress() > 35) {
				eleBase = 5;
				eleType = (rng100() % 4) + 1;
				eleMul = (rng100() % 5) + 1;
			}

			if(rooms[n].IsQuestMode() && rooms[n].GetMode() != MISSION_MODE){
				bool NpcKilled = rooms[n].IsNpcKilled(msg->npc_num);
				if(!NpcKilled){
					rooms[n].NpcKilled(msg->npc_num);
				}else {
					for(int i = 0; i < 8; i++)
					{
						exp.exp[i] = 0;
						exp.cpMul[i] = 0;
						eleType = eleBase = eleMul = 0;
					}
				}
				bool NoExp = false;
				MySQL MySql;
				for(int i = 0; i < 8; i++)
				{
					int total = exp.exp[i]*exp.cpMul[i];
					if(total){
						MyCharInfo *uInfo = rooms[n].GetUserInfo(i);
						if(uInfo)
						{
							if(Info->usr_slot == i && eleType > 0 && eleType < 5){
								if(Info->UpdateExp(total))
									MySql.GetExp(uInfo->usr_id,total,ElementTypes[eleType],eleBase*eleMul);
								else NoExp = true;
							}else if(Info->UpdateExp(total))
								MySql.GetExp(uInfo->usr_id,total);
							else NoExp = true;
							if(level.getLevel(uInfo->Points) != uInfo->Level){
								MySql.SetLevel(uInfo->usr_id,level.getLevel(uInfo->Points));
								uInfo->Level = level.getLevel(uInfo->Points);
							}
							MySql.UpdateUserInfo(*uInfo);
						}
					}
				}
				if(!NoExp)
					rooms[n].Send(&NpcKillResponseMessage(msg->npc_num,Info->usr_slot,msg->timeStamp,exp,levels,eleType,eleBase,eleMul));
			}else {
				
				if (rooms[n].GetMode() == MISSION_MODE) {
					int eleType = 0, eleBase = 1, eleMul = 0;
					if (Info->Mission % 10 == 5)
					{
						MySQL MySql;
						eleType = (rng100() % 4) + 1;
						eleBase = (rng100() % 5) + 1;
						eleMul = (rng100() % 10) + 1;
						MySql.GetExp(Info->usr_id, 1, ElementTypes[eleType], eleBase*eleMul);
					}
					rooms[n].Send(&MissionNpcKillResponseMessage(msg->npc_num, Info->usr_slot, msg->timeStamp, eleType, eleBase, eleMul, msg->molePoints));
					Info->npc_kills++;
				}else 
					rooms[n].Send(&MissionNpcKillResponseMessage(msg->npc_num, Info->usr_slot, msg->timeStamp, 0, 1, 0, msg->molePoints));
				if(rooms[n].GetMode() == SYMBOL_MODE){
					if(rooms[n].SetSymbolTeam(msg->npc_num,Info->usr_team)){
						//rooms[n].GetResults(Info->usr_team,1);
						rooms[n].SetWinningTeam(Info->usr_team,1);
						int *chars = rooms[n].GetChars();
						if(chars)
							BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),chars),0,true);
						else socket.Disconnect();
					}
				}else if(rooms[n].GetMode() == RACING_MODE){
					if(msg->npc_num == 33)
						rooms[n].SetWinningTeam(Info->usr_team);
				}else if(rooms[n].GetMode() == MOLE_MODE){
					if(rooms[n].AddMolePoints(Info->usr_team,msg->molePoints))
						rooms[n].SetWinningTeam(Info->usr_team);
				}
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleNpcKillMessage." << endl;
	}
}

void GameServer::HandleUpdateQuestProgressMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		LastActivity = clock();
		const QuestProgressMessage* msg = static_cast<const QuestProgressMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			int progress = rooms[n].GetProgress();
			if(rooms[n].UpdateProgress(msg->progress)){
				rooms[n].GetResults(10,1);
				BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
			}
			if(progress < 35 && msg->progress >= 35){
				BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleUpdateQuestProgressMessage." << endl;
	}
}

void GameServer::HandleDeathMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const DeathMessage* msg = static_cast<const DeathMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			if(rooms[n].IsQuestMode()){
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,Info->usr_life));
				Info->usr_life--;
				if(rooms[n].IsAllDead()){
					rooms[n].GetResults(10,2);
					BroadcastMessage(&RoomBasicInfoUpdateMessage(1,n,rooms[n].GetTitle(),rooms[n].GetMode(), rooms[n].GetMap(),rooms[n].GetCapacity(),rooms[n].IsPassworded(), rooms[n].IsPotion(),rooms[n].IsClosed(),rooms[n].IsPremium(),rooms[n].GetChars()),0,true);
				}
			}else if(rooms[n].Is3WinsMode()){
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,Info->usr_life));
				Info->usr_life--;
				if(rooms[n].IsTeamDead(Info->usr_team)){
					int win = Info->usr_team == 10 ? 20 : 10;
					rooms[n].SetWinningTeam(win);
				}
			}else if(rooms[n].IsSingleWinMode()){
				if(rooms[n].GetMode() == SYMBOL_MODE){
					rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,1));
					socket.Send(RoundClearResponseMessage(0,Info->Points,Info->Code,Info->usr_life++));
				}
			}else if(rooms[n].Is5WinsMode()){
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,1));
				socket.Send(RoundClearResponseMessage(0,Info->Points,Info->Code,Info->usr_life--));
				if(Info->usr_life <= 0)
					socket.Send(RoundClearResponseMessage(2,Info->Points,Info->Code,0));
				if(rooms[n].IsKingMode())
				{
					if(rooms[n].GetKing() == msg->slot){
						rooms[n].SetKing(msg->killerslot);
						rooms[n].Send(&NewKingResponseMessage(msg->killerslot));
					}
				}
			}else if(rooms[n].Is3KillsMode()){
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,Info->usr_life=1));
				rooms[n].SetWinningPlayer(msg->slot,msg->killerslot);
			}else if(rooms[n].GetMode() == CRYSTAL_MODE)
			{
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,Info->usr_life=1));
				socket.Send(RoundClearResponseMessage(0,Info->Points,Info->Code,1));
			}else if(rooms[n].GetMode() == FIGHT_CLUB_MODE || rooms[n].GetMode() == TOURNAMENT_MODE)
			{
				rooms[n].LeaveUserTurn(user);
				rooms[n].Send(&DeathResponseMessage(msg->slot,msg->killerslot,0,0,0,Info->usr_life=1));
				socket.Send(RoundClearResponseMessage(2,Info->Points,Info->Code,1));
				Info->usr_ready = 0;
				int slots[8];
				for(int i = 0; i < 8; i++)slots[i] = -1;
				rooms[n].GetTurns(slots);
				for(int i = 0; i < 8; i++){
					if(slots[i] != -1)
						rooms[n].Send(&SpawnResponseMessage(slots,i),i);
				}
			}
			if(msg->killerslot < 8)
			{
				MySQL MySql;
				MySql.AddDeath(Info->usr_id);
				MyCharInfo *info = rooms[n].GetUserInfo(msg->killerslot);
				if(info)
					MySql.AddKill(info->usr_id);
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleDeathMessage." << endl;
	}
}

void GameServer::HandleInGameMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const InGameMessage* msg = static_cast<const InGameMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		if(msg->request == 0xCB){
			MyCharInfo *Info = user->GetInfo();
			int n = Info->usr_room;
			if(n >= 0 && n < MAX_ROOMS){
				int slots[8];
				for(int i = 0; i < 8; i++)slots[i] = -1;
				//if(rooms[n].GetMode() == INFINITY_SURVIVAL || rooms[n].GetMode() == CRYSTAL_MODE || rooms[n].GetMode() == HOKEY_MODE || rooms[n].GetMode() == FIGHT_CLUB_MODE || rooms[n].GetMode() == BM_DEATH_MATCH
				if(rooms[n].GetMode() == INFINITY_SURVIVAL || rooms[n].GetMode() == FIGHT_CLUB_MODE || rooms[n].GetMode() == TOURNAMENT_MODE || rooms[n].GetMode() == BM_DEATH_MATCH)
				{
					/*int *levels = rooms[n].GetLevels();
					for(int i = 0; i < 8; i++)
					if(levels[i])slots[i] = i;*/
					rooms[n].EnterUserTurn(user);
					rooms[n].GetTurns(slots);
					//rooms[n].Send(&SpawnResponseMessage(slots,Info->usr_slot));
					for(int i = 0; i < 8; i++)
						if(slots[i] != -1)
							rooms[n].Send(&SpawnResponseMessage(slots,i),i);
				}else
					rooms[n].GetSlots(slots);
				socket.Send(SpawnResponseMessage(slots,Info->usr_slot));
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleInGameMessage." << endl;
	}
}

void GameServer::HandleReviveMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const ReviveMessage* msg = static_cast<const ReviveMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			if(Info->usr_life >= 0)rooms[n].Send(&ReviveResponseMessage(Info->usr_slot, msg->unk2, msg->unk3));
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleReviveMessage." << endl;
	}
}

void GameServer::HandleSymbolListMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const NpcListMessage* msg = static_cast<const NpcListMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			rooms[n].SetMapType(msg->mapType);
			rooms[n].Send(msg,-1,rooms[n].GetMaster());
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleSymbolListMessage." << endl;
	}
}

void GameServer::HandleBMKOMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const BigMatchNpcDeathMessage* msg = static_cast<const BigMatchNpcDeathMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			if(rooms[n].GetMode() == BM_DEATH_MATCH){
				rooms[n].Send(&BigBattleNpcKoResponseMessage(msg->npcn,msg->killerslot,1,1,-10,0,0,1));
				int team = 0;
				if(msg->npcn >= 9 && msg->npcn <= 24)
					team = 10;
				else if(msg->npcn >= 25 && msg->npcn <= 40)
					team = 20;
				else team = rooms[n].GetUserTeam(msg->npcn);
				rooms[n].SetBBMKills(team,rooms[n].GetBBMKills(team)+1);
				//cout << "Team : " << team << "  :  " << rooms[n].GetBBMKills(team) << endl;
				int maxP = rooms[n].GetTeamReadyPlayersCount(team) + 15;
				int BBMKills = rooms[n].GetBBMKills(team);
				if(BBMKills >= maxP){
					int win = team == 10 ? 20 : 10;
					rooms[n].SetWinningTeam(win);
					rooms[n].SetBBMKills(10,0);
					rooms[n].SetBBMKills(20,0);
					int slots[8];
					rooms[n].GetSlots(slots);
					rooms[n].Send(&SpawnResponseMessage(slots,Info->usr_slot));
				}
			}else if(rooms[n].GetMode() == BB_SURVIVAL){
				if(msg->npcn < 8){
					rooms[n].Send(&RoundClearResponseMessage(Info->usr_slot,Info->Points,Info->Code,5-(--Info->usr_life)));
					rooms[n].Send(&BigBattleNpcKoResponseMessage(msg->npcn,msg->killerid,1,1,-10,3,3,1));
				}else rooms[n].Send(&BigBattleNpcKoResponseMessage(msg->npcn,msg->killerid,1,1,1,1,1,1));
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleBMKOMessage." << endl;
	}
}

void GameServer::HandleBMListMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const BigBattleNpcListMessage* msg = static_cast<const BigBattleNpcListMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			rooms[n].Send(msg,-1,rooms[n].GetMaster());
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleBMListMessage." << endl;
	}
}

void GameServer::HandleMissionCountMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const MissionEntrancePassageCrossMessage* msg = static_cast<const MissionEntrancePassageCrossMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			rooms[n].Send(&MissionPassageCrossResponseMessage(time(0),msg->time));
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleMissionCountMessage." << endl;
	}
}

void GameServer::HandleMissionClearMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const MissionLevelClearMessage* msg = static_cast<const MissionLevelClearMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			if(msg->request == 1){
				rooms[n].SetWinningTeam(10,8);
			}else if(msg->request == 2){
				int newMission = rooms[n].GetNewMission();
				MySQL MySql;
				for(int i = 0; i < rooms[n].GetCapacity(); i++)
				{
					User* rmuser = rooms[n].GetUser(i);
					if(rmuser)
					{
						MyCharInfo *info = rmuser->GetInfo();
						if(info->Mission == (newMission-1)){
							info->Mission = newMission;
								if (newMission % 10 == 5)
									MySql.IncreaseMission(info->usr_id, 2);
								else if(info->npc_kills)
									MySql.IncreaseMission(info->usr_id, 1);
							info->npc_kills = 0;
						}
						info->usr_life = rooms[n].GetUserGameLife(info->questlife);
					}
				}
				rooms[n].Send(&MissionAfterResponseMessage(3,newMission));
			}
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleMissionClearMessage." << endl;
	}
}

void GameServer::HandleCrystalEnterMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const CrystalMessage* msg = static_cast<const CrystalMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS){
			int slots[8];
			rooms[n].GetSlots(slots);
			rooms[n].Send(&SpawnResponseMessage(slots,Info->usr_slot));
			short crystals[] = {2,2,0,0,0,0,0,0};
			rooms[n].Send(&CrystalsResponseMessage(crystals));
			rooms[n].Send(msg);
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleCrystalEnterMessage." << endl;
	}
}

void GameServer::HandleGoalMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const GoalMessage* msg = static_cast<const GoalMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS && Info->usr_mode == SOCCER_MODE){
			int winTeam = rooms[n].AddGoal(msg->goal);
			rooms[n].Send(&GoalResponseMessage(1,rooms[n].GetTeamWins(10),rooms[n].GetTeamWins(20)));
			if(winTeam)
				rooms[n].SetWinningTeam(winTeam);
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleGoalMessage." << endl;
	}
}

void GameServer::HandleHokeyMessage(const Message* message, TcpMessageHandler& socket)
{
	try {
		const HokeyMessage* msg = static_cast<const HokeyMessage*>(message);
		User* user = reinterpret_cast<User*>(socket.GetTag());
		MyCharInfo *Info = user->GetInfo();
		int n = Info->usr_room;
		if(n >= 0 && n < MAX_ROOMS && Info->usr_mode == HOKEY_MODE){
			int winTeam = rooms[n].AddGoal(msg->goal);
			rooms[n].Send(&HokeyResponseMessage(2,rooms[n].GetTeamWins(10),rooms[n].GetTeamWins(20)));
			if(winTeam)
				rooms[n].SetWinningTeam(winTeam);
		}
	}catch(...){
		Log::out(LOG_TYPE_IMPORTANT) << "Exception in HandleHokeyMessage." << endl;
	}
}