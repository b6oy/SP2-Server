#ifndef __FINDUSERMESSAGE_H__
#define __FINDUSERMESSAGE_H__

#include <Message.h>

class FindUserMessage : public Message
{
public:
    char username[16];

    bool IsValid() const;
};

#endif // __FINDUSERMESSAGE_H__
