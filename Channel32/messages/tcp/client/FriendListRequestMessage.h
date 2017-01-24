#ifndef __FRIENDLISTREQUESTMESSAGE_H__
#define __FRIENDLISTREQUESTMESSAGE_H__

#include <Message.h>

class FriendListRequestMessage : public Message
{
public:

    bool IsValid() const;
};

#endif // __FRIENDLISTREQUESTMESSAGE_H__
