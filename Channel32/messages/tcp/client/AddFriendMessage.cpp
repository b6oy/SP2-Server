#include "AddFriendMessage.h"

bool AddFriendMessage::IsValid() const
{
    return
        this->size == sizeof(AddFriendMessage);
}
