#include "UserShop2ItemBuyMessage.h"

bool UserShop2ItemBuyMessage::IsValid() const
{
    return
        this->size == sizeof(UserShop2ItemBuyMessage);
}
