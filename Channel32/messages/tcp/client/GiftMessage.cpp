#include "GiftMessage.h"

bool GiftMessage::IsValid() const
{
    return
        this->size == sizeof(GiftMessage);
}
