#ifndef __USERINFOREQUESTMESSAGE_H__
#define __USERINFOREQUESTMESSAGE_H__

#include <Message.h>

class UserInfoRequestMessage : public Message
{
public:
    int unk2;
    char username[16];

    bool IsValid() const;
};

#endif // __USERINFOREQUESTMESSAGE_H__
