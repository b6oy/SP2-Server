#include "SearchShopBuyResponseMessage.h"
#include <MessageTypes.h>

SearchShopBuyResponseMessage::SearchShopBuyResponseMessage(bool *bMyCard, int *TypeMyCard, int *GFMyCard, int *LevelMyCard, int *SkillMyCard, unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements, int MsgType)
    : Message(sizeof(SearchShopBuyResponseMessage), MESSAGE_TYPE_SEARCHSHOP_BUY_RESPONSE), Code(Code), WaterElements(WaterElements), FireElements(FireElements), EarthElements(EarthElements), WindElements(WindElements), MsgType(MsgType)
{
	for(int i = 0; i < 96; i++){
    this->bMyCard[i] = bMyCard[i];
    this->TypeMyCard[i] = TypeMyCard[i];
    this->GFMyCard[i] = GFMyCard[i];
    this->LevelMyCard[i] = LevelMyCard[i];
    this->SkillMyCard[i] = SkillMyCard[i];
	}
	unk2 = 0;
}