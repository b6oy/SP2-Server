#ifndef __ELEMENTCAPTUREDMESSAGE_H__
#define __ELEMENTCAPTUREDMESSAGE_H__

#include <Message.h>

class ElementCapturedMessage : public Message
{
public:
	int slot;
	int unk2; //4
	int eleType;
	int eleBase;
	int eleMul;

    ElementCapturedMessage(int slot, int eleType, int eleBase, int eleMul);
};

#endif // __ELEMENTCAPTUREDMESSAGE_H__
