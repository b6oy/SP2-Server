#include "RoomBasicInfoUpdateMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomBasicInfoUpdateMessage::RoomBasicInfoUpdateMessage(int Create, int roomnumber, char* title, int mode, int map, int maxplayers, bool bPassword, bool bPotion, bool bClosed, bool bPremium, int* characters)
    : Message(sizeof(RoomBasicInfoUpdateMessage), MESSAGE_TYPE_ROOM_BASIC_INFO_UPDATE),
      Create(Create), roomnumber(roomnumber), bPassword(bPassword),bPotion(bPotion),bClosed(bClosed),bPremium(bPremium), mode(mode), map(map), maxplayers(maxplayers)
{
    strcpy(this->title, title);
	for(int i = 0; i < 8; i++)
     this->characters[i] = characters[i];
	
	for(int i = 0; i < 13; i++)zeros[i] = 0;
	unk4 = 1;
	unk7 = -1;
	unk6 = 0;
	unk9 = 0x100;
}
