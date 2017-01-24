#include "RoomUserKickMessage.h"

bool RoomUserKickMessage::IsValid() const
{
    return
        this->size == sizeof(RoomUserKickMessage);
}
