#include <FieldValidator.h>
#include "DefaultCharacterChangeMessage.h"

bool DefaultCharacterChangeMessage::IsValid() const
{
    return
        this->size == sizeof(DefaultCharacterChangeMessage);
	// TODO: is valid character
}
