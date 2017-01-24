#include "TradeSuccessResponseMessage.h"
#include <MessageTypes.h>

TradeSuccessResponseMessage::TradeSuccessResponseMessage(char username[13], bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements)
	: Message(sizeof(TradeSuccessResponseMessage), MESSAGE_TYPE_TRADE_SUCCESS_RESPONSE), Code(Code), WaterElements(WaterElements), FireElements(FireElements), EarthElements(EarthElements), WindElements(WindElements)
{
	for(int i = 0; i < 13; i++)
		this->username[i] = username[i];
	for(int i = 0; i < 96; i++){
		this->bMyCard[i] = bMyCard[i];
		this->TypeMyCard[i] = TypeMyCard[i];
		this->GFMyCard[i] = GFMyCard[i];
		this->LevelMyCard[i] = LevelMyCard[i];
		this->SkillMyCard[i] = SkillMyCard[i];
	}
}