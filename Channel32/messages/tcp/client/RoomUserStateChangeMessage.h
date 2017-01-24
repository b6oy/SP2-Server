#ifndef __ROOMUSERSTATECHANGEMESSAGE_H__
#define __ROOMUSERSTATECHANGEMESSAGE_H__

#include <Message.h>

class RoomUserStateChangeMessage : public Message
{
public:
    int unk2; //0
    int Character;
    int team; //10
    int Ready; //1
    int GameStart; //2
    int unk3;
    int unk4;

    bool IsValid() const;
};

#endif // __ROOMUSERSTATECHANGEMESSAGE_H__
