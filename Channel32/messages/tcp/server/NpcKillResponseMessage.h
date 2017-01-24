#ifndef __NPCKILLRESPONSEMESSAGE_H__
#define __NPCKILLRESPONSEMESSAGE_H__

#include <Message.h>

struct ExpGain
{
	int cpMul[8];
	int exp[8];
};

class NpcKillResponseMessage : public Message
{
public:
	int npc_num;
	int killerslot;
	int zeros;
	int timeStamp;
	ExpGain exp;
	int levels[16];
	int eleType;
	int eleBase;
	int eleMul;
    NpcKillResponseMessage(int npc_num, int killerslot, int timeStamp, ExpGain exp, int *levels, int eleType, int eleBase, int eleMul);
};

#endif // __NPCKILLRESPONSEMESSAGE_H__
