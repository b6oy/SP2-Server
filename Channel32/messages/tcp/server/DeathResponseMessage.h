#ifndef __DEATHRESPONSEMESSAGE_H__
#define __DEATHRESPONSEMESSAGE_H__

#include <Message.h>

class DeathResponseMessage : public Message
{
public:
	int DeadplayerSlot;
    int KillerSlot;
    int PointsMiltiplier;
    int unk2; //3,2
    int unk3; //1
    int unk4; //1
    int unk5; //1
    int unk6; //1
    int unk7; //1
    int unk8; //1
    int GainedPoints;
    int LostPoints;
    int zeros[6];
    int unks[16]; //-1
    int unk01; //maybe kills
    int unk02; //0,1 maybe king
    int unk03; //1
    int canRespawn; //0
    DeathResponseMessage(int DeadplayerSlot, int KillerSlot, int PointsMiltiplier, int GainedPoints, int LostPoints, int canRespawn);
};

#endif // __DEATHRESPONSEMESSAGE_H__
