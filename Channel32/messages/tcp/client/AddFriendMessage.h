#ifndef __ADDFRIENDMESSAGE_H__
#define __ADDFRIENDMESSAGE_H__

#include <Message.h>

class AddFriendMessage : public Message
{
public:
    char username[16];
    int unk2; //1 = Add, 2 = Delete

    bool IsValid() const;
};

#endif // __ADDFRIENDMESSAGE_H__
