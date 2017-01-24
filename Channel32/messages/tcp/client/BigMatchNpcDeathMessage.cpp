#include "BigMatchNpcDeathMessage.h"

bool BigMatchNpcDeathMessage::IsValid() const
{
    return
        this->size == sizeof(BigMatchNpcDeathMessage);
}
