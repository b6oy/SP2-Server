#ifndef __ITEMRECEIVEMESSAGE_H__
#define __ITEMRECEIVEMESSAGE_H__

#include <Message.h>

class ItemReceiveMessage : public Message
{
public:
    char sender[15];
	int level; //7
	int slot; //9
	int zeros[30];
	int lvl; //7
    ItemReceiveMessage(char sender[15], int level, int slot);
};

#endif // __ITEMRECEIVEMESSAGE_H__
