#ifndef __UDPHANDSHAKE_H__
#define __UDPHANDSHAKE_H__

#include <Message.h>

class UdpHandShake : public Message
{
public:
	int unk01; //0x00373700
	int unk02; //0x29
	int unk03; //0x0012FC74
	int unk04; //0x00510918
	int unk05; //0x0012FC00
	int unk06; //0x0012BC60
	int unk07; //0x00373565
	int unk08; //0x0012BC60

    UdpHandShake();
};

#endif // __UDPHANDSHAKE_H__
