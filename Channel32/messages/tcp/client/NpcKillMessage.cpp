#include "NpcKillMessage.h"

bool NpcKillMessage::IsValid() const
{
    return
        this->size == sizeof(NpcKillMessage);
}
