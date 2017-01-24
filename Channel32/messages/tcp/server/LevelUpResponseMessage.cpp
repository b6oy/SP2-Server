#include "LevelUpResponseMessage.h"
#include <MessageTypes.h>

LevelUpResponseMessage::LevelUpResponseMessage(bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements)
    : Message(sizeof(LevelUpResponseMessage), MESSAGE_TYPE_LEVELUP_RESPONSE), Code(Code), WaterElements(WaterElements), FireElements(FireElements), EarthElements(EarthElements), WindElements(WindElements)
{
	unk2 = -1;
	unk3 = 7480;
	unk4 = 60;
	unk5 = 4002;

	for (int i = 0; i < 96; i++) {
		this->bMyCard[i] = bMyCard[i];
		this->TypeMyCard[i] = TypeMyCard[i];
		this->GFMyCard[i] = GFMyCard[i];
		this->LevelMyCard[i] = LevelMyCard[i];
		this->SkillMyCard[i] = SkillMyCard[i];
	}
}