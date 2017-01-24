#include "RoomTitleChangeMessage.h"

bool RoomTitleChangeMessage::IsValid() const
{
    return
        this->size == sizeof(RoomTitleChangeMessage);
}
