#ifndef __LOBBYINFOMESSAGE_H__
#define __LOBBYINFOMESSAGE_H__

#include <Message.h>

class LobbyInfoMessage : public Message
{
public:
    char username[16];
    int level;
    int unk01;
    int unk02;
    bool gender; //1
    bool b2; //1
    bool b3;
    bool b4;
    bool b5; //1
    bool b6; //1
    bool b7;
    bool b8;
    int missionlevel;

    LobbyInfoMessage(char* username, int level, bool gender, int missionlevel, bool b);
};

#endif // __LOBBYINFOMESSAGE_H__
