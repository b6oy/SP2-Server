#include "ShopSellResponseMessage.h"
#include <MessageTypes.h>

ShopSellResponseMessage::ShopSellResponseMessage(int item_slot,  unsigned __int64 Code)
    : Message(sizeof(ShopSellResponseMessage), MESSAGE_TYPE_SHOP_SELL_RESPONSE), item_slot(item_slot), Code(Code)
{
	unk2 = 1;
    unk3 = 0;
    unk4 = 0;
}