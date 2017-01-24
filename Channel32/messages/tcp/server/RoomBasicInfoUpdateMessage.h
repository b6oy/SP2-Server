#ifndef __ROOMBASICINFOUPDATEMESSAGE_H__
#define __ROOMBASICINFOUPDATEMESSAGE_H__

#include <Message.h>

class RoomBasicInfoUpdateMessage : public Message
{
public:
    int Create; //1
    int roomnumber;
    char title[29];
    int mode; //0x1b
    int map; //0x1b
    int unk4; //0x100
    int maxplayers; //8
	bool bPassword;
	bool bPotion;
    bool bClosed;
	bool bPremium;
    int unk6; //0x00551C00
    int unk7; //-1
    int characters[8]; //0x46
    int zeros[13];
    int unk9; //0x100

    RoomBasicInfoUpdateMessage(int Create, int roomnumber, char* title, int mode, int map, int maxplayers, bool bPassword, bool bPotion, bool bClosed, bool bPremium, int* characters);
};

#endif // __ROOMBASICINFOUPDATEMESSAGE_H__
