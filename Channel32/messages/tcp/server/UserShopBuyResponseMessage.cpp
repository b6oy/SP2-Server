#include "UserShopBuyResponseMessage.h"
#include <MessageTypes.h>

UserShopBuyResponseMessage::UserShopBuyResponseMessage()
	: Message(sizeof(UserShopBuyResponseMessage), MESSAGE_TYPE_USER_SHOP_BUY_RESPONSE)
{
	for(int i = 0; i < 8; i++)
		zeros[i] = 0;
}