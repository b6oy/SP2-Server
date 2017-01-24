#include "MissionNpcKillResponseMessage.h"
#include <MessageTypes.h>

MissionNpcKillResponseMessage::MissionNpcKillResponseMessage(int npc_num, int killerslot, int timeStamp, int eleType, int eleBase, int eleMul, int molePoints)
    : Message(sizeof(MissionNpcKillResponseMessage), MESSAGE_TYPE_MISSION_NPC_KILL_RESPONSE),
	npc_num(npc_num), killerslot(killerslot), timeStamp(timeStamp), eleType(eleType), eleBase(eleBase), eleMul(eleMul), molePoints(molePoints)
{
	zeros = 0;
	for(int i = 0; i < 8; i++){
		cpMul[i] = 1;
		exp[i] = 0;
		this->levels[i*2] = -1;
		this->levels[i*2+1] = -1;
	}
}
