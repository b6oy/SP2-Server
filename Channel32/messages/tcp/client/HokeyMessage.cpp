#include "HokeyMessage.h"

bool HokeyMessage::IsValid() const
{
    return
        this->size == sizeof(HokeyMessage);
}
