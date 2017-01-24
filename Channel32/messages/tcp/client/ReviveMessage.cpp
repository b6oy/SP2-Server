#include "ReviveMessage.h"

bool ReviveMessage::IsValid() const
{
    return
        this->size == sizeof(ReviveMessage);
}
