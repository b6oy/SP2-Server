#include "RoomCreationMessage.h"

bool RoomCreationMessage::IsValid() const
{
    return
        this->size == sizeof(RoomCreationMessage);
}
