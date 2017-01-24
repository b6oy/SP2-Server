#ifndef __HOKEYMESSAGE_H__
#define __HOKEYMESSAGE_H__

#include <Message.h>

class HokeyMessage : public Message
{
public:
	char goal;
	char unk1;
	char unk2;
	char unk3;

    bool IsValid() const;
};

#endif // __HOKEYMESSAGE_H__
