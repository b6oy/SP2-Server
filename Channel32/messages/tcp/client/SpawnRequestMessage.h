#ifndef __SPAWNREQUESTMESSAGE_H__
#define __SPAWNREQUESTMESSAGE_H__

#include <Message.h>

class SpawnRequestMessage : public Message
{
public:
    int request;
    int zero1;
    int zero2;

    bool IsValid() const;
};

#endif // __SPAWNREQUESTMESSAGE_H__
