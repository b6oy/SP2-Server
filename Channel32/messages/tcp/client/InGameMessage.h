#ifndef __INGAMEMESSAGE_H__
#define __INGAMEMESSAGE_H__

#include <Message.h>

class InGameMessage : public Message
{
public:
	int request;
	int zero1;
	int zero2;

    bool IsValid() const;
};

#endif // __INGAMEMESSAGE_H__
