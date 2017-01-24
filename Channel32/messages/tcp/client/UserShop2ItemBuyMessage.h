#ifndef __USERSHOP2ITEMBUYMESSAGE_H__
#define __USERSHOP2ITEMBUYMESSAGE_H__

#include <Message.h>

class UserShop2ItemBuyMessage : public Message
{
public:
    int room;
    char username[16];
    int unk2; //3
    int itm_slot; //0, maybe
    int itm_type;
    int itm_gf;
    int itm_level;
    int itm_skill;

    bool IsValid() const;
};

#endif // __USERSHOP2ITEMBUYMESSAGE_H__
