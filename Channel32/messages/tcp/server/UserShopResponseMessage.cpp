#include "UserShopResponseMessage.h"
#include <MessageTypes.h>

UserShopResponseMessage::UserShopResponseMessage(char username[13], bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements, int MsgType, int sold)
	: Message(sizeof(UserShopResponseMessage), MESSAGE_TYPE_USER_SHOP_RESPONSE), Code(Code), WaterElements(WaterElements), FireElements(FireElements), EarthElements(EarthElements), WindElements(WindElements), MsgType(MsgType), sold(sold)
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