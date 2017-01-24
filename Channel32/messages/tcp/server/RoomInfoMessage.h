#ifndef __ROOMINFOMESSAGE_H__
#define __ROOMINFOMESSAGE_H__

#include <Message.h>

class RoomInfoMessage : public Message
{
public:
    int unk2; //0
    int plevel[8]; //22, -99
    bool genders[8];
    char username[8][13];
    int zeros[8];
    int master;

    RoomInfoMessage(int* plevel, bool* genders, char** username, int master);
};

#endif // __ROOMINFOMESSAGE_H__
