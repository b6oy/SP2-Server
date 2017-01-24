#ifndef __DEFAULTCHARACTERCHANGEMESSAGE_H__
#define __DEFAULTCHARACTERCHANGEMESSAGE_H__

#include <Message.h>

class DefaultCharacterChangeMessage : public Message
{
public:
	int unknown1[4];
    int character;

	bool IsValid() const;

};

#endif // __DEFAULTCHARACTERCHANGEMESSAGE_H__
