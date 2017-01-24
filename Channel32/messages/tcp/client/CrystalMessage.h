#ifndef __CRYSTALMESSAGE_H__
#define __CRYSTALMESSAGE_H__

#include <Message.h>

class CrystalMessage : public Message
{
public:
    int unk1; //-1
	int ones[4];
	int unk2; //0x58
	int unk3; //0x31C
	int zero[2];
	int unks[2];
	int zero1[2];
	int unks1[4];

    bool IsValid() const;
};

#endif // __CRYSTALMESSAGE_H__
