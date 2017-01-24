#include "FindUserMessage.h"

bool FindUserMessage::IsValid() const
{
    return
        this->size == sizeof(FindUserMessage);
}
