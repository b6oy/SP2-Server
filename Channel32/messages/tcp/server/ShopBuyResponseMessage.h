#ifndef __SHOPBUYRESPONSEMESSAGE_H__
#define __SHOPBUYRESPONSEMESSAGE_H__

#include <Message.h>

class ShopBuyResponseMessage : public Message
{
public:
    int Bought; //1
    bool bMyCard[96];
    int TypeMyCard[96];
    int GFMyCard[96];
    int LevelMyCard[96];
    int SkillMyCard[96];
    unsigned __int64 Slots;
    unsigned __int64 Code;
    unsigned __int64 Cash;
    unsigned __int64 Coins;

    ShopBuyResponseMessage(int Bought, bool *bMyCard, int *TypeMyCard, int *GFMyCard, int *LevelMyCard, int *SkillMyCard, unsigned __int64 Slots, unsigned __int64 Code, unsigned __int64 Cash, unsigned __int64 Coins);
};

#endif // __SHOPBUYRESPONSEMESSAGE_H__
