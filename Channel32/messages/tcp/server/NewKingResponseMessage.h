#ifndef __NEWKINGRESPONSEMESSAGE_H__
#define __NEWKINGRESPONSEMESSAGE_H__

#include <Message.h>

class NewKingResponseMessage : public Message
{
public:
	int slot;

    NewKingResponseMessage(int slot);
};

#endif // __NEWKINGRESPONSEMESSAGE_H__
