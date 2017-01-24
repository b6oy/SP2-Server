#include "UserInfoRequestMessage.h"

bool UserInfoRequestMessage::IsValid() const
{
    return
        this->size == sizeof(UserInfoRequestMessage);
}
