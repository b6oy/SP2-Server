#include "UserShop2SearchMessage.h"

bool UserShop2SearchMessage::IsValid() const
{
    return
        this->size == sizeof(UserShop2SearchMessage);
}
