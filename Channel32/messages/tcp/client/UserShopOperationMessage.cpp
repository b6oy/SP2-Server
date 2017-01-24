#include "UserShopOperationMessage.h"

bool UserShopOperationMessage::IsValid() const
{
    return
        this->size == sizeof(UserShopOperationMessage);
}
