#ifndef __USERSHOPRESPONSEMESSAGE_H__
#define __USERSHOPRESPONSEMESSAGE_H__

#include <Message.h>

class UserShopResponseMessage : public Message
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
	int MsgType; //1 = Sold, 2 = Buy, 3 = Close
	int sold; //-1, 0 = sold
    UserShopResponseMessage(char username[13], bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements, int MsgType, int sold);
};

#endif // __USERSHOPRESPONSEMESSAGE_H__
