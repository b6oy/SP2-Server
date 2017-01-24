#include "EquipmentChangeMessage.h"

bool EquipmentChangeMessage::IsValid() const
{
    return
        this->size == sizeof(EquipmentChangeMessage);
}
