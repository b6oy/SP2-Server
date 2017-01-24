#ifndef __USERSHOPOPERATIONMESSAGE_H__
#define __USERSHOPOPERATIONMESSAGE_H__

#include <Message.h>

class UserShopOperationMessage : public Message
{
public:
    char id[13];
    char username[13];
    char title[17];
    int unk2;
    int unk3;
    int unk4;
    int shoprequest; //2 = Query, 3 = Buy, 4 = Open, 5 = Close
    int unk01; //-1
    int items[4];
    int itemType[4];
    int itemLevel[4];
    int itemSkill[4];
    int itemGF[4];
    int unk5;
    unsigned __int64 price[4];

    bool IsValid() const;
};

#endif // __USERSHOPOPERATIONMESSAGE_H__
