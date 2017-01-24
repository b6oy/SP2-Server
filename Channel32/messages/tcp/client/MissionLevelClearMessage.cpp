#include "MissionLevelClearMessage.h"

bool MissionLevelClearMessage::IsValid() const
{
    return
        this->size == sizeof(MissionLevelClearMessage);
}
