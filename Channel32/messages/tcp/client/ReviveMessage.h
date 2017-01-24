#ifndef __REVIVEMESSAGE_H__
#define __REVIVEMESSAGE_H__

#include <Message.h>

class ReviveMessage : public Message
{
public:
    int Slot;
    int unk2;
    int unk3;

    bool IsValid() const;
};

#endif // __REVIVEMESSAGE_H__
