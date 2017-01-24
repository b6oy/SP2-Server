#ifndef __ROOMCREATIONRESPONSEMESSAGE_H__
#define __ROOMCREATIONRESPONSEMESSAGE_H__

#include <Message.h>

class RoomCreationResponseMessage : public Message
{
public:
    int unk01; //2
    int roomnumber;
    char roomname[32];
    int mode; //0x1b
    int map; //0x1b
    char password[16];
    int capacity;
    char allowscrolls; //1
    char autoteam; //1
    short unk2; //0
    int character; //0xA0
    int unk03; //0x74F59300
    int maxcardlevel; //-1
    char allowcritsheild;
    char unk3; //0
    char unk4; //0
    char unk5; //0

    RoomCreationResponseMessage(int status, int roomnumber, char* roomname, int mode, int map, char* password, int capacity, char allowscrolls, char autoteam, int character, int maxcardlevel, char allowcritsheild);
};

#endif // __ROOMCREATIONRESPONSEMESSAGE_H__
