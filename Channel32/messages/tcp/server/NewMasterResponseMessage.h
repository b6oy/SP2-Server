#ifndef __NEWMASTERRESPONSEMESSAGE_H__
#define __NEWMASTERRESPONSEMESSAGE_H__

#include <Message.h>

class NewMasterResponseMessage : public Message
{
public:
	int Slot;
    int unk2;

    NewMasterResponseMessage(int Slot);
};

#endif // __NEWMASTERRESPONSEMESSAGE_H__
