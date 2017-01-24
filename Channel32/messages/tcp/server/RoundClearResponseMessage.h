#ifndef __ROUNDCLEARRESPONSEMESSAGE_H__
#define __ROUNDCLEARRESPONSEMESSAGE_H__

#include <Message.h>

class RoundClearResponseMessage : public Message
{
public:
    int Result; //maybe
    unsigned __int64 Points;
    unsigned __int64 Code;
    int unk2;
    int death; //1
	int unk4; //-75
	int unk5; //-75

    RoundClearResponseMessage(int Result, unsigned __int64 Points, unsigned __int64 Code, int death);
};

#endif // __ROUNDCLEARRESPONSEMESSAGE_H__
