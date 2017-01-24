#include "TradeStateChangeMessage.h"

bool TradeStateChangeMessage::IsValid() const
{
    return
        this->size == sizeof(TradeStateChangeMessage);
}
