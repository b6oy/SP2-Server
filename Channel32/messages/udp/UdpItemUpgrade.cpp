#include "UdpItemUpgrade.h"
#include <MessageTypes.h>
#include <cstring>

UdpItemUpgrade::UdpItemUpgrade(char *username,int cardType, int cardLevel): 
	Message(sizeof(UdpItemUpgrade), MESSAGE_TYPE_UDP_ITEM_LEVEL_UP), cardType(cardType), cardLevel(cardLevel)
{
	unk2 = 0x005572B4;
	unk3 = 0x00372D78;
	unk4 = 0x00000058;
	unk5 = 0x005572A8;
	one = 1; //7 A-Class player enter channel
	strcpy(this->username,username);
}