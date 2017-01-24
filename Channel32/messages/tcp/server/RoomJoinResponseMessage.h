#ifndef __ROOMJOINRESPONSEMESSAGE_H__
#define __ROOMJOINRESPONSEMESSAGE_H__

#include <Message.h>

class RoomJoinResponseMessage : public Message
{
public:
    int join; //0
    int roomnumber;
    char title[32];
    int mode;
    int map;
    int unk01; //0x04A30000
    int unk02; //0x7C96A144
    int unk03; //0x04A307D8
    int unk04; //0x0012FB8C
    int maxp;
    int allowscrolls; //0x7C96A101
    int unk06;
    int unk07; //0x04A30000
    int Slot; //1
    int unk09; //0xA
    int unk10;
    int unk11; //-1
    int unk12;
    int allowcritsheild; //0x77DF0001

    RoomJoinResponseMessage(int join, int roomnumber, char* title, int mode, int map, int maxp, int allowscrolls, int Slot, int allowcritsheild);
};

#endif // __ROOMJOINRESPONSEMESSAGE_H__
