#include "ElementBuyResponseMessage.h"
#include <MessageTypes.h>

ElementBuyResponseMessage::ElementBuyResponseMessage(int buy, unsigned __int64 code, int water, int fire, int earth, int wind)
    : Message(sizeof(ElementBuyResponseMessage), MESSAGE_TYPE_ELEMENT_BUY_RESPONSE), buy(buy), code(code), water(water), fire(fire), earth(earth), wind(wind)
{
}