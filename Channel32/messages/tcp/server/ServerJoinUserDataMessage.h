#ifndef __SERVERJOINUSERDATAMESSAGE_H__
#define __SERVERJOINUSERDATAMESSAGE_H__

#include <Message.h>

class ServerJoinUserDataMessage : public Message
{
public:
    int unk2; //1
    int zero1[6];
    int unk3; //0x10000
    int unk4; //0x220
    int unk5; //1
    int zero2[3];
    int unk6; //1
    int unk7; //0
    unsigned __int64 Points;
    unsigned __int64 unk01;
    unsigned __int64 Points2;
    unsigned __int64 Code;
    unsigned __int64 Coins;
    int level1;
    int level2;
    int scrolls[3];
    int WaterElements;
    int FireElements;
    int EarthElements;
    int WindElements;       //0x98
    int DefaultCharacter; //Maybe
    bool bMyCard[96]; //12x2x4
    int IDMyCard[96];
    int TypeMyCard[96];
    int GFMyCard[96];
    int LevelMyCard[96];
    int SkillMyCard[96];
    int nOfSlots;
    int zero4[2];
    int unk8; //0x32
    int unk9; //0x64
    int unk10; //0xC8
    int unk11; //0x190
    int unk12; //0x320
    int unk13; //0x640
    int unk14; //0x960
    int unk15; //0xC80
    int unk16; //0x1900
    int unk16a; //0x3200
    int unk16b; //0x6400
    int unk16c; //0xC800
    int unk16d; //0x19000
    int unk17; //0x32000
    int unk18; //0x64000
    int unk19; //0xC8000
    int unk20; //0x190000
    int unk21; //0x320000
    int unk22; //0x640000
    int unk23; //0xC80000
    int unk24; //0x1900000
    int unk25; //0x3200000
    int unk26; //0x6400000
    int unk27; //0xC800000
    int unk28; //0x19000000
    int unk29; //0x32000000
    int unk30; //0x64000000
    int unk31; //0xC8000000
    int unk32; //0
    int unk33; //0x90000000
    int unk34; //1
    int unk35; //0x20000000
    int unk36; //3
    int unk37; //0x40000000
    int unk38; //6
    int ChannelType; //3
    int unk39; //7
    int unk40; //0x14
    int unk41; //0
    int VisitBonusCode;
    int VisitBonusElementType;
    int VisitBonusElementNumber;
    int VisitBonusElementMultiple;
    int unk42; //0
    char bunk[7]; //1 0 1 1 1 1 0 0
    int Rank;
    int unk43; //1
    int maxrooms; //0x108
    int munk[8]; //-1
    int unk45; //7
    int zero5[2];
    int unk46; //0x120101

    ServerJoinUserDataMessage(unsigned __int64 Points, unsigned __int64 Points2, unsigned __int64 Code, unsigned __int64 Coins, int level1, int level2, bool gender, int* scrolls, int WaterElements, int FireElements, int EarthElements, int WindElements, int DefaultCharacter, bool* bMyCard, int* IDMyCard, int* TypeMyCard, int* GFMyCard, int* LevelMyCard, int* SkillMyCard, int nOfSlots, int ChannelType, int VisitBonusCode, int VisitBonusElementType, int VisitBonusElementNumber, int VisitBonusElementMultiple, int Rank, int maxrooms);
};

#endif // __SERVERJOINUSERDATAMESSAGE_H__
