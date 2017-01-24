#include "GameShopItemSellMessage.h"

bool GameShopItemSellMessage::IsValid() const
{
    return
        this->size == sizeof(GameShopItemSellMessage);
}
