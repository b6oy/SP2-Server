#ifndef __BIGMATCHNPCDEATHMESSAGE_H__
#define __BIGMATCHNPCDEATHMESSAGE_H__

#include <Message.h>

class BigMatchNpcDeathMessage : public Message
{
public:
    int killer; //0 = npc, other = player
    int npcn;
    int npclevel;
    int killerslot;
    int killerid;
    int unk3;
    char unk4[20];

    bool IsValid() const;
};

#endif // __BIGMATCHNPCDEATHMESSAGE_H__
