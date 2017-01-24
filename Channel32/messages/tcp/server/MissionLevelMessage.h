#ifndef __MISSIONLEVELMESSAGE_H__
#define __MISSIONLEVELMESSAGE_H__

#include <Message.h>

class MissionLevelMessage : public Message
{
public:
    int MissionLevel;
    int unk2; //0

    MissionLevelMessage(int MissionLevel);
};

#endif // __MISSIONLEVELMESSAGE_H__
