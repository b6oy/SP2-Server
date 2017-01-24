#ifndef __SCROLLPICKMESSAGE_H__
#define __SCROLLPICKMESSAGE_H__

#include <Message.h>

class ScrollPickMessage : public Message
{
public:
    int zero;
	int scroll;
	int slot;

    bool IsValid() const;
};

#endif // __SCROLLPICKMESSAGE_H__
