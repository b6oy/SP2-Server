#ifndef __UDPFORWARD_H__
#define __UDPFORWARD_H__

#include <Message.h>

class UdpForward : public Message
{
public:
	int room;
	int source;
	int dest;
};

#endif // __UDPFORWARD_H__
