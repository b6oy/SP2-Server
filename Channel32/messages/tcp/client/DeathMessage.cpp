#include "DeathMessage.h"

bool DeathMessage::IsValid() const
{
    return
        this->size == sizeof(DeathMessage);
}
