#ifndef __SCROLLBUYORSELLMESSAGE_H__
#define __SCROLLBUYORSELLMESSAGE_H__

#include <Message.h>

class ScrollBuyOrSellMessage : public Message
{
public:
    int buy; //0
    int scrollid; //0xB = bubble

    bool IsValid() const;
};

#endif // __SCROLLBUYORSELLMESSAGE_H__
