#include "ScrollBuyOrSellResponseMessage.h"
#include <MessageTypes.h>

ScrollBuyOrSellResponseMessage::ScrollBuyOrSellResponseMessage(int buy, int unk2, int scrollid, unsigned __int64 Code)
    : Message(sizeof(ScrollBuyOrSellResponseMessage), MESSAGE_TYPE_BUY_SCROLL_RESPONSE), buy(buy), unk2(unk2), scrollid(scrollid), Code(Code)
{
	zero1 = zero2 = 0;
}