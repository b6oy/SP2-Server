#ifndef __MISSIONPASSAGECROSSRESPONSEMESSAGE_H__
#define __MISSIONPASSAGECROSSRESPONSEMESSAGE_H__

#include <Message.h>

class MissionPassageCrossResponseMessage : public Message
{
public:
	int zero1;
	int timestamp; //0x025A0214
	int time; //6000
	int zero2;

    MissionPassageCrossResponseMessage(int timestamp, int time);
};

#endif // __MISSIONPASSAGECROSSRESPONSEMESSAGE_H__
