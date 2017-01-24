#ifndef __FORCECHARGEMESSAGE_H__
#define __FORCECHARGEMESSAGE_H__

#include <Message.h>

class ForceChargeMessage : public Message
{
public:
    int item_slot;
	int item_type;
	int gf_slot;
	int gf_type;

    bool IsValid() const;
};

#endif // __FORCECHARGEMESSAGE_H__
