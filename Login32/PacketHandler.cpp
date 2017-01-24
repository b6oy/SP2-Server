#if 0

#include "PacketHandler.h"
#include "ini.h"

extern CIni config;

IOSocket cIOSocket;
PacketHandler::PacketHandler(SOCKET S)
{
	msg_socket = S;
	nOfPackets = 0;
	State = -1;
}

void PacketHandler::Handler(unsigned char* buf)
{
	nOfPackets = 0;
	Decrypt(buf);

	switch (IdentifyPacketType(buf))
	{
	case LOGIN_REQ:
		Login_Info = (LoginInfo*)buf;
		printf("Client Trying to Login with\nID: %s\nPW: %s\n",Login_Info->username,Login_Info->password);
		GenerateResponse(LOGIN_RESPONSE);
		break;
	case SERVERINFO_REQ:
	case AFTER_SERVERINFO_REQ:
		Server_Info_Request = (ServerInfoRequest*)buf;
		printf("Client Requesting Server Info\n");
		GenerateResponse(SERVERINFO_RESPONSE);
		break;
	case CHANGE_DEFAULT_CHARACTER_REQ:
		Default_Character_Change_Request = (DefaultCharacterChangeRequest*)buf;
		printf("Client Requesting To Change Character\n");
		GenerateResponse(CHANGE_DEFAULT_CHARACTER_RESPONSE);
		break;
	case TRAINING_DONE_REQ:
		printf("TRAINING_DONE_REQ\n");
		GenerateResponse(TRAINING_DONE_RESPONSE);
		break;
	case 10515:
		closesocket(msg_socket);
		break;
	default:
		break;
	}
}

PacketHandler::~PacketHandler()
{
	nOfPackets = 0;
	MySql.Close();
}

int PacketHandler::UpdateState()
{
	return State = abs(((State = (~State + 0x14fb) * 0x1f) >> 16) ^ State);
}

int PacketHandler::IdentifyPacketType(unsigned char* buf)
{
	return *(int*)(buf+4);
}

void PacketHandler::Encrypt(unsigned char *buf)
{
	for (int i = 4; i < buf[0]*nOfPackets; i++)
	{
		if (i == buf[0]) i+= 4;
		buf[i] = ~((BYTE)(buf[i] << 3) | (BYTE)(buf[i] >> 5));
	}


	printf("---- Encrypted Data  ----\n");

	for (int i = 0; i < buf[0]; i++)
	{
		if (i && i%16 == 0)printf("\n");
		if (*(BYTE*)(buf+i) < 0x10)printf("0");
		printf("%x ",(int)*(BYTE*)(buf+i));
	}
	printf("\n");
}

void PacketHandler::Decrypt(unsigned char *buf)
{
	for (int i = 4; i < buf[0]; i++)
		buf[i] = ~((BYTE)(buf[i] >> 3) | (BYTE)(buf[i] << 5));

	printf("---- Decrypted Data  ----\n");
	for (int i = 0; i < buf[0]; i++)
	{
		if (i && i%16 == 0)printf("\n");
		if (*(BYTE*)(buf+i) < 0x10)printf("0");
		printf("%x ",(int)*(BYTE*)(buf+i));
	}
	printf("\n");
}

bool PacketHandler::IsCorrectLogin()
{
	if(usr_id = MySql.Login(Login_Info->username,Login_Info->password))return true;
	return false;
}

void PacketHandler::GetCharInfo(char *charname,MyCharInfo &Info)
{
	if(usr_id)MySql.GetUserInfo(usr_id,Info);
}

void PacketHandler::SetDefaultCharacter(Character DefaultCharacter)
{
	if(usr_id)MySql.SetDefaultCharacter(usr_id,DefaultCharacter);
}

void PacketHandler::GenerateResponse(int ResponsePacketType)
{
	nOfPackets = 1;
	switch (ResponsePacketType)
	{
	case LOGIN_RESPONSE:
		Login_Response.size = 0xA8;
		Login_Response.type = LOGIN_RESPONSE;
		Login_Response.unk1 = 11036;
		Login_Response.state = UpdateState();
		if (!IsCorrectLogin())
		{
			Login_Response.Response = WrongPasswd;
		}
		else if(!MySql.IsUserActive(Login_Info->username))
		{
			Login_Response.Response = CorrectPasswd;
			MyCharInfo UsrInfo;
			GetCharInfo(Login_Info->username,UsrInfo);
			Login_Response.UserType = UsrInfo.UserType;
			*(int*)&Login_Response.DefaultCharacter = UsrInfo.DefaultCharacter;
			Login_Response.UserLevel1 = UsrInfo.Level;
			Login_Response.UserLevel2 = UsrInfo.Level;
			Login_Response.AgeCheck = 1;
			Login_Response.Points = UsrInfo.Points;
			Login_Response.Code = UsrInfo.Code;
			memset(&Login_Response.unk5,0,20*4);
		}else Login_Response.Response = AlreadyIn;
		Login_Response.checksum = cIOSocket.MakeDigest((unsigned char*)&Login_Response);
		buffer = (unsigned char*)&Login_Response;
		break;

	case SERVERINFO_RESPONSE:
		Server_Info[0].size = 0x68;
		Server_Info[0].type = Server_Info_Request->type+1;
		Server_Info[0].unk1 = 11036;
		Server_Info[0].state = UpdateState();


		if (Server_Info_Request->serverType == 1)
		{
			config.SetSection("CHANNEL1");
			Server_Info[0].channel = 1;
			Server_Info[0].servernumber = 0;

			strcpy(Server_Info[0].ip, config.ReadString("ip", "127.0.0.1"));

			Server_Info[0].port = config.ReadInteger("port", 9303);
			Server_Info[0].serverload = 0;
			strcpy(Server_Info[0].chname, config.ReadString("name", "Test ChannelX1"));
			strcpy(Server_Info[0].gname, config.ReadString("guild", " CaptureGuild"));
		}
		else if (Server_Info_Request->serverType == 2)
		{
			config.SetSection("CHANNEL2");
			Server_Info[0].channel = 2;
			Server_Info[0].servernumber = 0;

			strcpy(Server_Info[0].ip, config.ReadString("ip", "127.0.0.1"));

			Server_Info[0].port = config.ReadInteger("port", 9303);
			Server_Info[0].serverload = 0;
			strcpy(Server_Info[0].chname, config.ReadString("name", "Test ChannelX4"));
			strcpy(Server_Info[0].gname, config.ReadString("guild", " CaptureGuild"));
		}
		else if (Server_Info_Request->serverType == 3)
		{
			config.SetSection("CHANNEL3");
			Server_Info[0].channel = 3;
			Server_Info[0].servernumber = 0;

			strcpy(Server_Info[0].ip, config.ReadString("ip", "127.0.0.1"));

			Server_Info[0].port = config.ReadInteger("port", 9303);
			Server_Info[0].serverload = 0;
			strcpy(Server_Info[0].chname, config.ReadString("name", "Test ChannelX10"));
			strcpy(Server_Info[0].gname, config.ReadString("guild", " CaptureGuild"));

			config.SetSection("CHANNEL4");
			Server_Info[1].size = 0x68;
			Server_Info[1].type = Server_Info_Request->type+1;
			Server_Info[1].unk1 = 11036;
			Server_Info[1].state = UpdateState();
			Server_Info[1].channel = 3;
			Server_Info[1].servernumber = 1;

			strcpy(Server_Info[1].ip, config.ReadString("ip", "127.0.0.1"));

			Server_Info[1].port = config.ReadInteger("port", 9303);
			Server_Info[1].serverload = 0;
			strcpy(Server_Info[1].chname, config.ReadString("name", "Test ChannelX10 2"));
			strcpy(Server_Info[1].gname, config.ReadString("guild", " CaptureGuild"));

			Server_Info[1].checksum = cIOSocket.MakeDigest((unsigned char*)&Server_Info[1]);
			nOfPackets = 2;

		}

		Server_Info[0].checksum = cIOSocket.MakeDigest((unsigned char*)&Server_Info[0]);
		buffer = (unsigned char*)&Server_Info;
		break;
	case CHANGE_DEFAULT_CHARACTER_RESPONSE:
		Default_Character_Change_Response.size = 0x1C;
		Default_Character_Change_Response.type = CHANGE_DEFAULT_CHARACTER_RESPONSE;
		Default_Character_Change_Response.unk1 = 11036;
		Default_Character_Change_Response.state = UpdateState();
		Default_Character_Change_Response.unk2 = 1;
		Default_Character_Change_Response.character = Default_Character_Change_Request->character;
		Default_Character_Change_Response.checksum = cIOSocket.MakeDigest((unsigned char*)&Default_Character_Change_Response);
		buffer = (unsigned char*)&Default_Character_Change_Response;
		SetDefaultCharacter(Default_Character_Change_Request->character);
		break;
	case TRAINING_DONE_RESPONSE:
		TrainingDone_Response.size = 0x98;
		TrainingDone_Response.type = TRAINING_DONE_RESPONSE;
		TrainingDone_Response.unk1 = 11036;
		{
		Level level;
		int r = rand() % 4 + 1;
			for(int i = 0; i < 9; i++){
			TrainingDone_Response.items[i] = t_items[i] + (r*10);
			TrainingDone_Response.zeros[i] = 0;
			TrainingDone_Response.gf[i] = 100;
			MySql.InsertNewItem(usr_id,i,TrainingDone_Response.items[i],TrainingDone_Response.gf[i],0,0);
			}
			TrainingDone_Response.items[9] = t_items[9] + r;
			TrainingDone_Response.zeros[9] = 0;
			TrainingDone_Response.gf[9] = 30;
			MySql.InsertNewItem(usr_id,9,TrainingDone_Response.items[9],TrainingDone_Response.gf[9],0,0);
			TrainingDone_Response.unk2 = -1;
			TrainingDone_Response.unk3 = 2000;
			MySql.GetExp(usr_id,TrainingDone_Response.unk3,ElementTypes[r],2000,level.getLevel(TrainingDone_Response.unk3));
		}
		TrainingDone_Response.unk4 = 0;
		TrainingDone_Response.state = UpdateState();
		TrainingDone_Response.checksum = cIOSocket.MakeDigest((unsigned char*)&TrainingDone_Response);
		buffer = (unsigned char*)&TrainingDone_Response;
		break;
	default:
		break;
	}
}

char* PacketHandler::ServerResponse()
{
	Encrypt(buffer);
	return (char*)buffer;
}

int PacketHandler::ServerResponse(unsigned char* buf)
{
	Encrypt(buffer);
	memcpy(buf,buffer,buffer[0]*nOfPackets);

	return nOfPackets;
}

#endif
