#ifndef __BMNPCLISTMESSAGE_H__
#define __BMNPCLISTMESSAGE_H__

#include <Message.h>

struct BMNpcData
{
	short xPos;
	short yPos;
	int unk1;
	int unk2;
	short unk3;
	short unk4;
	short one;
	short npcType;
	short one2;
	short level;
};

class BigBattleNpcListMessage : public Message
{
public:
    int unk2;
	int unk3;
	BMNpcData npc[41]; //Not sure
	char idc[220];
	int mapType;
	int unk4;
    bool IsValid() const;
};

#endif // __BMNPCLISTMESSAGE_H__
