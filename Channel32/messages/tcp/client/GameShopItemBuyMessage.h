#ifndef __GAMESHOPITEMBUYMESSAGE_H__
#define __GAMESHOPITEMBUYMESSAGE_H__

#include <Message.h>

class GameShopItemBuyMessage : public Message
{
public:
    int unk2; //-1
    int item;
    int gf;
    int unk3;
    int level;
    int unk5; //1

    bool IsValid() const;
};

#endif // __GAMESHOPITEMBUYMESSAGE_H__
