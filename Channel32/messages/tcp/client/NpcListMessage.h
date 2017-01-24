#ifndef __NPCLISTMESSAGE_H__
#define __NPCLISTMESSAGE_H__

#include <Message.h>

struct NpcData
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

class NpcListMessage : public Message
{
public:
    int unk2;
	int unk3;
	NpcData npc[33];
	char idc[200];
	int mapType;
	int unk4;
    bool IsValid() const;
};

#endif // __NPCLISTMESSAGE_H__
