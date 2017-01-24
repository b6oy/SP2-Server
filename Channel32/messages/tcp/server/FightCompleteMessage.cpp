#include "FightCompleteMessage.h"
#include <MessageTypes.h>

FightCompleteMessage::FightCompleteMessage(int *results, int bluewins, int redwins, int negative_exp, unsigned __int64 Points, unsigned __int64 Code, int winner, int *maxrounds, int unk5, int gainedExp[8], int eleType, int eleBase, int eleMul, int levels[16])
    : Message(sizeof(FightCompleteMessage), MESSAGE_TYPE_FIGHT_COMPLETE_RESPONSE), 
	bluewins(bluewins), redwins(redwins), negative_exp(negative_exp), Points(Points), Code(Code), winner(winner), unk5(unk5)
{
	for(int i = 0; i < 8; i++){
		this->results[i] = results[i];
		if(this->results[i] == 1)
		{
			this->eleType[i] = eleType;
			this->eleBase[i] = eleBase;
		}else {
			this->eleType[i] = 0;
			this->eleBase[i] = 0;
		}
		this->maxrounds[i] = maxrounds[i];
		this->eleMul[i] = eleMul;
		zeros[i] = 0;
		ones3[i] = 1;
		gainedPoints[i] = gainedExp[i];
		gainedCodes[i] = gainedExp[i];
	}
	for (int i = 0; i < 16; i++)
		this->levels[i] = levels[i];
	//redwins = 3;
	//winner = 10;
	dzero = 0;
	unk5 = 0;
}