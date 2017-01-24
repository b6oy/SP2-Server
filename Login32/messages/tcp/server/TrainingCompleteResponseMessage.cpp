#include <MessageTypes.h>
#include "TrainingCompleteResponseMessage.h"

TrainingCompleteResponseMessage::TrainingCompleteResponseMessage(Item* items)
	: Message(sizeof(TrainingCompleteResponseMessage), MESSAGE_TYPE_TRAINING_COMPLETE_RESPONSE)
{
	for (int i = 0; i < 10; i++)
	{
		this->itemTypes[i] = items[i].GetType();
		this->itemRemainingForceDays[i] = items[i].GetRemainingForceDays();
		this->zeros[i] = 0;
	}
	this->unk2 = -1;
	this->unk3 = 2000;
	this->unk4 = 0;
}
