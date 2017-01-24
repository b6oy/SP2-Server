#ifndef __NPCKILLMESSAGE_H__
#define __NPCKILLMESSAGE_H__

#include <Message.h>

class NpcKillMessage : public Message
{
public:
    int npc_num;
    int zero;
    int timeStamp;
    int damages[8];
    short npcType;
    short npcLevel;
    int molePoints;

    bool IsValid() const;
};

#endif // __NPCKILLMESSAGE_H__
