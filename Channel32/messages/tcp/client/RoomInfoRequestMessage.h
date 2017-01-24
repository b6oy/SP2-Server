#ifndef __ROOMINFOREQUESTMESSAGE_H__
#define __ROOMINFOREQUESTMESSAGE_H__

#include <Message.h>

class RoomInfoRequestMessage : public Message
{
public:
    int roomnumber;

    bool IsValid() const;
};

#endif // __ROOMINFOREQUESTMESSAGE_H__
