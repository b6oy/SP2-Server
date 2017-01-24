#ifndef __ROOMUSERKICKMESSAGE_H__
#define __ROOMUSERKICKMESSAGE_H__

#include <Message.h>

class RoomUserKickMessage : public Message
{
public:
    int slot;

    bool IsValid() const;
};

#endif // __ROOMUSERKICKMESSAGE_H__
