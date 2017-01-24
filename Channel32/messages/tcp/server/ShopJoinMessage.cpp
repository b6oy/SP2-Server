#include "ShopJoinMessage.h"
#include <MessageTypes.h>

ShopJoinMessage::ShopJoinMessage(int cash)
    : Message(sizeof(ShopJoinMessage), MESSAGE_TYPE_SHOP_JOIN_RESPONSE), cash(cash)
{
}