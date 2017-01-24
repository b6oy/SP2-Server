#include "RoomUserDataRequestMessage.h"

bool RoomUserDataRequestMessage::IsValid() const
{
    return
        this->size == sizeof(RoomUserDataRequestMessage);
}
