#ifndef __TRAININGCOMPLETERESPONSEMESSAGE_H__
#define __TRAININGCOMPLETERESPONSEMESSAGE_H__

#include <Message.h>
#include <Item.h>

class TrainingCompleteResponseMessage : public Message
{
public:
	int itemTypes[10];
	int zeros[10]; // skills? just guessing
	int itemRemainingForceDays[10];
	int unk2; // -1
	int unk3; //1005
	int unk4; //1243904

	TrainingCompleteResponseMessage(Item* items);
};

#endif // __TRAININGCOMPLETERESPONSEMESSAGE_H__
