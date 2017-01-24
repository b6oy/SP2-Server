#ifndef __SCROLLUSEMESSAGE_H__
#define __SCROLLUSEMESSAGE_H__

#include <Message.h>

class ScrollUseMessage : public Message
{
public:
    int unk2; //2
    int slot;
    int unk3; //1
    int unk4;

    bool IsValid() const;
};

#endif // __SCROLLUSEMESSAGE_H__
