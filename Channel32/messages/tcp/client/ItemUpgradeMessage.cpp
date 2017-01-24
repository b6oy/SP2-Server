#include "ItemUpgradeMessage.h"

bool ItemUpgradeMessage::IsValid() const
{
    return
        this->size == sizeof(ItemUpgradeMessage);
}
