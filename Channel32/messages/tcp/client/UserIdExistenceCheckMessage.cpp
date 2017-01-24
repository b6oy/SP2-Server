#include "UserIdExistenceCheckMessage.h"

bool UserIdExistenceCheckMessage::IsValid() const
{
    return
        this->size == sizeof(UserIdExistenceCheckMessage);
}
