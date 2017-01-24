#include "MysteryRoomUserJoinMessage.h"
#include <MessageTypes.h>

MysteryRoomUserJoinMessage::MysteryRoomUserJoinMessage()
    : Message(sizeof(MysteryRoomUserJoinMessage), MESSAGE_TYPE_MYSTERY_ROOM_USER_JOIN)
{
}
