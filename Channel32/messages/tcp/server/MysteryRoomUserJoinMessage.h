#ifndef __MYSTERYROOMUSERJOINMESSAGE_H__
#define __MYSTERYROOMUSERJOINMESSAGE_H__

#include <Message.h>

class MysteryRoomUserJoinMessage : public Message
{
public:
    int unks[4];

    MysteryRoomUserJoinMessage();
};

#endif // __MYSTERYROOMUSERJOINMESSAGE_H__
