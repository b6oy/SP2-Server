#include "FieldScrollPickMessage.h"

bool FieldScrollPickMessage::IsValid() const
{
    return
        this->size == sizeof(FieldScrollPickMessage);
}
