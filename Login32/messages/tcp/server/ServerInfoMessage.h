#ifndef __SERVERINFOMESSAGE_H__
#define __SERVERINFOMESSAGE_H__

#include <Message.h>

class ServerInfoMessage : public Message
{
public:
	short channelNumber;
    short serverNumber;
    char ip[16];
    int port;
    int serverLoad; //or maybe number of users in the server
	char userType;
    char serverName[17];
    short unk3;
    int unk4;
    int unk5; //zero
    char topGuild[14];
    int unk6; //0x258
    int unk7;
    int unk8;

	ServerInfoMessage(short channelNumber, short serverNumber, char* ip, int port,
		int serverLoad, char* serverName, char* topGuild, char userType);
};

#endif // __SERVERINFOMESSAGE_H__
