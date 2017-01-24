#include "ScrollBuyOrSellMessage.h"

bool ScrollBuyOrSellMessage::IsValid() const
{
    return
        this->size == sizeof(ScrollBuyOrSellMessage);
}
