#ifndef __MEMOMESSAGE_H__
#define __MEMOMESSAGE_H__

#include <Message.h>

class MemoMessage : public Message
{
public:
    char username[16];
    int unk2; //5
    int unk3; //0x000008FD
    int zero;
    char msg[120];

    bool IsValid() const;
};

#endif // __MEMOMESSAGE_H__
