#include "MemoMessage.h"

bool MemoMessage::IsValid() const
{
    return
        this->size == sizeof(MemoMessage);
}
