#include "FriendListRequestMessage.h"

bool FriendListRequestMessage::IsValid() const
{
    return
        this->size == sizeof(FriendListRequestMessage);
}
