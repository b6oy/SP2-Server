#include "GameShopItemBuyMessage.h"

bool GameShopItemBuyMessage::IsValid() const
{
    return
        this->size == sizeof(GameShopItemBuyMessage);
}
