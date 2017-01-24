#ifndef __CHATMESSAGEMESSAGE_H__
#define __CHATMESSAGEMESSAGE_H__

#include <Message.h>

class ChatMessageMessage : public Message
{
public:
    int chatType; //0 All, 7 Trade
    char senderId[13];
    char recieverId[13];
    char msg[52];
    short unk2;
    int unk3;
    int unk4; //1
    int unk5;
    int unk6; //0x0018F9C4
    int unk7; //0x74D2FF16

    bool IsValid() const;
};

#endif // __CHATMESSAGEMESSAGE_H__
