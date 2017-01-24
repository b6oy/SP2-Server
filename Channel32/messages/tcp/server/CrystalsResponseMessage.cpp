#include "CrystalsResponseMessage.h"
#include <MessageTypes.h>

CrystalsResponseMessage::CrystalsResponseMessage(short crystals[8])
    : Message(sizeof(CrystalsResponseMessage), MESSAGE_TYPE_CRYSTALS_RESPONSE)
{
	for(int i = 0; i < 8; i++)
		this->crystals[i] = crystals[i];
	zero = 0;
	unk1 = 0x00550000;
}