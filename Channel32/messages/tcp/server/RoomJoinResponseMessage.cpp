#include "RoomJoinResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomJoinResponseMessage::RoomJoinResponseMessage(int join, int roomnumber, char* title, int mode, int map, int maxp, int allowscrolls, int Slot, int allowcritsheild)
    : Message(sizeof(RoomJoinResponseMessage), MESSAGE_TYPE_ROOM_JOIN_RESPONSE),
     join(join), roomnumber(roomnumber), mode(mode), map(map), maxp(maxp), allowscrolls(allowscrolls), Slot(Slot), allowcritsheild(allowcritsheild)
{
	strcpy(this->title, title);
	unk01 = 0; //0x04A30000
	unk02 = 0; //0x7C96A144
	unk03 = 0; //0x04A307D8
	unk04 = 0; //0x0012FB8C
	//allowscrolls = 1; //0x7C96A101
	unk06 = 0;
	unk07 = 0; //0x04A30000
	unk09 = 1; //0xA
	unk10 = 0;
	unk11 = -1; //-1
	unk12 = 0;
	//allowcritsheild = 0; //0x77DF0001
}
