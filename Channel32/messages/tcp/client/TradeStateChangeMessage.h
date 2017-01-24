#ifndef __TRADESTATECHANGEMESSAGE_H__
#define __TRADESTATECHANGEMESSAGE_H__

#include <Message.h>

class TradeStateChangeMessage : public Message
{
public:
    char username[16];
    int confirm; //1 = None, 5 = Cancel, 6 = Add Item, 7 = Config, 9 = Final Confirm, 14 = Trade Fail
    char username2[16];
    int itemID[4];
    unsigned __int64 Code;
    int availableslots;
    int itemType[4];
    int itemGF[4];
    int itemLevel[4];
    int itemSkill[4];
    int unk08;

    bool IsValid() const;
};

#endif // __TRADESTATECHANGEMESSAGE_H__
