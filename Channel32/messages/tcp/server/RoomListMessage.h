#ifndef __ROOMLISTMESSAGE_H__
#define __ROOMLISTMESSAGE_H__

#include <Message.h>

class RoomListMessage : public Message
{
public:
    int roomnumber[22];
    char title[22][29];
    short zero1;
    int mode[22];
    int map[22];
    int unks2[22]; //1
    int maxplayers[22];
    //int zeros[5];
    //short szero;
	bool bPassword[22];
    bool bPotion[22];
    bool bClosed[22];
    short szero1;
    int unk3[11];
    int unks4[22]; //-1,-1
    int players[22][16]; //0x8C
    int unks6[115];
    short zero2;
    bool bunk[22]; //1..
    int zeros1[5];
    int unk4; // 0x500000

    RoomListMessage(int* roomnumber, char title[22][29], int* mode, int* map, int* maxplayers, bool* bPotion, bool* bPassword, bool* bClosed, int players[22][16]);
};

#endif // __ROOMLISTMESSAGE_H__
