#include "UdpHandShake.h"
#include <MessageTypes.h>

UdpHandShake::UdpHandShake(): Message(sizeof(UdpHandShake), MESSAGE_TYPE_UDP_HANDSHAKE)
{
	unk02 = 0x29;
}