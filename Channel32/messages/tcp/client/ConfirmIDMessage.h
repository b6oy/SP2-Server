#ifndef __CONFIRMIDMESSAGE_H__
#define __CONFIRMIDMESSAGE_H__

#include <Message.h>

class ConfirmIDMessage : public Message
{
public:
    char username[16];

    bool IsValid() const;
};

#endif // __CONFIRMIDMESSAGE_H__
