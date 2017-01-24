#include "ScrollUseMessage.h"

bool ScrollUseMessage::IsValid() const
{
    return
        this->size == sizeof(ScrollUseMessage);
}
