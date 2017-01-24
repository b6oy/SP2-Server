#ifndef __ROOMCREATIONMESSAGE_H__
#define __ROOMCREATIONMESSAGE_H__

#include <Message.h>

class RoomCreationMessage : public Message
{
public:
    int roomnumber;
    char roomname[32];
    int mode; //0x1b
    int map; //0x1b
    char password[16];
    int capacity;
    char allowscrolls; //1
    char autoteam; //0
    short unk2; //0
    int maxcardlevel; //-1
    char allowcritsheild;
    char unk3; //0
    char unk4; //0
    char unk5; //0

    bool IsValid() const;
};

#endif // __ROOMCREATIONMESSAGE_H__
