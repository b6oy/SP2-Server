#include "UserShop2AddOrRemoveMessage.h"

bool UserShop2AddOrRemoveMessage::IsValid() const
{
    return
        this->size == sizeof(UserShop2AddOrRemoveMessage);
}
