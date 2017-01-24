#ifndef __MEMORECEIVEMESSAGE_H__
#define __MEMORECEIVEMESSAGE_H__

#include <Message.h>

class MemoReceiveMessage : public Message
{
public:
    char username[16];
	int unk2; //5
	int unk3; //0x000008FD
	int zero;
	char msg[120];
	int time;
	int unk4;

    MemoReceiveMessage(char username[16], int unk3, char msg[120]);
};

#endif // __MEMORECEIVEMESSAGE_H__
