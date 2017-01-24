#ifndef __DEFAULTCHARACTERCHANGERESPONSEMESSAGE_H__
#define __DEFAULTCHARACTERCHANGERESPONSEMESSAGE_H__

#include <Message.h>
#include <ServerEnum.h>

class DefaultCharacterChangeResponseMessage : public Message
{
public:
    int unk2; //1
    int character;
    int unk3;
    int unk4;
    int unk5;

	DefaultCharacterChangeResponseMessage(int character);
};

#endif // __DEFAULTCHARACTERCHANGERESPONSEMESSAGE_H__
