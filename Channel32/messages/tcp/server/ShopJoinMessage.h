#ifndef __SHOPJOINMESSAGE_H__
#define __SHOPJOINMESSAGE_H__

#include <Message.h>

class ShopJoinMessage : public Message
{
public:
    int cash;

    ShopJoinMessage(int cash);
};

#endif // __SHOPJOINMESSAGE_H__
