#include "ChatMessageMessage.h"

bool ChatMessageMessage::IsValid() const
{
    return
        this->size == sizeof(ChatMessageMessage);
}
