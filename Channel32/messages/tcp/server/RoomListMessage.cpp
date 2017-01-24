#include "RoomListMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomListMessage::RoomListMessage(int* roomnumber, char title[22][29], int* mode, int* map, int* maxplayers, bool* bPotion, bool* bPassword, bool* bClosed, int players[22][16])
    : Message(sizeof(RoomListMessage), MESSAGE_TYPE_ROOM_LIST)
{
	for(int i = 0; i < 22; i++){
		unks2[i] = 1;
		unks4[i] = -1;
		bunk[i] = true;
    this->roomnumber[i] = roomnumber[i];
    for(int j = 0; j < 29; j++)
		this->title[i][j] = title[i][j];
    this->mode[i] = mode[i];
    this->map[i] = map[i];
    this->maxplayers[i] = maxplayers[i];
	this->bPassword[i] = bPassword[i];
    this->bPotion[i] = bPotion[i];
    this->bClosed[i] = bClosed[i];
    for(int j = 0; j < 8; j++)
		this->players[i][j] = players[i][j];
	for(int j = 8; j < 16; j++)
		this->players[i][j] = 0;
	}
	zero1 = szero1 = zero2 = 0;
	for(int i = 0; i < 11; i++)unk3[i] = 0;
	for(int i = 0; i < 5; i++)zeros1[i] = 0;
	for(int i = 0; i < 115; i++)unks6[i] = 0;
	unk4 = 0x500000;
}
