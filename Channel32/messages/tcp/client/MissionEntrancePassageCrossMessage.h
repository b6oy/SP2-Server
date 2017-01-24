#ifndef __MISSIONENTRANCEPASSAGECROSSMESSAGE_H__
#define __MISSIONENTRANCEPASSAGECROSSMESSAGE_H__

#include <Message.h>

class MissionEntrancePassageCrossMessage : public Message
{
public:
    int zero1;
    int time; //6000
    int zero2;

    bool IsValid() const;
};

#endif // __MISSIONENTRANCEPASSAGECROSSMESSAGE_H__
