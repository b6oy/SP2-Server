#ifndef __BIGBATTLENPCMULTIPLIERRESPONSEMESSAGE_H__
#define __BIGBATTLENPCMULTIPLIERRESPONSEMESSAGE_H__

#include <Message.h>

class BigBattleNpcMultiplierResponseMessage : public Message
{
public:
	char x[36];
    BigBattleNpcMultiplierResponseMessage(char x[36]);
};

#endif // __BIGBATTLENPCMULTIPLIERRESPONSEMESSAGE_H__
