#ifndef __UNKNOWNRESPONSEMESSAGE_H__
#define __UNKNOWNRESPONSEMESSAGE_H__

#include <Message.h>

class UnknownResponseMessage : public Message
{
public:
	int zero;
	int one1;
	int one2;
	int two;
	UnknownResponseMessage();
};

#endif // __UNKNOWNRESPONSEMESSAGE_H__
