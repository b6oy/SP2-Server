#ifndef __USERSHOP2SEARCHMESSAGE_H__
#define __USERSHOP2SEARCHMESSAGE_H__

#include <Message.h>

class UserShop2SearchMessage : public Message
{
public:
    int characteristic;
    int level;
    int searchtype;

    bool IsValid() const;
};

#endif // __USERSHOP2SEARCHMESSAGE_H__
