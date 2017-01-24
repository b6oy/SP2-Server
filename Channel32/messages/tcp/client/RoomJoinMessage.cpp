#include "RoomJoinMessage.h"

bool RoomJoinMessage::IsValid() const
{
    return
        this->size == sizeof(RoomJoinMessage);
}
