#ifndef __MISSIONLEVELCLEARMESSAGE_H__
#define __MISSIONLEVELCLEARMESSAGE_H__

#include <Message.h>

class MissionLevelClearMessage : public Message
{
public:
    int request;

    bool IsValid() const;
};

#endif // __MISSIONLEVELCLEARMESSAGE_H__
