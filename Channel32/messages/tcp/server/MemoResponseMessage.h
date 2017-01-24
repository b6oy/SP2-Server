#ifndef __MEMORESPONSEMESSAGE_H__
#define __MEMORESPONSEMESSAGE_H__

#include <Message.h>

class MemoResponseMessage : public Message
{
public:
    int unk2; //1
	char username[16];

    MemoResponseMessage(int unk2, char username[16]);
};

#endif // __MEMORESPONSEMESSAGE_H__
