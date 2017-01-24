#ifndef __SERVERJOINRESPONSEMESSAGE_H__
#define __SERVERJOINRESPONSEMESSAGE_H__

#include <Message.h>

class ServerJoinResponseMessage : public Message
{
public:
    int unk2; //0x2CF
    int unk3; //0x2CA
    int unk4; //0
    int unk5; //1
    int unk6;
    int unk7;
    int unk8;
    int unk9; //0x6D15D3
    int unk10; //0
    int unk11; //0
    int unk12; //0x78020F00

    ServerJoinResponseMessage();
};

#endif // __SERVERJOINRESPONSEMESSAGE_H__
