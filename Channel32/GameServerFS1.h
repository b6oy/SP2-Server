void GameServer::SendLobbyInfo(TcpMessageHandler& socket)
{
	//lobbyLock.lock();
	User* player = reinterpret_cast<User*>(socket.GetTag());
	MyCharInfo *Info = player->GetInfo();
	for(int i = 0; i < users.size(); i++){
		User* user = users.at(i);
		MyCharInfo uInfo;
		user->GetCharInfo(uInfo);
		if(uInfo.usr_room != -1)continue;
		TcpMessageHandler& usocket = user->GetTcpSocket();
		socket.Send(LobbyInfoMessage(uInfo.usr_name,uInfo.Level,uInfo.gender,uInfo.Mission,true));
		if(usocket.GetTag() != socket.GetTag())usocket.Send(LobbyInfoMessage(Info->usr_name,Info->Level,Info->gender,Info->Mission,true));
	}
	int roomnumber[22], mode[22], map[22], maxplayers[22];
	int players[22][16];
	char title[22][29];
	bool bPotion[22], bPassword[22], bClosed[22];
	for(int i = 0; i < 22; i++){
		roomnumber[i] = -1;
		mode[i] = map[i] = maxplayers[i] = 0;
		for(int j = 0; j < 8; j++)
			players[i][j] = 0;
		bPotion[i] = bPassword[i] = bClosed[i] = false;
		for(int j = 0; j < 29; j++)
			title[i][j] = 0;
	}
	int c = 0;
	for(int i = 0; i < MAX_ROOMS; i++)
	{
		if(rooms[i].IsOpen())
		{
			roomnumber[c] = i;
			mode[c] = rooms[i].GetMode();
			map[c] = rooms[i].GetMap();
			maxplayers[c] = rooms[i].GetCapacity();
			bPotion[c] = rooms[i].IsPotion();
			bClosed[c] = rooms[i].IsClosed();
			bPassword[c] = rooms[i].IsPassworded();
			int *p = rooms[i].GetChars();
			for(int j = 0; j < 8; j++)players[c][j] = p[j];
			strcpy(title[c],rooms[i].GetTitle());
			c++;
			if(c == 22){
				socket.Send(RoomListMessage((int*)roomnumber,title,(int*)mode,(int*)map,(int*)maxplayers,(bool*)bPotion,(bool*)bPassword,(bool*)bClosed,players));
				for(int i = 0; i < 22; i++){
					roomnumber[i] = -1;
					mode[i] = map[i] = maxplayers[i] = 0;
					for(int j = 0; j < 8; j++)
						players[i][j] = 0;
					bPotion[i] = bPassword[i] = bClosed[i] = false;
					for(int j = 0; j < 29; j++)
						title[i][j] = 0;
				}
				c = 0;
			}
		}
	}
	if(c)socket.Send(RoomListMessage((int*)roomnumber,title,(int*)mode,(int*)map,(int*)maxplayers,(bool*)bPotion,(bool*)bPassword,(bool*)bClosed,players));
	//lobbyLock.unlock();
}

void GameServer::SendFriendListResponse(MySQL *MySql, MyCharInfo *Info, TcpMessageHandler& socket)
{
	char names[24][13];
	int online[24]; //-1
	int unks[24]; //-1
	for(int i = 0; i < 24; i++)
		if(i < Info->nFriend){
			strcpy(names[i],Info->Friend[i].name);
			if(MySql->IsUserActive(Info->Friend[i].name))online[i] = unks[i] = 0;
			else online[i] = unks[i] = -1;
		}else {
			names[i][0] = 0;
			online[i] = unks[i] = -1;
		}
		socket.Send(FriendListResponseMessage(names,online,unks));
}

void GameServer::SendExitRoomResponse(TcpMessageHandler& socket)
{
	User* user = reinterpret_cast<User*>(socket.GetTag());
	MyCharInfo *Info = user->GetInfo();
	int roomnumber = Info->usr_room;
	if(roomnumber >= 0 && roomnumber <= MAX_ROOMS){
		if(rooms[roomnumber].GetMode() == COMMUNITY_MODE && Info->usershop_open)
		{
			MySQL MySql;
			MySql.RemoveItems(Info);
			Info->usershop_open = false;
		}else if(rooms[roomnumber].GetMode() == FIGHT_CLUB_MODE)
		{
			rooms[roomnumber].LeaveUserTurn(user);
			int slots[8];
			for(int i = 0; i < 8; i++)slots[i] = -1;
			rooms[roomnumber].GetTurns(slots);
			for(int i = 0; i < 8; i++)
				if(slots[i] != -1)
					rooms[roomnumber].Send(&SpawnResponseMessage(slots,i),i);
		}
		rooms[roomnumber].Send(&RoomExitResponseMessage(Info->usr_slot,Info->usr_name));
		bool bExit = rooms[roomnumber].ExitPlayer(user);
		int *chars = rooms[roomnumber].GetChars();
		if(chars)
			BroadcastMessage(&RoomBasicInfoUpdateMessage(!bExit,roomnumber,rooms[roomnumber].GetTitle(),rooms[roomnumber].GetMode(), rooms[roomnumber].GetMap(),rooms[roomnumber].GetCapacity(),rooms[roomnumber].IsPassworded(),rooms[roomnumber].IsPotion(),rooms[roomnumber].IsClosed(),rooms[roomnumber].IsPremium(),chars),&socket,true);
		else socket.Disconnect();
		SendLobbyInfo(socket);
	}
}

void GameServer::SendExitRoomResponse(User* user)
{
	if(user){
		MyCharInfo *Info = user->GetInfo();
		int roomnumber = Info->usr_room;
		if(roomnumber >= 0 && roomnumber <= MAX_ROOMS){
			if(rooms[roomnumber].GetMode() == COMMUNITY_MODE && Info->usershop_open)
			{
				MySQL MySql;
				MySql.RemoveItems(Info);
				Info->usershop_open = false;
			}else if(rooms[roomnumber].GetMode() == FIGHT_CLUB_MODE)
			{
				rooms[roomnumber].LeaveUserTurn(user);
				int slots[8];
				for(int i = 0; i < 8; i++)slots[i] = -1;
				rooms[roomnumber].GetTurns(slots);
				for(int i = 0; i < 8; i++)
					if(slots[i] != -1)
						rooms[roomnumber].Send(&SpawnResponseMessage(slots,i),i);
			}
			rooms[roomnumber].Send(&RoomExitResponseMessage(Info->usr_slot,Info->usr_name));
			bool bExit = rooms[roomnumber].ExitPlayer(user);
			BroadcastMessage(&RoomBasicInfoUpdateMessage(!bExit,roomnumber,rooms[roomnumber].GetTitle(),rooms[roomnumber].GetMode(), rooms[roomnumber].GetMap(),rooms[roomnumber].GetCapacity(),rooms[roomnumber].IsPassworded(),rooms[roomnumber].IsPotion(),rooms[roomnumber].IsClosed(),rooms[roomnumber].IsPremium(),rooms[roomnumber].GetChars()),0,true);
		}
	}
}