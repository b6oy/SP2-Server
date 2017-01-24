#ifndef __TRADESUCCESSRESPONSEMESSAGE_H__
#define __TRADESUCCESSRESPONSEMESSAGE_H__

#include <Message.h>

class TradeSuccessResponseMessage : public Message
{
public:
	char username[13];
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
    TradeSuccessResponseMessage(char username[13], bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements);
};

#endif // __TRADESUCCESSRESPONSEMESSAGE_H__
