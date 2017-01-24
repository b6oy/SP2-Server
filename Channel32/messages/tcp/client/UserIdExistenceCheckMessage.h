#ifndef __USERIDEXISTENCECHECKMESSAGE_H__
#define __USERIDEXISTENCECHECKMESSAGE_H__

#include <Message.h>

class UserIdExistenceCheckMessage : public Message
{
public:
    char username[16];

    bool IsValid() const;
};

#endif // __USERIDEXISTENCECHECKMESSAGE_H__
