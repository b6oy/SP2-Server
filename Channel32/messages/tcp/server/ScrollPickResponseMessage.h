#ifndef __SCROLLPICKRESPONSEMESSAGE_H__
#define __SCROLLPICKRESPONSEMESSAGE_H__

#include <Message.h>

class ScrollPickResponseMessage : public Message
{
public:
	int zero;
	int scroll;
	int slot;

    ScrollPickResponseMessage(int scroll, int slot);
};

#endif // __SCROLLPICKRESPONSEMESSAGE_H__
