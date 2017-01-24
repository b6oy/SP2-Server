#ifndef __GAMESHOPITEMSELLMESSAGE_H__
#define __GAMESHOPITEMSELLMESSAGE_H__

#include <Message.h>

class GameShopItemSellMessage : public Message
{
public:
    int item_slot;

    bool IsValid() const;
};

#endif // __GAMESHOPITEMSELLMESSAGE_H__
