#include "ConfirmIDMessage.h"

bool ConfirmIDMessage::IsValid() const
{
    return
        this->size == sizeof(ConfirmIDMessage);
}
