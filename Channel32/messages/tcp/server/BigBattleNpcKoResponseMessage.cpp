#include "BigBattleNpcKoResponseMessage.h"
#include <MessageTypes.h>

BigBattleNpcKoResponseMessage::BigBattleNpcKoResponseMessage(int npcn, int killerslot, int multiplier, int pointbase, int sub, int eleType, int eleBase, int eleMul)
    : Message(sizeof(BigBattleNpcKoResponseMessage), MESSAGE_TYPE_BIGBATTLE_NPC_KO_RESPONSE), npcn(npcn), killerslot(killerslot), multiplier(multiplier), pointbase(pointbase), sub(sub),eleType(eleType), eleBase(eleBase), eleMul(eleMul)
{
	unk2 = 1;
	unk3 = 1;
	unk4 = 1;
	for(int i = 0; i < 20; i++)unks[i] = -1;
	one = 1;
	zero1 = 7000;
	zzero1 = 0;
	zzero2 = 0;
	unk5 = -1;
	//Points = 1000;
}