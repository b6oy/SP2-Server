#ifndef __KSSNVERIFICATIONREQUESTMESSAGE_H__
#define __KSSNVERIFICATIONREQUESTMESSAGE_H__

#include <Message.h>

class KssnVerificationRequestMessage : public Message
{
public:
    int id;

    bool IsValid() const;
};

#endif // __KSSNVERIFICATIONREQUESTMESSAGE_H__
