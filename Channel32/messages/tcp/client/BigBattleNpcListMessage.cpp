#include "BigBattleNpcListMessage.h"

bool BigBattleNpcListMessage::IsValid() const
{
    return
        this->size == sizeof(BigBattleNpcListMessage);
}
