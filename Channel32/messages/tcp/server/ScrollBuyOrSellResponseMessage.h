#ifndef __SCROLLBUYORSELLRESPONSEMESSAGE_H__
#define __SCROLLBUYORSELLRESPONSEMESSAGE_H__

#include <Message.h>

class ScrollBuyOrSellResponseMessage : public Message
{
public:
    int buy;
    int zero1;
    int unk2; //2
    int scrollid; //0xC
    int zero2;
    unsigned __int64 Code;

    ScrollBuyOrSellResponseMessage(int buy, int unk2, int scrollid, unsigned __int64 Code);
};

#endif // __SCROLLBUYORSELLRESPONSEMESSAGE_H__
