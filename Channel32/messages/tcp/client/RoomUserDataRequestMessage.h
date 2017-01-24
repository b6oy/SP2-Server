#ifndef __ROOMUSERDATAREQUESTMESSAGE_H__
#define __ROOMUSERDATAREQUESTMESSAGE_H__

#include <Message.h>

class RoomUserDataRequestMessage : public Message
{
public:
    int unk2;
    int unk3;
    int unk4;
    int unk5;
    int unk6;
    int unk7;
    int bbbb1; //0x01010101
    int bbbb2; //0x01010101
    int unk8; //0x18B17401

    bool IsValid() const;
};

#endif // __ROOMUSERDATAREQUESTMESSAGE_H__
