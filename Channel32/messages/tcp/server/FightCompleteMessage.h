#ifndef __FIGHTCOMPLETEMESSAGE_H__
#define __FIGHTCOMPLETEMESSAGE_H__

#include <Message.h>

class FightCompleteMessage : public Message
{
public:
	int results[8]; //1 or -1, 1= Win, 2= Lose
	int bluewins; //maybe
	int redwins;
	int negative_exp;
	unsigned __int64 Points;
	unsigned __int64 Code;
	unsigned __int64 dzero;
	int gainedPoints[8];
	int gainedCodes[8];
	int eleType[8];
	int eleBase[8];
	int eleMul[8]; //1
	int winner; //10
	int maxrounds[8]; //1
	int levels[16]; //-1
	int zeros[8];
	int ones3[8]; //1
	int unk5; //268487332
    FightCompleteMessage(int *results, int bluewins, int redwins, int negative_exp, unsigned __int64 Points, unsigned __int64 Code, int winner, int *maxrounds, int unk5, int gainedExp[8], int eleType, int eleBase, int eleMul, int levels[16]);
};

#endif // __FIGHTCOMPLETEMESSAGE_H__
