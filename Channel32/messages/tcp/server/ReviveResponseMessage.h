#ifndef __REVIVERESPONSEMESSAGE_H__
#define __REVIVERESPONSEMESSAGE_H__

#include <Message.h>

class ReviveResponseMessage : public Message
{
public:
    int Slot;
    int unk2;
    int unk3;

    ReviveResponseMessage(int Slot, int unk2, int unk3);
};

#endif // __REVIVERESPONSEMESSAGE_H__
