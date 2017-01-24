#ifndef __FORCECHARGERESPONSEMESSAGE_H__
#define __FORCECHARGERESPONSEMESSAGE_H__

#include <Message.h>

class ForceChargeResponseMessage : public Message
{
public:
	int success; //1
	int item_slot;
	int item_type;
	int gf_slot;

    ForceChargeResponseMessage(int success, int item_slot, int item_type, int gf_slot);
};

#endif // __FORCECHARGERESPONSEMESSAGE_H__
