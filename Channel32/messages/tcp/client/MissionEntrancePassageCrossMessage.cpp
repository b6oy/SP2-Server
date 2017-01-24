#include "MissionEntrancePassageCrossMessage.h"

bool MissionEntrancePassageCrossMessage::IsValid() const
{
    return
        this->size == sizeof(MissionEntrancePassageCrossMessage);
}
