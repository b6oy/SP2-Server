#include "RoomUserStateChangeMessage.h"

bool RoomUserStateChangeMessage::IsValid() const
{
    return
        this->size == sizeof(RoomUserStateChangeMessage);
}
