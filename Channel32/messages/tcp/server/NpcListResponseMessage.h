#ifndef __NPCLISTRESPONSEMESSAGE_H__
#define __NPCLISTRESPONSEMESSAGE_H__

#include <Message.h>

class NpcListResponseMessage : public Message
{
public:
	unsigned char levels[36];
    NpcListResponseMessage(short *NpcLevels);
};

#endif // __NPCLISTRESPONSEMESSAGE_H__
