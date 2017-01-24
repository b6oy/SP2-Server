#include "InGameMessage.h"

bool InGameMessage::IsValid() const
{
    return
        this->size == sizeof(InGameMessage);
}
