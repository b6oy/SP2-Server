#ifndef __ITEMUPGRADEMESSAGE_H__
#define __ITEMUPGRADEMESSAGE_H__

#include <Message.h>

class ItemUpgradeMessage : public Message
{
public:
    int Slot;
    int UpgradeType; //1 = Lvl, 2 = Skill
    int unk3; //0

    bool IsValid() const;
};

#endif // __ITEMUPGRADEMESSAGE_H__
