#ifndef __USERSHOP2ADDORREMOVEMESSAGE_H__
#define __USERSHOP2ADDORREMOVEMESSAGE_H__

#include <Message.h>

class UserShop2AddOrRemoveMessage : public Message
{
public:
    int unk2; //1 = Sell, 2 = Del
    int unk3; //1, Del = shopid?
    int slot;
    unsigned __int64 price;

    bool IsValid() const;
};

#endif // __USERSHOP2ADDORREMOVEMESSAGE_H__
