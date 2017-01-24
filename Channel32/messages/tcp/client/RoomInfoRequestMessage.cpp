#include "RoomInfoRequestMessage.h"

bool RoomInfoRequestMessage::IsValid() const
{
    return
        this->size == sizeof(RoomInfoRequestMessage);
}
