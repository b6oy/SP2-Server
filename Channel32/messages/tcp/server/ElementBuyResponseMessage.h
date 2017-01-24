#ifndef __ELEMENTBUYRESPONSEMESSAGE_H__
#define __ELEMENTBUYRESPONSEMESSAGE_H__

#include <Message.h>

class ElementBuyResponseMessage : public Message
{
public:
	int buy; //1
	unsigned __int64 code;
	int water;
	int fire;
	int earth;
	int wind;
    ElementBuyResponseMessage(int buy, unsigned __int64 code, int water, int fire, int earth, int wind);
};

#endif // __ELEMENTBUYRESPONSEMESSAGE_H__
