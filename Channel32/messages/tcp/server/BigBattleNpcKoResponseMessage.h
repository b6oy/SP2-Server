#ifndef __BIGBATTLENPCKORESPONSEMESSAGE_H__
#define __BIGBATTLENPCKORESPONSEMESSAGE_H__

#include <Message.h>

class BigBattleNpcKoResponseMessage : public Message
{
public:
	int npcn;
	int killerslot;
	int unk2; //1
	int multiplier;
	int unk3; //1
	int unk4; //1
	int pointbase;
	int sub; //0xFFFFFFFA
	//unsigned __int64 Points;
	int zzero1;
	int zzero2;
	//int zero;
	//int npcn2;
	int unks[20]; //-1
	int eleType;
	int eleBase;
	int eleMul; //1
	int one; //1
	int zero1;
	int unk5; //-1

    BigBattleNpcKoResponseMessage(int npcn, int killerslot, int multiplier, int pointbase, int sub, int eleType, int eleBase, int eleMul);
};

#endif // __BIGBATTLENPCKORESPONSEMESSAGE_H__
