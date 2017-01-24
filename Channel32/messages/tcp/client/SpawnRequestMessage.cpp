#include "SpawnRequestMessage.h"

bool SpawnRequestMessage::IsValid() const
{
    return
        this->size == sizeof(SpawnRequestMessage);
}
