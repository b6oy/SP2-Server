#ifndef __SEARCHSHOPBUYRESPONSEMESSAGE_H__
#define __SEARCHSHOPBUYRESPONSEMESSAGE_H__

#include <Message.h>

class SearchShopBuyResponseMessage : public Message
{
public:
	bool bMyCard[96];
    int TypeMyCard[96];
    int GFMyCard[96];
    int LevelMyCard[96];
    int SkillMyCard[96];
	unsigned __int64 Code;
	int WaterElements;
    int FireElements;
    int EarthElements;
    int WindElements; 
	int MsgType; //1 = Sold, 2 = Buy, 3 = Close
	int unk2;

    SearchShopBuyResponseMessage(bool *bMyCard, int *TypeMyCard, int *GFMyCard, int *LevelMyCard, int *SkillMyCard, unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements, int MsgType);
};

#endif // __SEARCHSHOPBUYRESPONSEMESSAGE_H__
