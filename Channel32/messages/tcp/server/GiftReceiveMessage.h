#ifndef __GIFTRECEIVEMESSAGE_H__
#define __GIFTRECEIVEMESSAGE_H__

#include <Message.h>

class GiftReceiveMessage : public Message
{
public:
    int slot;
	int type;
	int gf;
	int level;
	int skill;

    GiftReceiveMessage(int slot, int type, int gf, int level, int skill);
};

#endif // __GIFTRECEIVEMESSAGE_H__
