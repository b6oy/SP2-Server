#include "ForceChargeMessage.h"

bool ForceChargeMessage::IsValid() const
{
    return
        this->size == sizeof(ForceChargeMessage);
}
