#include "DeathResponseMessage.h"
#include <MessageTypes.h>

DeathResponseMessage::DeathResponseMessage(int DeadplayerSlot, int KillerSlot, int PointsMiltiplier, int GainedPoints, int LostPoints, int canRespawn)
    : Message(sizeof(DeathResponseMessage), MESSAGE_TYPE_DEATH_RESPONSE),
	DeadplayerSlot(DeadplayerSlot), KillerSlot(KillerSlot), PointsMiltiplier(PointsMiltiplier), GainedPoints(GainedPoints), LostPoints(LostPoints), canRespawn(canRespawn)

{
	    unk2 = 3; //3,2
        unk3 = 1; //1
        unk4 = 1; //1
        unk5 = 1; //1
        unk6 = 1; //1
        unk7 = 1; //1
        unk8 = 1; //1
		for(int i = 0; i < 6; i++)zeros[i] = 0;
        for(int i = 0; i < 16; i++)unks[i] = -1;
        unk01 = 2; //maybe kills
        unk02 = 0; //0,1 maybe king
        unk03 = 0; //1
}