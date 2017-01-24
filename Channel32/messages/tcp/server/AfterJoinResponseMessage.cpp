#include "AfterJoinResponseMessage.h"
#include <MessageTypes.h>

AfterJoinResponseMessage::AfterJoinResponseMessage()
    : Message(sizeof(AfterJoinResponseMessage), MESSAGE_TYPE_AFTER_ROOM_JOIN_RESPONSE)
{
	unk2 = -1;
	unk3 = -1;
	unk4 = -1;
}