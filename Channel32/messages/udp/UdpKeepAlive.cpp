#include "UdpKeepAlive.h"
#include <MessageTypes.h>

UdpKeepAlive::UdpKeepAlive(int clock): Message(sizeof(UdpKeepAlive), MESSAGE_TYPE_UDP_KEEPALIVE), clock(clock)
{
	unk02 = 0x29;
	unk06 = 76373136;
}