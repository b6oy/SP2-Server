#include "OpenUserShopResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

OpenUserShopResponseMessage::OpenUserShopResponseMessage(char username[13], char shopname[15])
    : Message(sizeof(OpenUserShopResponseMessage), MESSAGE_TYPE_OPEN_USER_SHOP_RESPONSE)
{
	strncpy(this->username,username,13);
	strncpy(this->shopname,shopname,15);
	one = 1;
	zero = 0;
	zero1 = 0;
	zero2 = 0;
}