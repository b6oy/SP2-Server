#include "CrystalMessage.h"

bool CrystalMessage::IsValid() const
{
    return
        this->size == sizeof(CrystalMessage);
}
