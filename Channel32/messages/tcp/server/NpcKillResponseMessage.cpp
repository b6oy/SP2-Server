#include "NpcKillResponseMessage.h"
#include <MessageTypes.h>

NpcKillResponseMessage::NpcKillResponseMessage(int npc_num, int killerslot, int timeStamp, ExpGain exp, int *levels, int eleType, int eleBase, int eleMul)
    : Message(sizeof(NpcKillResponseMessage), MESSAGE_TYPE_NPC_KILL_RESPONSE),
	npc_num(npc_num), killerslot(killerslot), timeStamp(timeStamp), exp(exp), eleType(eleType), eleBase(eleBase), eleMul(eleMul)
{
	zeros = 0;
	for(int i = 0; i < 16; i++)
		this->levels[i] = levels[i];
}
