#ifndef __UDPKEEPALIVE_H__
#define __UDPKEEPALIVE_H__

#include <Message.h>

class UdpKeepAlive : public Message
{
public:
	int unk01; //0x00373700
	int unk02; //0x29
	int unk03; //0x0012FC74
	int unk04; //0x00510918
	int clock; //0x0012FC00
	int unk06; //0x0012BC60

    UdpKeepAlive(int clock);
};

#endif // __UDPKEEPALIVE_H__
