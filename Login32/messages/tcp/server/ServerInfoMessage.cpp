#include <cstring>

#include "ServerInfoMessage.h"
#include <MessageTypes.h>

ServerInfoMessage::ServerInfoMessage(
	short channelNumber, short serverNumber, char* ip, int port,
	int serverLoad, char* serverName, char* topGuild, char userType)
	: Message(sizeof(ServerInfoMessage), MESSAGE_TYPE_SERVER_INFO),
	  channelNumber(channelNumber), serverNumber(serverNumber),
	  port(port), serverLoad(serverLoad), userType(userType)
{
	strcpy(this->ip, ip);
	strcpy(this->serverName, serverName);
	strcpy(this->topGuild, topGuild);

	unk3 = 0;
    unk4 = 0;
    unk5 = 0;
    unk6 = 0;
    unk7 = 0;
    unk8 = 0;
}
