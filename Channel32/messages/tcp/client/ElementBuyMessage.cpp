#include "ElementBuyMessage.h"

bool ElementBuyMessage::IsValid() const
{
    return
        this->size == sizeof(ElementBuyMessage);
}
