#include "RoomExitResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomExitResponseMessage::RoomExitResponseMessage(int slot, char username[16])
    : Message(sizeof(RoomExitResponseMessage), MESSAGE_TYPE_ROOM_EXIT_RESPONSE), slot(slot)
{
	strcpy(this->username,username);
}
