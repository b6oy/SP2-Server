#ifndef __SHOPSELLRESPONSEMESSAGE_H__
#define __SHOPSELLRESPONSEMESSAGE_H__

#include <Message.h>

class ShopSellResponseMessage : public Message
{
public:
    int unk2; //1
    int item_slot;
    int unk3;
    unsigned __int64 Code;
    unsigned __int64 unk4;

    ShopSellResponseMessage(int item_slot,  unsigned __int64 Code);
};

#endif // __SHOPSELLRESPONSEMESSAGE_H__
