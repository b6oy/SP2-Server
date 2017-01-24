#ifndef __SERVERJOINMESSAGE_H__
#define __SERVERJOINMESSAGE_H__

#include <Message.h>

class ServerJoinMessage : public Message
{
public:
    char username[13];
    char unkn[13];
    int unk2; //2
    short unk3; //0x0C10
    int unk4; //0x9D7603C9
    char unkn1[9];
    int pid; //0x1068 PID
    int unk6; //7
    int unk7; //0x13
    int unk8;
    int unk9;

    bool IsValid() const;
};

#endif // __SERVERJOINMESSAGE_H__
