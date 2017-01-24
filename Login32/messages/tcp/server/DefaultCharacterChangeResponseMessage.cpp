#include <MessageTypes.h>
#include "DefaultCharacterChangeResponseMessage.h"

DefaultCharacterChangeResponseMessage::DefaultCharacterChangeResponseMessage(int character)
	: Message(sizeof(DefaultCharacterChangeResponseMessage),
	  MESSAGE_TYPE_DEFAULT_CHARACTER_CHANGE_RESPONSE), character(character), unk2(1)
{
}
