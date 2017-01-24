#ifndef __UDPITEMUPGRADEE_H__
#define __UDPITEMUPGRADEE_H__

#include <Message.h>

class UdpItemUpgrade : public Message
{
public:
	int unk2; //0x005572B4
	int unk3; //0x00372D78
	int unk4; //0x00000058
	int unk5; //0x005572A8
	int one; //1
	char username[16];
	int cardType;
	int cardLevel;

    UdpItemUpgrade(char *username,int cardType, int cardLevel);
};

#endif // __UDPITEMUPGRADEE_H__
