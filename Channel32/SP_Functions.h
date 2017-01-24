#include "UserList.h"
IOSocket cIOSocket;
LobbyList Lobby;
ExpCalculator ExpCalc(10);
Level level;

void PacketHandler::GetUserInfo()
{
	MySQL MySql;
	MySql.GetUserInfo(Join_Channel_Request->username,Info);
	LobbyInfo.name = Join_Channel_Request->username;
	LobbyInfo.level = Info.Level;
	LobbyInfo.mission = Info.Mission;
	LobbyInfo.gender = Info.gender;
	MySql.GetScrolls(&Info);
}

void PacketHandler::GetUserItems()
{
	MySQL MySql;
	MySql.GetUserItems(Info.usr_id,Join_Channel_PlayerData_Response.bMyCard, Join_Channel_PlayerData_Response.IDMyCard,
		Join_Channel_PlayerData_Response.TypeMyCard, Join_Channel_PlayerData_Response.GFMyCard,
		Join_Channel_PlayerData_Response.LevelMyCard, Join_Channel_PlayerData_Response.SkillMyCard);
	MySql.GetScrolls(&Info);
	MySql.RemoveItems(&Info);
}

void PacketHandler::GetChatMessage(ChatResponse *Chat_Response)
{
	if(Chat_Response->chatType == 0 || Chat_Response->chatType == 7)
		if(Info.usr_room != -1)return;
	if(Chat_Response->chatType == 1)
		if(strcmp(Chat_Response->recieverId, Info.usr_name) != 0)return;
	Chat_Response->state = UpdateState();
	Chat_Response->checksum = cIOSocket.MakeDigest((uint8*)Chat_Response);
	unsigned char msg[0x80];
	memcpy(msg,Chat_Response,0x7C);
	//Encrypt(msg);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetMemoMessage(SendMemoRequest *SMR,char *name)
{
	RcvMemoResponse RMR;
	RMR.size = 0xB0;
	RMR.type = RCV_MEMO_RESPONSE;
	RMR.unk1 = 11036;
	strcpy(RMR.username,name);
	RMR.unk2 = 5;
	RMR.unk3 = SMR->unk3;
	RMR.zero = 0;
	strcpy(RMR.msg,SMR->msg);
	for(int i = 0; i < 8; i++)
		RMR.msg[119-i] = 0;
	RMR.time = 0;
	RMR.unk4 = 0;
	RMR.state = UpdateState();
	RMR.checksum = cIOSocket.MakeDigest((uint8*)&RMR);
	unsigned char *msg = (unsigned char*)&RMR;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetStoredMessages()
{
	MySQL MySql;
	RcvMemoResponse RMR;
	RMR.size = 0xB0;
	RMR.type = RCV_MEMO_RESPONSE;
	RMR.unk1 = 11036;
	RMR.unk2 = 5;
	RMR.unk3 = 0;
	RMR.zero = 0;
	for(int i = 0; i < 8; i++)
		RMR.msg[119-i] = 0;
	RMR.time = 0;
	RMR.unk4 = 0;
	while(MySql.GetStoredMessages(&RMR,Info.usr_name) >= 1){
		RMR.state = UpdateState();
		RMR.checksum = cIOSocket.MakeDigest((uint8*)&RMR);
		RcvMemoResponse tmp = RMR;
		unsigned char *msg = (unsigned char*)&tmp;
		for (int i = 4; i < *(int*)msg; i++)
			msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
		send(msg_socket,(char*)msg,*(int*)msg, 0);
	}
}

void PacketHandler::GetConfirmIdResponse(int response)
{
	ConfirmIdResponse CIR;
	CIR.size = 0x18;
	CIR.type = CONFIRM_ID_RESPONSE;
	CIR.unk1 = 11036;
	CIR.response = response;
	CIR.state = UpdateState();
	CIR.checksum = cIOSocket.MakeDigest((uint8*)&CIR);
	unsigned char *msg = (unsigned char*)&CIR;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetLobbyMessage(LobbyUserInfoResponse* LUIR)
{
	if(Info.usr_room != -1)return;

	LUIR->state = UpdateState();
	LUIR->checksum = cIOSocket.MakeDigest((uint8*)LUIR);
	unsigned char msg[0x40];
	memcpy(msg,LUIR,0x3C);
	//Encrypt((unsigned char*)&msg);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));

	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetNewRoomMessage(LobbyRoomResponse* LRR)
{
	LRR->state = UpdateState();
	LRR->checksum = cIOSocket.MakeDigest((uint8*)LRR);
	unsigned char msg[0xB4];
	memcpy(msg,LRR,0xB0);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));

	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetInRoomPlayerList(RoomPlayerDataResponse* RPDR)
{
	RPDR->state = UpdateState();
	RPDR->checksum = cIOSocket.MakeDigest((uint8*)RPDR);
	unsigned char msg[0x120];
	memcpy(msg,RPDR,0x120);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));

	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetExitRoomResponse()
{
	MySQL MySql;
	memset(&Room_Exit_Response,0,sizeof(RoomExitResponse));
	Room_Exit_Response.size = 0x28;
	Room_Exit_Response.type = ROOM_EXIT_RESPONSE;
	Room_Exit_Response.unk1 = 11036;
	Room_Exit_Response.unk2 = Info.usr_slot;
	strcpy(Room_Exit_Response.username,LobbyInfo.name.c_str());
	RoomList.ProdcastPlayerExitRoom(this,&Room_Exit_Response,Info.usr_room);
	Room_Exit_Response.state = UpdateState();
	Room_Exit_Response.checksum = cIOSocket.MakeDigest((uint8*)&Room_Exit_Response);
	buffer = (unsigned char*)&Room_Exit_Response;
	for (int i = 4; i < *(int*)buffer; i++)
		buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
	send(msg_socket,(char*)buffer,*(int*)buffer, 0);
	HandleList.ProdcastNewRoom(this,0,RoomList.ExitPlayer(Info.usr_room,this),Info.usr_room);
	LastPosition = 0;
	Info.usr_char = Info.DefaultCharacter + Info.premium;
	if(Info.usershop_open)
		MySql.RemoveItems(&Info);
	Info.usershop_open = false;
	Info.usr_room = -1;
	LobbyInfo.level = Info.Level;
	Lobby.Insert(LobbyInfo);
	HandleList.ProdcastLobbyInfo(this,&LobbyInfo,true);
	GenerateResponse(LOBBY_USERINFO_RESPONSE);
	send(msg_socket,(char*)pack,nOfPackets, 0);
	//HandleList.ProdcastRoomUpdate(Info.usr_room);
	GetRoomListResponse();
}

void PacketHandler::GetPlayerDisconnectedResponse()
{
	memset(&Room_Exit_Response,0,sizeof(RoomExitResponse));
	Room_Exit_Response.size = 0x28;
	Room_Exit_Response.type = ROOM_EXIT_RESPONSE;
	Room_Exit_Response.unk1 = 11036;
	Room_Exit_Response.unk2 = Info.usr_slot;
	strcpy(Room_Exit_Response.username,LobbyInfo.name.c_str());
	RoomList.ProdcastPlayerExitRoom(this,&Room_Exit_Response,Info.usr_room);
	HandleList.ProdcastNewRoom(this,0,RoomList.ExitPlayer(Info.usr_room,this),Info.usr_room);
	HandleList.ProdcastLobbyInfo(this,&LobbyInfo,false);
}

void PacketHandler::GetPlayerExitRoomResponse(RoomExitResponse *RER)
{
	RER->state = UpdateState();
	RER->checksum = cIOSocket.MakeDigest((uint8*)RER);
	unsigned char msg[0x2C];
	memcpy(msg,RER,0x2C);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));

	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetInRoomData(RoomPlayerDataResponse* RPDR, bool started)
{
	MySQL MySql;
	RPDR->Character = Info.usr_char;
	strcpy(RPDR->netip,IP);
	if(!LocIP[0])
	{
		MySql.GetUserIP(Info.usr_id,LocIP);
	}
	strcpy(RPDR->locip,LocIP);
	RPDR->level = Info.Level;
	strcpy(RPDR->username,LobbyInfo.name.c_str());
	RPDR->missionlevel = Info.Mission;
	MySql.GetEquipData(Info.usr_id,RPDR);
	RPDR->Ready = Info.usr_ready;
	//RPDR->team = Info.usr_team;
	RPDR->unk4 = 1;
	RPDR->unk9 = 0x01FFFFFF;
	if(Info.usr_team == 0){
		RPDR->team = 10;
		if(Info.usr_mode == DUEL_MODE || Info.usr_mode == DODGE_MODE || Info.usr_mode == TEAMPLAY_MODE || Info.usr_mode == ASSAULT_MODE || Info.usr_mode == SOCCER_MODE)
			switch (Info.usr_slot)
		{
			case 0:
				RPDR->team = 10;
				break;
			case 1:
				RPDR->team = 20;
				break;
		}
		else if(Info.usr_mode == COMMUNITY_MODE)RPDR->team = 0;
		else if(Info.usr_mode == SURVIVAL_MODE || Info.usr_mode == K_SURVIVAL_MODE)RPDR->team = 0;
		else if(Info.usr_mode == LUCKY_3_MODE)RPDR->team = 0;
	}else RPDR->team = Info.usr_team;

	if(started && Info.usr_ready && !Joined)
	{
		Info.alive = true;
		RPDR->Start = 0;
		RPDR->bunk1 = false; //0 = GameStart
		//if(Info.rm_master == Info.usr_slot)RoomList.InitializeLife(Info.usr_room);
		RoomList.InitializeLife(Info.usr_room,Info.usr_slot);
	}
	else {
		RPDR->Start = 2;
		RPDR->bunk1 = false; //0 = GameStart
	}
	if(Info.rm_master != Info.usr_slot)
		RPDR->bunk1 = true;

	//RPDR->unk22 = 0x01010101;
	RPDR->bunk2 = Info.questlife; //QuestLife
	RPDR->bunk3 = 1;
	RPDR->bunk4 = 0; 
	RPDR->scroll[0] = Info.scrolls[0];
	RPDR->scroll[1] = Info.scrolls[1];
	RPDR->scroll[2] = Info.scrolls[2];
	if(Info.usr_ready && Info.usr_mode == COMMUNITY_MODE)
		RoomList.GetOpenShops(this,Info.usr_room);
	Info.usr_team = RPDR->team;
}

void PacketHandler::GetInRoomUpgradeResponse(CardUpgradeResponse *CUR)
{
	CUR->state = UpdateState();
	CUR->checksum = cIOSocket.MakeDigest((uint8*)CUR);
	unsigned char msg[0x5C];
	memcpy(msg,CUR,0x5C);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));

	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetRoomListResponse()
{
	memset(&Room_List_Response,0,sizeof(Room_List_Response));
	Room_List_Response.size = 0xC90;
	Room_List_Response.type = ROOM_LIST_RESPONSE;
	Room_List_Response.unk1 = 11036;
	Room_List_Response.unk4 = 0x500000;
	for(int i = 0; i < 22; i++)Room_List_Response.bunk[i] = true;
	bool more = RoomList.GetRoomList(&Room_List_Response);
	Room_List_Response.state = UpdateState();
	Room_List_Response.checksum = cIOSocket.MakeDigest((uint8*)&Room_List_Response);
	buffer = (unsigned char*)&Room_List_Response;
	for (int i = 4; i < *(int*)buffer; i++)
		buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
	send(msg_socket,(char*)buffer,*(int*)buffer, 0);
}

bool PacketHandler::GetRoomJoinResponse()
{
	memset(&Room_Join_Response,0,sizeof(Room_Join_Response));
	Room_Join_Response.size = 0x7C;
	Room_Join_Response.type = ROOM_JOIN_RESPONSE;
	Room_Join_Response.unk1 = 11036;
	Room_Join_Response.roomnumber = Room_Join_Request->roomnumber;
	Info.usr_room = Room_Join_Request->roomnumber;
	bool join = RoomList.JoinRoom(this,&LobbyInfo.name,Room_Join_Request->roomnumber,Info.gender,Info.Level);
	if(join)RoomList.GetRoomData(&Room_Join_Response);
	Room_Join_Response.unk2 = !join;
	Room_Join_Response.unk05 = 1; //1
	Room_Join_Response.Slot = Info.usr_slot; //1
	Room_Join_Response.unk09 = 1; //0xA
	Room_Join_Response.unk11 = -1;
	Room_Join_Response.unk13 = 1;
	Room_Join_Response.state = UpdateState();
	Room_Join_Response.checksum = cIOSocket.MakeDigest((uint8*)&Room_Join_Response);
	buffer = (unsigned char*)&Room_Join_Response;
	if(join)Lobby.Delete(LobbyInfo.name);
	if(join)HandleList.ProdcastLobbyInfo(this,&LobbyInfo,false);
	if(join)HandleList.ProdcastRoomUpdate(Info.usr_room);
	for (int i = 4; i < *(int*)buffer; i++)
		buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
	send(msg_socket,(char*)buffer,*(int*)buffer, 0);
	//nOfPackets = 0;
	if(join)GenerateResponse(ROOM_PLAYERDATA_RESPONSE);
	return join;
}

void PacketHandler::GetRoomCreateResponse()
{
	memset(&Create_Room_Response.size,0,sizeof(CreateRoomResponse));
	Create_Room_Response.size = 0x6C;
	Create_Room_Response.type = ROOM_CREATE_RESPONSE;
	Create_Room_Response.unk1 = 11036;
	Create_Room_Response.unk01 = 2; //CreateRoom, 0 = no room to create
	RoomList.ValidateRoomNumber(Create_Room_Request->roomnumber);
	Create_Room_Response.roomnumber = Create_Room_Request->roomnumber;
	Info.usr_room = Create_Room_Request->roomnumber;
	strcpy(Create_Room_Response.roomname,Create_Room_Request->roomname);
	Create_Room_Response.mode = Create_Room_Request->mode; //0x1b
	Create_Room_Response.map = Create_Room_Request->map; //0x1b
	strcpy(Create_Room_Response.password,Create_Room_Request->password);
	Create_Room_Response.capacity = Create_Room_Request->capacity;
	Create_Room_Response.allowscrolls = 1; //1
	Create_Room_Response.autoteam = 1; //1
	Create_Room_Response.unk2 = 12;
	Create_Room_Response.character = Info.DefaultCharacter+120; //0x0A
	Create_Room_Response.unk03 = 0x74F59300; //0x74F59300
	Create_Room_Response.maxcardlevel = -1;
	Create_Room_Response.allowcritsheild = -1;
	Create_Room_Response.unk3 = -1; //0
	Create_Room_Response.unk4 = 1; //0
	Create_Room_Response.unk5 = 0; //0
	Create_Room_Response.state = UpdateState();
	Create_Room_Response.checksum = cIOSocket.MakeDigest((uint8*)&Create_Room_Response);
	buffer = (unsigned char*)&Create_Room_Response;
	RoomList.CreateRoom(this,&LobbyInfo.name,&Create_Room_Response,Info.gender,Info.Level);
	HandleList.ProdcastNewRoom(this,&Create_Room_Response,true);
	Lobby.Delete(LobbyInfo.name);
	HandleList.ProdcastLobbyInfo(this,&LobbyInfo,false);
	for (int i = 4; i < *(int*)buffer; i++)
		buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
	send(msg_socket,(char*)buffer,*(int*)buffer, 0);
	GenerateResponse(ROOM_PLAYERDATA_RESPONSE);
}

void PacketHandler::GetInRoomDeathResponse(PlayerKilledResponse *PKR, int life, bool roundclear)
{
	int Points = 200, Killer = PKR->KillerSlot;
	/*
	if(Info.usr_slot == PKR->DeadplayerSlot)
	{
	PKR->GainedPoints = -Points;
	PKR->LostPoints = Points;
	}
	else
	{*/
	PKR->GainedPoints = -Points;
	PKR->LostPoints = Points;
	//}
	PKR->state = UpdateState();
	PKR->checksum = cIOSocket.MakeDigest((uint8*)PKR);
	unsigned char msg[0xB0];
	memcpy(msg,PKR,0xB0);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	if(Info.usr_mode == K_SURVIVAL_MODE)
	{
		NewKing_Response.size = 0x18;
		NewKing_Response.type = IN_GAME_RESPONSE;
		NewKing_Response.unk1 = 11036;
		NewKing_Response.slot = Killer;
		NewKing_Response.state = UpdateState();
		NewKing_Response.checksum = cIOSocket.MakeDigest((uint8*)&NewKing_Response);
		buffer = (unsigned char*)&NewKing_Response;
		for (int i = 4; i < *(int*)buffer; i++)
			buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
		send(msg_socket,(char*)buffer,*(int*)buffer, 0);
		if(Info.usr_slot == PKR->DeadplayerSlot)GetRoundClearResponse(5-life);
	}else if((Info.usr_mode == SURVIVAL_MODE ||  Info.usr_mode == LUCKY_3_MODE)&& Info.usr_slot == PKR->DeadplayerSlot)
		GetRoundClearResponse(5-life);

}

void PacketHandler::GetRoundClearResponse(int death)
{
	RoundClear_Response.size = 0x38;
	RoundClear_Response.type = ROUND_CLEAR_RESPONSE;
	RoundClear_Response.unk1 = 11036;
	RoundClear_Response.Slot = 0;
	RoundClear_Response.Points = Info.Points;
	RoundClear_Response.Code = Info.Code;
	RoundClear_Response.unk2 = 0;
	RoundClear_Response.unk3 = death;
	if(RoundClear_Response.unk3 == 5)RoundClear_Response.Slot = 2;
	RoundClear_Response.unk4 = RoundClear_Response.unk5 = 0;
	RoundClear_Response.state = UpdateState();
	RoundClear_Response.checksum = cIOSocket.MakeDigest((uint8*)&RoundClear_Response);
	buffer = (unsigned char*)&RoundClear_Response;
	for (int i = 4; i < *(int*)buffer; i++)
		buffer[i] = ~((BYTE)(buffer[i] << 3) | (BYTE)(buffer[i] >> 5));
	send(msg_socket,(char*)buffer,*(int*)buffer, 0);
}

void PacketHandler::Trader()
{
	if(strcmp(Trade_Struct.username,Info.usr_name)) //Prevent Items Hijacking
		closesocket(msg_socket);
	Trade_Struct.availableslots = 4;
	Info.TradeProgress = Trade_Struct.confirm;
	int progress = RoomList.SendTradeResponse(&Trade_Struct,Info.usr_room,Info.usr_id);
	Trade_Struct.state = UpdateState();
	Trade_Struct.checksum = cIOSocket.MakeDigest((uint8*)&Trade_Struct);
	unsigned char msg[0x9C];
	memcpy(msg,&Trade_Struct,0x9C);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	if(Info.TradeProgress == 9 && progress == 9)
		CompleteTrade();
}

void PacketHandler::CompleteTrade()
{
	MySQL MySql;
	TradeSuccess_Response.size = 0x6A0;
	TradeSuccess_Response.type = TRADE_SUCCESS_RESPONSE;
	TradeSuccess_Response.unk1 = 11036;
	strcpy(TradeSuccess_Response.username,Info.usr_name);
	MySql.GetUserItems(Info.usr_id,TradeSuccess_Response.bMyCard,0,TradeSuccess_Response.TypeMyCard,TradeSuccess_Response.GFMyCard,TradeSuccess_Response.LevelMyCard,TradeSuccess_Response.SkillMyCard);
	MySql.UpdateUserInfo(Info);
	TradeSuccess_Response.Code = Info.Code;
	TradeSuccess_Response.WaterElements = Info.Water;
	TradeSuccess_Response.FireElements = Info.Fire;
	TradeSuccess_Response.EarthElements = Info.Earth;
	TradeSuccess_Response.WindElements = Info.Wind;
	TradeSuccess_Response.state = UpdateState();
	TradeSuccess_Response.checksum = cIOSocket.MakeDigest((uint8*)&TradeSuccess_Response);
	unsigned char *msg = (unsigned char*)&TradeSuccess_Response;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

int PacketHandler::GetTradeResponse(TradeStruct *TS,int usr_id)
{
	MySQL MySql;
	TS->state = UpdateState();
	TS->checksum = cIOSocket.MakeDigest((uint8*)TS);
	unsigned char msg[0x9C];
	memcpy(msg,TS,0x9C);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	if(Info.TradeProgress == 9 && TS->confirm == 9){
		MySql.IssueTrade(TS,&Trade_Struct,usr_id,Info.usr_id);
		CompleteTrade();
	}
	return Info.TradeProgress;
}

void PacketHandler::GetRoomPlayerData()
{
	if(Joined)
	{
		GetMasterResponse(Info.rm_master);
		Joined = false;
	}
	int x = RoomList.GetInRoomPlayerList(Info.usr_room,pack);
	for(int i = 0; i < x; i++)
	{
		*(int*)(pack+(i*0x118)+0x10) = UpdateState();
		*(int*)(pack+(i*0x118)+0x0C) = cIOSocket.MakeDigest((uint8*)(pack+(i*0x118)));
		Encrypt(pack+(i*0x118));
	}
	send(msg_socket,(char*)pack,x*0x118, 0);
	/*NpcList myList;
	RoomList.GetNpcList(&myList,Info.usr_room);
	if(Info.usr_ready)
	if(myList.size == 0x404)
	{
	myList.state = UpdateState();
	myList.checksum = cIOSocket.MakeDigest((uint8*)&myList);
	unsigned char *msg = (unsigned char*)&myList;
	for (int i = 4; i < *(int*)msg; i++)
	msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	}
	*/
}

void PacketHandler::GetMasterResponse(int mSlot)
{
	Info.rm_master = mSlot;
	NewMasterResponse NMR;
	NMR.size = 0x1C;
	NMR.type = NEW_MASTER_RESPONSE;
	NMR.unk1 = 11036;
	NMR.Slot = mSlot;
	NMR.unk2 = 1;
	NMR.state = UpdateState();
	NMR.checksum = cIOSocket.MakeDigest((uint8*)&NMR);
	unsigned char *msg = (unsigned char*)&NMR;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetNpcList(NpcList *npc)
{
	if(!Info.usr_ready)return;
	npc->state = UpdateState();
	npc->checksum = cIOSocket.MakeDigest((uint8*)npc);
	unsigned char msg[0x408];
	memcpy(msg,npc,0x408);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetLevelUpResponse()
{
	MySQL MySql;
	cout << "LEVEL UP" << endl;
	LevelUp LU;
	LU.size = 0x6A0;
	LU.type = LEVEL_UP;
	LU.unk1 = 11036;
	LU.unk2 = -1;
	LU.unk3 = 7480;
	LU.unk4 = 60;
	LU.unk5 = 4002;
	MySql.GetUserItems(Info.usr_id,LU.bMyCard,0,LU.TypeMyCard,LU.GFMyCard,LU.LevelMyCard,LU.SkillMyCard);
	MySql.UpdateUserInfo(Info);
	LU.Code = Info.Code;
	LU.WaterElements = Info.Water;
	LU.FireElements = Info.Fire;
	LU.EarthElements = Info.Earth;
	LU.WindElements = Info.Wind;
	LU.SkillMyCard[95] = 10;
	LU.state = UpdateState();
	LU.checksum = cIOSocket.MakeDigest((uint8*)&LU);
	unsigned char *msg = (unsigned char*)&LU;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetExpGainResponse(QuestGainResponse *QGR)
{
	MySQL MySql;
	if(Info.usr_slot >= 0 && Info.usr_slot < 8)
	{
		int total = QGR->exp.exp[Info.usr_slot]*QGR->exp.cpMul[Info.usr_slot];
		if(QGR->killerslot == Info.usr_slot && QGR->eleType > 0 && QGR->eleType < 5)
			MySql.GetExp(Info.usr_id,total,ElementTypes[QGR->eleType],QGR->eleBase*QGR->eleMul);
		else MySql.GetExp(Info.usr_id,total);
		Info.Points += total;
		Info.Code += total;
		//if(level.getLevel(Info.Points) != Info.Level)GetLevelUpResponse();
		if(level.getLevel(Info.Points) != Info.Level)
			Info.Level = QGR->unks[Info.usr_slot] = level.getLevel(Info.Points);
	}
	QGR->state = UpdateState();
	QGR->checksum = cIOSocket.MakeDigest((uint8*)QGR);
	unsigned char msg[0xB4];
	memcpy(msg,QGR,0xB4);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetMissionKillResponse(MissionNpcKillResponse *MNKR)
{
	MNKR->state = UpdateState();
	MNKR->checksum = cIOSocket.MakeDigest((uint8*)MNKR);
	unsigned char msg[0xB8];
	memcpy(msg,MNKR,0xB8);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetReviveResponse(ReviveResponse *Revive_Response)
{
	Revive_Response->state = UpdateState();
	Revive_Response->checksum = cIOSocket.MakeDigest((uint8*)Revive_Response);
	unsigned char msg[0x24];
	memcpy(msg,Revive_Response,0x24);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetResultResponse(ResultsResponse* Results_Response)
{
	Info.usr_ready = 0;
	Results_Response->Points = Info.Points;
	Results_Response->Code = Info.Code;
	Results_Response->state = UpdateState();
	Results_Response->checksum = cIOSocket.MakeDigest((uint8*)Results_Response);
	unsigned char msg[0x94];
	memcpy(msg,Results_Response,0x94);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetBigBattleNpcMultiplier()
{
	if(Info.usr_mode != 0x21)return;
	BigBattleNpcMultiplier BBNM;
	BBNM.size = 0x38;
	BBNM.type = BIGBATTLE_NPC_X_RESPONSE;
	BBNM.unk1 = 11036;
	BBNM.x[0] = 2;
	BBNM.x[1] = 5;
	BBNM.x[2] = 10;
	for(int i = 3; i < 36; i++)
		BBNM.x[i] = 1;	
	BBNM.state = UpdateState();
	BBNM.checksum = cIOSocket.MakeDigest((uint8*)&BBNM);
	unsigned char *msg = (unsigned char*)&BBNM;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetJoinResponse2()
{
	RoomJoinResponse2 RJR2;
	RJR2.size = 0x24;
	RJR2.type = ROOM_JOIN_RESPONSE2;
	RJR2.unk1 = 11036;
	for(int i = 0; i < 4; i++)
		RJR2.unks[i] = -1;
	RJR2.state = UpdateState();
	RJR2.checksum = cIOSocket.MakeDigest((uint8*)&RJR2);
	unsigned char *msg = (unsigned char*)&RJR2;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetKickResponse(int slot)
{
	PlayerKickResponse PKR;
	PKR.size = 0x18;
	PKR.type = PLAYER_KICK_RESPONSE;
	PKR.unk1 = 11036;
	PKR.slot = slot;
	PKR.state = UpdateState();
	PKR.checksum = cIOSocket.MakeDigest((uint8*)&PKR);
	unsigned char *msg = (unsigned char*)&PKR;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	if(Info.usr_slot == slot){
		HandleList.ProdcastNewRoom(this,0,RoomList.ExitPlayer(Info.usr_room,this),Info.usr_room);
		Info.usr_char = Info.DefaultCharacter + Info.premium;
		Lobby.Insert(LobbyInfo);
		HandleList.ProdcastLobbyInfo(this,&LobbyInfo,true);
		GenerateResponse(LOBBY_USERINFO_RESPONSE);
		send(msg_socket,(char*)pack,nOfPackets, 0);
		HandleList.ProdcastRoomUpdate(Info.usr_room);
		Info.usr_room = -1;
	}
}

void PacketHandler::GetTitleChange(RoomTitleChangeResponse *RTCR)
{
	RTCR->state = UpdateState();
	RTCR->checksum = cIOSocket.MakeDigest((uint8*)RTCR);
	unsigned char msg[0x38];
	memcpy(msg,RTCR,0x34);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetUserOpenShop(OpenUserShopProd *OUSP)
{
	OUSP->state = UpdateState();
	OUSP->checksum = cIOSocket.MakeDigest((uint8*)OUSP);
	unsigned char msg[0x44];
	memcpy(msg,OUSP,0x44);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

OpenUserShopProd* PacketHandler::GetOpenUserShopProd()
{
	return &OpenUserShop_Prod;
}

void PacketHandler::GetUserCloseShop(CloseUserShopProd *CUSP)
{
	CUSP->state = UpdateState();
	CUSP->checksum = cIOSocket.MakeDigest((uint8*)CUSP);
	memcpy(pack,CUSP,0x6AC);
	for (int i = 4; i < *(int*)pack; i++)
		pack[i] = ~((BYTE)(pack[i] << 3) | (BYTE)(pack[i] >> 5));
	send(msg_socket,(char*)pack,*(int*)pack, 0);
}

void PacketHandler::GetUserShopBuyResponse(int MsgType)
{
	MySQL MySql;
	UserShopBuy_Response.size = 0x34;
	UserShopBuy_Response.type = USER_SHOP_BUY_RESPONSE;
	UserShopBuy_Response.unk1 = 11036;
	for(int i = 0; i < 8; i++)UserShopBuy_Response.zeros[i] = 0;
	UserShopBuy_Response.state = UpdateState();
	UserShopBuy_Response.checksum = cIOSocket.MakeDigest((uint8*)&UserShopBuy_Response);
	unsigned char *msg = (unsigned char*)&UserShopBuy_Response;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	CloseUserShop_Prod.size = 0x6A8;
	CloseUserShop_Prod.type = CLOSE_USER_SHOP_PROD;
	CloseUserShop_Prod.unk1 = 11036;
	strcpy(CloseUserShop_Prod.username,Info.usr_name);
	MySql.GetUserItems(Info.usr_id, CloseUserShop_Prod.bMyCard, 0, CloseUserShop_Prod.TypeMyCard, CloseUserShop_Prod.GFMyCard, CloseUserShop_Prod.LevelMyCard, CloseUserShop_Prod.SkillMyCard);
	MySql.UpdateUserInfo(Info);
	CloseUserShop_Prod.Code = Info.Code;
	CloseUserShop_Prod.WaterElements = Info.Water;
	CloseUserShop_Prod.FireElements = Info.Fire;
	CloseUserShop_Prod.EarthElements = Info.Earth;
	CloseUserShop_Prod.WindElements = Info.Wind;
	CloseUserShop_Prod.MsgType = MsgType;
	if(MsgType == 1)CloseUserShop_Prod.unk2 = 0;
	else CloseUserShop_Prod.unk2 = -1;
	CloseUserShop_Prod.state = UpdateState();
	CloseUserShop_Prod.checksum = cIOSocket.MakeDigest((uint8*)&CloseUserShop_Prod);
	msg = (unsigned char*)&CloseUserShop_Prod;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetRoundCompleteResponse(MissionCompleteResponse *RC)
{
	MissionComplete = *RC;
	MissionComplete.Points = Info.Points;
	MissionComplete.Code = Info.Code;
	MissionComplete.state = UpdateState();
	MissionComplete.checksum = cIOSocket.MakeDigest((uint8*)&MissionComplete);
	unsigned char *msg = (unsigned char*)&MissionComplete;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetAddFriendResponse()
{
	MySQL MySql;
	bool Add = AddFriend_Request->unk2 == 1;
	if(Add){
		if(Info.nFriend < 24)MySql.AddFriend(Info.usr_id,AddFriend_Request->username);
	}else MySql.DeleteFriend(Info.usr_id,AddFriend_Request->username);
	AddFriend_Request->type = ADD_FRIEND_RESPONSE;
	AddFriend_Request->unk2 = 1;
	AddFriend_Request->state = UpdateState();
	AddFriend_Request->checksum = cIOSocket.MakeDigest((uint8*)AddFriend_Request);
	unsigned char *msg = (unsigned char*)AddFriend_Request;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
	RecacheFriends();
	GetFriendListResponse();
}

void PacketHandler::GetFriendListResponse()
{
	MySQL MySql;
	FriendListResponse FLR;
	FLR.size = 0x20C;
	FLR.type = FRIEND_LIST_RESPONSE;
	FLR.unk1 = 11036;
	cout << "Info.nFriend : " << Info.nFriend << endl;
	for(int i = 0; i < 24; i++)
		if(i < Info.nFriend){
			strcpy(FLR.names[i],Info.Friend[i].name);
			if(MySql.IsUserActive(Info.Friend[i].name))FLR.online[i] = FLR.unks[i] = 0;
			else FLR.online[i] = FLR.unks[i] = -1;
		}else {
			FLR.names[i][0] = 0;
			FLR.online[i] = FLR.unks[i] = -1;
		}
		FLR.state = UpdateState();
		FLR.checksum = cIOSocket.MakeDigest((uint8*)&FLR);
		unsigned char *msg = (unsigned char*)&FLR;
		for (int i = 4; i < *(int*)msg; i++)
			msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
		send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::RecacheFriends()
{
	MySQL MySql;
	Info.nFriend = MySql.GetFriendList(Info.usr_id,Info.Friend);
}

void PacketHandler::SendUdpCardLevelUpgrade()
{
	udp_cardlevelup clu;
	clu.size = 0x40;
	clu.type = 0x1128;
	clu.unk1 = 11036;
	clu.unk2 = 0x005572B4;
	clu.unk3 = 0x00372D78;
	clu.unk4 = 0x00000058;
	clu.unk5 = 0x005572A8;
	clu.one = 1;
	strcpy(clu.username,Info.usr_name);
	clu.cardType = Card_Upgrade_Response.Type;
	clu.cardLevel = Card_Upgrade_Response.Level;
	HandleList.ProdcastUpgradeSuccess(&clu);
}

void PacketHandler::udp_Getcardlevelup(udp_cardlevelup *uclu)
{
	uclu->state = UpdateUDPState();
	uclu->checksum = cIOSocket.MakeDigest((uint8*)uclu);
	unsigned char msg[0x44];
	memcpy(msg,uclu,0x40);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	sendto(udp_msg_socket,(char*)msg, *(int*)msg, 0,(struct sockaddr *)&udp_client, sizeof(udp_client));
}

void PacketHandler::GetUseUSResponse()
{
	UseUSResponse US;
	US.size = 0x24;
	US.type = USE_US_RESPONSE;
	US.unk1 = 11036;
	US.unk2 = 4;
	US.unk3 = 1;
	US.slot = UseUS_Request->slot;
	US.price = UseUS_Request->price;
	MySQL MySql;
	MySql.AddItemToShop(&Info,US.slot,US.price);
	US.state = UpdateState();
	US.checksum = cIOSocket.MakeDigest((uint8*)&US);
	unsigned char *msg = (unsigned char*)&US;
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

void PacketHandler::GetGoalResponse(GoalResponse *GR)
{
	GR->state = UpdateState();
	GR->checksum = cIOSocket.MakeDigest((uint8*)GR);
	unsigned char msg[0x2C];
	memcpy(msg,GR,0x28);
	for (int i = 4; i < *(int*)msg; i++)
		msg[i] = ~((BYTE)(msg[i] << 3) | (BYTE)(msg[i] >> 5));
	send(msg_socket,(char*)msg,*(int*)msg, 0);
}

//link to udp
void udpGetUserName(char *name,int room,int slot)
{
	RoomList.GetUserName(name,room,slot);
}