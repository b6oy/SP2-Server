#include <FieldValidator.h>
#include "TrainingCompleteMessage.h"

bool TrainingCompleteMessage::IsValid() const
{
    return
        this->size == sizeof(TrainingCompleteMessage);
}