#ifndef __MISSIONAFTERRESPONSEMESSAGE_H__
#define __MISSIONAFTERRESPONSEMESSAGE_H__

#include <Message.h>

class MissionAfterResponseMessage : public Message
{
public:
	int unk2; //3
	int unk3; //2

    MissionAfterResponseMessage(int unk2, int unk3);
};

#endif // __MISSIONAFTERRESPONSEMESSAGE_H__
