#ifndef __DEATHMESSAGE_H__
#define __DEATHMESSAGE_H__

#include <Message.h>

class DeathMessage : public Message
{
public:
    int slot; //Player slot?
    int killerslot;
    int unk3;
    int points;
    int unk4;
    int unk5;
    int unk6;
    int unk7;
    int unk8;
    int unk9;

    bool IsValid() const;
};

#endif // __DEATHMESSAGE_H__
