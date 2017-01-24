#include "NpcListMessage.h"

bool NpcListMessage::IsValid() const
{
    return
        this->size == sizeof(NpcListMessage);
}
