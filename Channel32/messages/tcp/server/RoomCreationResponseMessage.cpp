#include "RoomCreationResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomCreationResponseMessage::RoomCreationResponseMessage(int status, int roomnumber, char* roomname, int mode, int map, char* password, int capacity, char allowscrolls, char autoteam, int character, int maxcardlevel, char allowcritsheild)
    : Message(sizeof(RoomCreationResponseMessage), MESSAGE_TYPE_ROOM_CREATION_RESPONSE),
      roomnumber(roomnumber), mode(mode), map(map), capacity(capacity), allowscrolls(allowscrolls), autoteam(autoteam), character(character), maxcardlevel(maxcardlevel), allowcritsheild(allowcritsheild)
{
	unk01 = status; //2 = ok
	for(int i = 0; i < 32; i++)
		roomname[i] = 0;
	for(int i = 0; i < 16; i++)
		password[i] = 0;
	strcpy(this->roomname, roomname);
	strcpy(this->password, password);
	unk03 = 0;
	unk2 = 0;
	unk3 = -1; //0
	unk4 = 0; //0
	unk5 = 0; //0
}
