#ifndef __CRYSTALSRESPONSEMESSAGE_H__
#define __CRYSTALSRESPONSEMESSAGE_H__

#include <Message.h>

class CrystalsResponseMessage : public Message
{
public:
	short crystals[8];
	int zero;
	int unk1; //0x00550000

    CrystalsResponseMessage(short crystals[8]);
};

#endif // __CRYSTALSRESPONSEMESSAGE_H__
