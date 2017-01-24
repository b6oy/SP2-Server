#ifndef __SERVERENUM_H__
#define __SERVERENUM_H__

#include <time.h>
#include "rng.h"

#define COMMUNITY_MODE		0x01
#define TEAMPLAY_MODE		0x03
#define SURVIVAL_MODE		0x04
#define DUEL_MODE			0x05
#define LUCKY_3_MODE		0x06
#define ASSAULT_MODE		0x07
#define SOCCER_MODE			0x08
#define KING_SLAYER			0x09
#define MAGIC_LUCKY_3		0x0A
#define DUNGEON_QUEST_1		0x0B
#define DUNGEON_QUEST_2		0x0C
#define DUNGEON_QUEST_3		0x0D
#define DUNGEON_QUEST_4		0x0E
#define FIGHT_CLUB_MODE		0x0F
#define TOURNAMENT_MODE		0x10
#define DUNGEON_QUEST_5		0x11
#define FOREST_QUEST_1		0x12
#define FOREST_QUEST_2		0x13
#define FOREST_QUEST_3		0x14
#define FOREST_QUEST_4		0x15
#define FOREST_QUEST_5		0x16
#define FLAME_QUEST_1		0x17
#define FLAME_QUEST_2		0x18
#define FLAME_QUEST_3		0x19
#define FLAME_QUEST_4		0x1A
#define FLAME_QUEST_5		0x1B
#define DODGE_MODE			0x1C
#define MOLE_MODE			0x1D
#define RACING_MODE			0x1E
#define SYMBOL_MODE			0x1F
#define K_SURVIVAL_MODE		0x20
#define BB_SURVIVAL			0x21
#define BM_AUTO				0x22
#define BM_DEATH_MATCH		0x23
#define MISSION_TRAINING	0x2E
#define MISSION_MODE		0x2F
#define CRYSTAL_MODE		0x28
#define HOKEY_MODE			0x29
#define INFINITY_SURVIVAL	0x30
#define INFINITY_SYMBOL		0x31
#define INFINITY_KING		0x32
#define HERO_MODE			0x33


enum Character
{
    None = 0,
    Xyrho = 10,
    Shamoo = 20,
    Seven = 30,
    Cream = 40,
    Roland = 50,
    Aurelli = 60,
    Hawk = 70,
    Hazel = 80,
    Cara = 90,
    Warren = 100,
    Lucy = 110,
    Will = 120,
    PremXyrho = 130,
    PremShamoo = 140,
    PremSeven = 150,
    PremCream = 160,
    PremRoland = 170,
    PremAurelli = 180,
    PremHawk = 190,
    PremHazel = 200,
    PremCara = 210,
    PremWarren = 220,
    PremLucy = 230,
    PremWill = 240,

};

enum ItemType
{
    ct_pet = 0,
    ct_wpn = 1,
    ct_arm = 2,
    ct_mag = 3
};

enum AvatarType
{
    ct_foot = 1,
    ct_body = 2,
    ct_hand1 = 3,
    ct_hand2 = 4,
    ct_face = 5,
    ct_hair = 6,
    ct_head = 7
};

enum SearchType
{
	st_Spirit = 0,
	st_Axe = 11,
	st_Staff = 12,
	st_Sword = 13,
	st_Bow = 14,
	st_Shield = 21,
	st_Pendant = 22,
	st_Armour = 23,
	st_Boots = 24,
	st_Magic = 31,
	st_Cash = 90,
	st_GoldForce = 91,
	st_Avatar = 92
};

enum NpcType {
	NPC_TYPE_GOLEM = 1,
	NPC_TYPE_SOLDIER = 2,
	NPC_TYPE_ARCHER = 3,
	NPC_TYPE___UNKNOWN1 = 4, // I tested all modes and didn't see any NPC with this type
	NPC_TYPE_NIGHT_SOLDIER = 5,
	NPC_TYPE_DEATH = 6,
	NPC_TYPE_SLIME = 7,
	NPC_TYPE_GARGOYLE = 8,
	NPC_TYPE_TREASURE_BOX = 9,
	NPC_TYPE_MASTER_SOLDIER = 10,
	NPC_TYPE_BARLOG = 11,
	NPC_TYPE_GOBLIN = 12,
	NPC_TYPE_GOBLIN_SHAMAN = 13,
	NPC_TYPE_HORNED_OWL = 14,
	NPC_TYPE_DARK_TREE = 15,
	NPC_TYPE___UNKNOWN2 = 16, // I tested all modes and didn't see any NPC with this type
	NPC_TYPE_ORC = 17,
	NPC_TYPE_PHANTOM = 18,
	NPC_TYPE_ORC_BERSERK = 19,
	NPC_TYPE_ORC_MAGE = 20,
	NPC_TYPE_CYCLOPS = 21,
	NPC_TYPE_DARK_FAIRY = 22,
	NPC_TYPE_MAGMA_GOLEM = 23,
	NPC_TYPE_HELL_HOUND = 24,
	NPC_TYPE_MAGMA_BOMBER = 25,
	NPC_TYPE_DARK_ORB = 26,
	NPC_TYPE_SEAL_STONE = 27,
	NPC_TYPE_CERBERUS = 28,
	NPC_TYPE_BURNING_SOUL = 29,
	NPC_TYPE_EFREET = 30,
	NPC_TYPE_RED_DRAGON = 31,
	NPC_TYPE_BARRICADE = 32,
	NPC_TYPE_DODGE_SNOWMAN = 33,
	NPC_TYPE_MOLE = 34,
	NPC_TYPE_SYMBOL = 35,
	NPC_TYPE_REAL_CHARACTER = 36,
	NPC_TYPE_HOCKEY_GOALIE = 37,
	NPC_TYPE_HOCKEY_NET = 38,
	NPC_TYPE_PET_SLIME = 39,
	NPC_TYPE_PET_SKULL_MAGE = 40,
	NPC_TYPE_PET_GOBLIN_SHAMAN = 41,
	NPC_TYPE_PET_GOLEM = 42,
	NPC_TYPE_PET_MAGMA_GOLEM = 43,
	NPC_TYPE_PET_SANTA_CLAUS = 44,
	NPC_TYPE_PET_BEAGLE = 45,
	NPC_TYPE_PET_LEO = 47,
	NPC_TYPE_PET_SOCCER_LEO = 48,
	NPC_TYPE_PET_RED_DRAGON = 49,
	NPC_TYPE_PET_MINI_PIG = 50,
	NPC_TYPE_PET_MAGIC_PENGUIN = 51,
	NPC_TYPE_PET_SNOWMAN = 52,
	NPC_TYPE_TRAINING_TARGET = 100,
	NPC_TYPE_TRAINING_BARREL = 101,
	NPC_TYPE_QUEST_CRYSTAL = 102
};

struct FRIEND
{
	char name[13];
	int room;
};

struct TradeStruct
{
	int itemID[4];
	unsigned __int64 Code;
	int itemType[4];
	int itemGF[4];
	int itemLevel[4];
	int itemSkill[4];
};

class MyCharInfo
{
public:
	MyCharInfo(){
	GM_new_skill =  0;
	usr_room = -1;
	usr_ready = 0;
	usr_team = 0;
	usr_life = 0;
	usr_power = 0;
	premium = 120;
	TradeProgress = 0;
	nFriend = 0;
	usr_turn = 0;
	premium = 120;
	if(premium == 120)questlife = true;
	admin = true;
	alive = usershop_open = false;
	nSlots = nFreeSlots = 0;
	for(int i = 0; i < 13; i++)usr_name[i] = 0;
	for(int i = 0; i < 4; i++)Shop_Items[i] = Shop_id[i] = -1;
	Points = 0;
	Code = 0;
	Coins = 0;
	nSlots = 0;
	nFreeSlots = 0;
	Water = 0;
	Fire = 0;
	Earth = 0;
	Wind = 0;
	last_minute = clock();
	anti_spam = clock();
	exp_min = 0;
	npc_kills = 0;
	usr_last_element = clock();
	for (int i = 0; i < 32; i++)
	{
		ip[i] = hwid[i] = 0;
	}
	}
    int usr_id,usr_room,usr_ready,usr_slot,usr_char,rm_master,usr_mode, usr_team,usr_life, usr_turn, usr_power;
	char usr_name[13];
    int UserType, premium, TradeProgress;
    bool gender, admin, questlife, usershop_open, alive;
    int DefaultCharacter;
    int Level;
    unsigned __int64 Points;
    unsigned __int64 Code;
    int Coins;
    int Mission;
    int nSlots, nFreeSlots;
    int Water, Fire, Earth, Wind;
	int scrolls[3];
	int Shop_Items[4], Shop_id[4];
	char Shop_Title[16];
	int nFriend;
	FRIEND Friend[24];
	int GM_new_skill;
	int last_minute, exp_min, npc_kills;
	//Caching Trade Data
	TradeStruct TS;
	char ip[32];
	char hwid[32];
	int anti_spam;
	int usr_last_element;

	bool UpdateExp(int total)
	{
		int tdef = clock() - last_minute;
		if(tdef > 60000){
			last_minute = clock();
			exp_min = 0;
		}
		if(exp_min > 30000000)
			return false;
		exp_min += total;
		return true;
	}

	int CanChat()
	{
		int tdef = clock() - last_minute;
		if(tdef > 1000){
			last_minute = clock();
			exp_min = 0;
		}else exp_min++;
		return exp_min;
	}

};

struct Equips
{
    int magic;
    int weapon;
    int armour;
    int pet;
    //Avatar
};

enum CardType1
{
    black = 1,
    silver = 2,
    gold = 3,
    avatar = 4,
    pet = 5,
    silverp = 7
};

enum CardType2
{
    none = 0,
    water = 1*10,
    fire = 2*10,
    earth = 3*10,
    wind = 4*10
};


enum Weapon
{
    axe = 1+100+1000,
    staff = 2+100+1000,
    sword = 3+100+1000,
    bow = 4+100+1000
};

enum Armor
{
    shield = 1+200+1000,
    pendant = 2+200+1000,
    armor = 3+200+1000,
    boots = 4+200+1000
};

enum Magic
{
    normalmagic = 1+300+1000,
    specialmagic = 2+300+1000
};


class Card
{
public:
    Card(Weapon a, CardType2 b)
    {
        Type = a + b;
    }
    Card(Armor a, CardType2 b)
    {
        Type = a + b;
    }
    Card(Magic a, CardType2 b)
    {
        Type = a + b;
    }
    int Type;
    int getType()
    {
        return Type;
    };
};

enum Skill1
{


};

class Skill
{
public:
    Skill(int a,int b, int c)
    {
        skill = a*1000000 + b*1000 + c;
    }
    int skill;
    int getType()
    {
        return skill;
    };
};

const int MagicEleLvlCost[] = {4,7,13,50,100,800,1600,3200,0};
const int MagicEleSkillCost[] = {2,2,4,7,25,50,400,800,1600,0};
const int WpnEleLvlCost [] = {2,4,7,25,50,400,800,1600,0};
const int WpnEleSkillCost [] = {1,1,2,4,13,25,200,400,800,0};
const int ArmEleLvlCost [] = {1,2,4,13,25,200,400,800,0};
const int ArmEleSkillCost [] = {1,1,1,2,7,13,100,200,400,0};
const int ShdEleLvlCost [] = {1,1,2,7,13,100,200,400,0};
const int ShdEleSkillCost [] = {1,1,1,1,4,7,50,100,200,0};


const int BootSkill1[] = {110,111,112,113,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171};
const int ArmorSkill1[] = {102,103,104,105,106,107,108,109,142,143,144,145,146,147,148,149,150,151,152,153,154,155};
const int WeaponSkill1[] = {100,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141};
const int ShieldSkill1[] = {102,103,104,105,106,107,108,109,142,143,144,145,146,147,148,149,150,151,152,153,154,155};
const int ShieldSkill2[] = {301,302,303,304,305,306,307,308,310,311,312,313,314,315,325,326,327,328,329,330,349,350,351,352,353,354,355,356,357,358,359,360,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435};
const int PendantSkill1[] = {0,0,0,0,0};
const int PendantSkill2[] = {308,310,311,312,349,350,357,358,359,360};
const int BootSkill2[] = {310,311,312,313,349,350,351,352,361,362,363,364,365,366,367,368,369,370,371,372};
const int MeleeWpnSkill2[] = {200,201,300,301,302,303,304,306,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435};
const int RangedWpnSkill2[] = {200,201,202,203,300,301,302,303,304,306,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435};
const int MagicSkill[] = {300,301,302,303,304,306,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435};
static const char * ChatTypes[] = {"All","Whisper","Friend","Guild","Tip","Unk","GM","Trade"};
static const char * ElementTypes[] = {"none","water","fire","earth","wind"};
class ItemId
{
private:
public:
    int Identify(int a)
    {
        return a/1000;
    }
    int IdentifyItem(int a)
    {
        return (a/100)%10;
    }
    int IdentifyType(int a)
    {
        return a%10;
    }
    bool UpgradeItem(int gf,int level)
    {
        if(level < 5)return true;
        int x = rng() * 100;
        int range = 0;
        if(level == 5)
            range = 20;
        else if(level == 6)
            range = 10;
        else if(level == 7)
            range = 5;
        if(gf)range *= 2;
        if(x < range)return true;
        return false;
    }
    int GetUpgradeCost(int type,int level)
    {
        switch(IdentifyItem(type))
        {
            case ct_mag:
            return MagicEleLvlCost[level];
            case ct_wpn:
            return WpnEleLvlCost[level];
            case ct_arm:
            if(type%10 == 1)return ShdEleLvlCost[level];
			if(type%10 == 4)return WpnEleLvlCost[level];
            return ArmEleLvlCost[level];
            default:
            break;
        }
        return 0;
    }
	int GetSkillCost(int type,int level)
    {
        switch(IdentifyItem(type))
        {
            case ct_mag:
            return MagicEleSkillCost[level];
            case ct_wpn:
            return WpnEleSkillCost[level];
            case ct_arm:
            if(type%10 == 1)return ShdEleSkillCost[level];
            return ArmEleSkillCost[level];
            default:
            break;
        }
        return 0;
    }
    int GenerateSkill(int level,int Type)
	{
        int a = Type%10, b = IdentifyItem(Type);
        int Skill1 = rng100()%((level+1)*4) + 1, Skill2 = 0, Skill3 = 0;
        if(a == 4 && b == ct_arm ) //boots
        {
            Skill2 = BootSkill1[rng100()%20];
            Skill3 = BootSkill2[rng100()%20];
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
        }else if(a == 3 && b == ct_arm) //armor
        {
            Skill2 = ArmorSkill1[rng100()%22];
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
        }else if(a == 2 && b == ct_arm) //Pendant
		{
			Skill2 = PendantSkill1[rng100()%3];
            Skill3 = PendantSkill2[rng100()%10];
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
		}else if(a == 1 && b == ct_arm) //Shield
		{
			Skill2 = ShieldSkill1[rng100()%22];
            Skill3 = ShieldSkill2[rng100()%116];
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
		}

        if(b == ct_wpn)
        {
            Skill2 = WeaponSkill1[rng100()%25];
            if(a == 1 || a == 3)
            {
                Skill3 = MeleeWpnSkill2[rng1000()%106];
            }
            else if(a == 2 || a == 4)
            {
                Skill3 = RangedWpnSkill2[rng1000()%108];
            }
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
        }
        if(b == ct_mag)
        {
            Skill2 = MagicSkill[rng1000()%104];
            Skill3 = MagicSkill[rng1000()%104];
            Skill Sk(Skill1,Skill2,Skill3);
            return Sk.getType();
        }
    }
	SearchType IdentifyShopType(int type)
	{
		if(type > 10000)return st_Spirit;
		int a = type%10, b = IdentifyItem(type);
		 if(b == ct_wpn)
		 {
			 if(a == 1)return st_Axe;
			 if(a == 2)return st_Staff;
			 if(a == 3)return st_Sword;
			 if(a == 4)return st_Bow;
		 }else if(b == ct_arm)
		 {
			 if(a == 1)return st_Shield;
			 if(a == 2)return st_Pendant;
			 if(a == 3)return st_Armour;
			 if(a == 4)return st_Boots;
		 }else if(b == ct_mag)
			 return st_Magic;
		 else if(b == ct_pet)
			 return st_Cash;
		 else if(Identify(type) == 2)
			 return st_Cash;
	}
};
/*
struct ExpGain
{
	int cpMul[8];
	int exp[8];
};*/
class ExpCalculator
{
private:
	int ch_multiplier;
public:
	struct ExpGain
	{
		int cpMul[8];
		int exp[8];
	};
	ExpCalculator(int multiplier)
	{
		unsigned int seed = 0x8F246E2C ^ clock();
		InitWELLRNG512a(&seed);
		ch_multiplier = multiplier;
	}
	int CalculateNpcExp(int npcType, int damage)
	{
		if(npcType == NPC_TYPE_SYMBOL)return 0;
		return (damage*2)%100000;
	}
	void Calculate(short npcType, ExpGain *gain,int *damages)
	{
		if(damages)
		{
			int totaldmg = 0;
			for(int i = 0; i < 8; i++)
				totaldmg += damages[i];
			int totalexp = CalculateNpcExp(npcType, totaldmg);
			for(int i = 0; i < 8; i++)
				if(damages[i]){
					gain->exp[i] = totalexp*(1.5*damages[i]/totaldmg);
					int r = rng() * 11;
					gain->cpMul[i] = 10;
					for (int k = 1; k < 10; k++)
					{
						if (r < k)
						{
							gain->cpMul[i] = 10 - k;
							break;
						}
					}
					int g = rng100() % 5;
					if (g == 0)
						gain->cpMul[i] = 1;
					else if (g == 1)
						gain->cpMul[i] = 1;
					else if (g == 2)
						gain->cpMul[i] = 2;
					else if (g == 3)
						gain->cpMul[i] = 3;
				}else gain->exp[i] = 0;
		}
	}

};

class Level
{
public:
int getLevel(unsigned __int64 points)
{
	if(points >= 26843545600)
		return 32;
	else if(points >= 13421772800)
		return 31;
	else if(points >= 6710886400 )
		return 30;
	else if(points >= 3355443200 )
		return 29;
	else if(points >= 1677721600 )
		return 28;
	else if(points >= 838860800 )
		return 27;
	else if(points >= 419430400 )
		return 26;
	else if(points >= 209715200 )
		return 25;
	else if(points >= 104857600 )
		return 24;
	else if(points >= 52428800 )
		return 23;
	else if(points >= 26214400 )
		return 22;
	else if(points >= 13107200 )
		return 21;
	else if(points >= 6553600 )
		return 20;
	else if(points >= 3276800 )
		return 19;
	else if(points >= 1638400 )
		return 18;
	else if(points >= 819200 )
		return 17;
	else if(points >= 409600 )
		return 16;
	else if(points >= 204800 )
		return 15;
	else if(points >= 102400 )
		return 14;
	else if(points >= 51200 )
		return 13;
	else if(points >= 25600 )
		return 12;
	else if(points >= 12800 )
		return 11;
	else if(points >= 6400 )
		return 10;
	else if(points >= 3200 )
		return 9;
	else if(points >= 2400 )
		return 8;
	else if(points >= 1600 )
		return 7;
	else if(points >= 800 )
		return 6;
	else if(points >= 400 )
		return 5;
	else if(points >= 200 )
		return 4;
	else if(points >= 100 )
		return 3;
	else if(points >= 50 )
		return 2;
	else if(points > 0)
		return 1;
	return 0;
}
};


#endif
