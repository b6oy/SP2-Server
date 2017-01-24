#ifndef __ROOMJOINMESSAGE_H__
#define __ROOMJOINMESSAGE_H__

#include <Message.h>

class RoomJoinMessage : public Message
{
public:
    int roomnumber;
    char roompw[16];

    bool IsValid() const;
};

#endif // __ROOMJOINMESSAGE_H__
