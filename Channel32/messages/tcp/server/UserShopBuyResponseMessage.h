#ifndef __USERSHOPBUYRESPONSEMESSAGE_H__
#define __USERSHOPBUYRESPONSEMESSAGE_H__

#include <Message.h>

class UserShopBuyResponseMessage : public Message
{
public:
	int zeros[8];
    UserShopBuyResponseMessage();
};

#endif // __USERSHOPBUYRESPONSEMESSAGE_H__
