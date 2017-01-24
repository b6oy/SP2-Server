#include "ShopBuyResponseMessage.h"
#include <MessageTypes.h>

ShopBuyResponseMessage::ShopBuyResponseMessage(int Bought, bool *bMyCard, int *TypeMyCard, int *GFMyCard, int *LevelMyCard, int *SkillMyCard, unsigned __int64 Slots, unsigned __int64 Code, unsigned __int64 Cash, unsigned __int64 Coins)
    : Message(sizeof(ShopBuyResponseMessage), MESSAGE_TYPE_SHOP_BUY_RESPONSE), Bought(Bought), Slots(Slots), Code(Code), Cash(Cash), Coins(Coins)
{
	for(int i = 0; i < 96; i++){
    this->bMyCard[i] = bMyCard[i];
    this->TypeMyCard[i] = TypeMyCard[i];
    this->GFMyCard[i] = GFMyCard[i];
    this->LevelMyCard[i] = LevelMyCard[i];
    this->SkillMyCard[i] = SkillMyCard[i];
	}
}