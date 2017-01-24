#include "RoundClearResponseMessage.h"
#include <MessageTypes.h>

RoundClearResponseMessage::RoundClearResponseMessage(int Result, unsigned __int64 Points, unsigned __int64 Code, int death)
    : Message(sizeof(RoundClearResponseMessage), MESSAGE_TYPE_ROUND_CLEAR_RESPONSE), Result(Result),Points(Points),Code(Code),death(death)
{
	unk2 = 0;
	unk4 = 0;
	unk5 = 0;
}