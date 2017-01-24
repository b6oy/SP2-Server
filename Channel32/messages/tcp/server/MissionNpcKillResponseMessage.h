#ifndef __MISSIONNPCKILLRESPONSEMESSAGE_H__
#define __MISSIONNPCKILLRESPONSEMESSAGE_H__

#include <Message.h>

class MissionNpcKillResponseMessage : public Message
{
public:
	int npc_num;
	int killerslot;
	int zeros;
	int timeStamp;
	int cpMul[8];
	int exp[8];
	int levels[16];
	int eleType;
	int eleBase;
	int eleMul;
	int molePoints;
    MissionNpcKillResponseMessage(int npc_num, int killerslot, int timeStamp, int eleType, int eleBase, int eleMul, int molePoints);
};

#endif // __MISSIONNPCKILLRESPONSEMESSAGE_H__
