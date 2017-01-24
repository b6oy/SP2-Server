#ifndef __ITEMUPGRADERESPONSEMESSAGE_H__
#define __ITEMUPGRADERESPONSEMESSAGE_H__

#include <Message.h>

class ItemUpgradeResponseMessage : public Message
{
public:
    int Slot;
    int UpgradeType; //1 = Lvl, 2 = Skill
    int Upgraded; //1 lvl, 5 skill
    int Level;
    int Skill;
    int Type;
    int GF;
    int userSlot;
    int UpgradeType2;
    int Returned;
    int unk7;
    unsigned __int64 Code;
    int WaterElements;
    int FireElements;
    int EarthElements;
    int WindElements;

    ItemUpgradeResponseMessage(int Slot,int UpgradeType,int Upgraded,int Level,int Skill,int Type,int GF, int userSlot,int UpgradeType2,unsigned __int64 Code,int WaterElements,int FireElements,int EarthElements,int WindElements, int Returned);
};

#endif // __ITEMUPGRADERESPONSEMESSAGE_H__
