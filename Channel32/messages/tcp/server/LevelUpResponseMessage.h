#ifndef __LEVELUPRESPONSEMESSAGE_H__
#define __LEVELUPRESPONSEMESSAGE_H__

#include <Message.h>

class LevelUpResponseMessage : public Message
{
public:
	int unk2; //-1
	int unk3; //7480
	int unk4; //60
	int unk5; //4002
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

	LevelUpResponseMessage(bool bMyCard[96], int TypeMyCard[96], int GFMyCard[96], int LevelMyCard[96], int SkillMyCard[96], unsigned __int64 Code, int WaterElements, int FireElements, int EarthElements, int WindElements);
};

#endif // __LEVELUPRESPONSEMESSAGE_H__
