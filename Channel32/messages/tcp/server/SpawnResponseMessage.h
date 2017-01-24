#ifndef __SPAWNRESPONSEMESSAGE_H__
#define __SPAWNRESPONSEMESSAGE_H__

#include <Message.h>

class SpawnResponseMessage : public Message
{
public:
	int slots[8]; //0 = on; -1 = off
	int slot;

    SpawnResponseMessage(int *slots, int slot);
};

#endif // __SPAWNRESPONSEMESSAGE_H__
