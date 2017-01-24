#ifndef __GIFTMESSAGE_H__
#define __GIFTMESSAGE_H__

#include <Message.h>

class GiftMessage : public Message
{
public:
    char username[16];
    int gift_type;
    int slot;
    int unk;

    bool IsValid() const;
};

#endif // __GIFTMESSAGE_H__
