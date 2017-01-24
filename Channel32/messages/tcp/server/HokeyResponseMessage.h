#ifndef __HOKEYRESPONSEMESSAGE_H__
#define __HOKEYRESPONSEMESSAGE_H__

#include <Message.h>

class HokeyResponseMessage : public Message
{
public:
	int round; //2
	int bluewins; //1
	int redwins;
	int zero;

    HokeyResponseMessage(int round, int bluewins, int redwins);
};

#endif // __HOKEYRESPONSEMESSAGE_H__
