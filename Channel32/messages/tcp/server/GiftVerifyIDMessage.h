#ifndef __GIFTVERIFYIDMESSAGE_H__
#define __GIFTVERIFYIDMESSAGE_H__

#include <Message.h>

class GiftVerifyIDMessage : public Message
{
public:
    int id;

    GiftVerifyIDMessage(int id);
};

#endif // __GIFTVERIFYIDMESSAGE_H__
