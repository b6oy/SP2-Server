#include "GoalMessage.h"

bool GoalMessage::IsValid() const
{
    return
        this->size == sizeof(GoalMessage);
}
