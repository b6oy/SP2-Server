#ifndef __AFTERJOINRESPONSEMESSAGE_H__
#define __AFTERJOINRESPONSEMESSAGE_H__

#include <Message.h>

class AfterJoinResponseMessage : public Message
{
public:
    int unk2; //-1
    int unk3; //-1
    int unk4; //-1

    AfterJoinResponseMessage();
};

#endif // __AFTERJOINRESPONSEMESSAGE_H__
