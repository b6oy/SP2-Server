#include "RoomInfoMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomInfoMessage::RoomInfoMessage(int* plevel, bool* genders, char** username, int master)
    : Message(sizeof(RoomInfoMessage), MESSAGE_TYPE_ROOM_INFO),
      master(master)
{
	unk2 = 0;
	for(int i = 0; i < 8; i++){
    this->plevel[i] = plevel[i];
    this->genders[i] = genders[i];
	for(int j = 0; j < 13; j++)
		this->username[i][j] = username[i][j];
	zeros[i] = 0;
	}
}
