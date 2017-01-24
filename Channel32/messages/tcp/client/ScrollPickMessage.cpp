#include "ScrollPickMessage.h"

bool ScrollPickMessage::IsValid() const
{
    return
        this->size == sizeof(ScrollPickMessage);
}
