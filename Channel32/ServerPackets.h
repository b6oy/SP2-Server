#ifndef __SERVERPACKETS_H__
#define __SERVERPACKETS_H__

#define JOIN_CHANNEL_RESPONSE   17271
#define JOIN_MISSIONLEVEL_RESPONSE   17491
#define JOIN_PLAYERDATA_RESPONSE   17154
#define ROOM_CREATE_RESPONSE 17160
#define NPC_LIST_RESPONSE   17417
#define ROOM_PLAYERDATA_RESPONSE 17175
#define NPC_KILL_RESPONSE   17241
//#define QUEST_LIFE_RESPONSE 17206
#define REVIVE_RESPONSE 17204
#define LOBBY_USERINFO_RESPONSE 17155
#define ROOM_EXIT_RESPONSE 17177
#define CHAT_RESPONSE 17202
#define USER_INFO_RESPONSE 17168
#define ROOM_LIST_RESPONSE  17537
#define NEW_ROOM_RESPONSE   17156
#define ROOM_PLAYER_LIST_RESPONSE  17170
#define ROOM_JOIN_RESPONSE    17172
#define ROOM_JOIN_RESPONSE2    17412
#define SHOP_JOIN_RESPONSE    17252
#define SHOP_BUY_RESPONSE     17256
#define SHOP_SELL_RESPONSE     17254
#define CARD_UPGRADE_RESPONSE   17219
#define AFTER_ROOM_JOIN_RESPONSE    17411
#define IN_GAME_RESPONSE        17297
#define PLAYER_KILLED_RESPONSE  17206
#define NEW_MASTER_RESPONSE 17188
#define ROUND_CLEAR_RESPONSE 17207
#define BUY_SCROLL_RESPONSE 17200
#define PICK_SCROLL_RESPONSE		  17479
#define RESULTS_RESPONSE 17249
#define SPAWN_RESPONSE	17264
#define MISSION_COMPLETE_RESPONSE 17208
#define MISSION_AFTER_RESPONSE 17495
#define BIGBATTLE_NPC_X_RESPONSE	17424
#define CARD_SEARCH_RESPONSE	17459
#define BIGBATTLE_NPC_KO_RESPONSE  17303
#define PLAYER_KICK_RESPONSE	17185
#define CHANGE_ROOMTITLE_RESPONSE	17257
#define TRADE_SUCCESS_RESPONSE	17217
#define OPEN_USER_SHOP_PROD	17267
#define CLOSE_USER_SHOP_PROD 17266
#define USER_SHOP_BUY_RESPONSE	17522
#define SEARCH_SHOP_BUY_RESPONSE 17462
#define MISSION_NPC_KILL_RESPONSE 17281
#define START_COUNT_DOWN_RESPONSE 17493
#define SEND_MEMO_RESPONSE	17445
#define RCV_MEMO_RESPONSE 17446
#define CONFIRM_ID_RESPONSE 17428
#define FIND_USER_RESPONSE 17190
#define ADD_FRIEND_RESPONSE 17236
#define FRIEND_LIST_RESPONSE 17238
#define LEVEL_UP_RESPONSE	17264
#define LEVEL_UP 17223
#define GIFT_VERIFY_ID_RESPONSE 17430
#define SEND_GIFT_RESPONSE 17432
#define USE_US_RESPONSE	17525
#define GOAL_RESPONSE	17221

struct LobbyUserInfoResponse
{
    int size; //0x3C
    int type;
    int unk1; //11036
    int checksum;
    int state;
    char username[16];
    int level;
    int unk01;
    int unk02;
    bool gender; //1
    bool b2; //1
    bool b3;
    bool b4;
    bool b5; //1
    bool b6; //1
    bool b7;
    bool b8;
    int missionlevel;
};

struct JoinChannelResponse
{
    int size; //0x40
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //0x2CF
    int unk3; //0x2CA
    int unk4; //0
    int unk5; //1
    int unk6;
    int unk7;
    int unk8;
    int unk9; //0x6D15D3
    int unk10; //0
    int unk11; //0
    int unk12; //0x78020F00
};

struct JoinChannelMissionLevelResponse
{
    int size; //0x1C
    int type;
    int unk1; //11036
    int checksum;
    int state; //0x24DB8
    int MissionLevel;
    int unk2; //0
};

struct JoinChannelPlayerDataResponse
{
    int size; //0x980
    int type;
    int unk1; //11036
    int checksum;
    int state; //0x44DF45
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
    int zero3[3];
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
    bool bunk[7]; //1 0 1 1 1 1 0 0
    int Rank;
    int unk43; //1
    int unk44; //0x108
    int munk1, munk2, munk3, munk4, munk5, munk6, munk7, munk8; //-1
    int unk45; //7
    int zero5[2];
    int unk46; //0x120101
};


struct CreateRoomResponse
{
    int size;
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk01; //2
    int roomnumber;
    char roomname[32];
    int mode; //0x1b
    int map; //0x1b
    char password[16];
    int capacity;
    char allowscrolls; //1
    char autoteam; //1
    short unk2; //0
    int character; //0xA0
    int unk03; //0x74F59300
    int maxcardlevel; //-1
    char allowcritsheild;
    char unk3; //0
    char unk4; //0
    char unk5; //0
};

struct RoomPlayerDataResponse
{
    int size; //0x118
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int Slot; //0
    char netip[16];
    char locip[16];
    int level;
    char username[13];
    short unk3; //0
    int unk4; //0
    int unk5;
    int unk6;
    int unk7;
    int unk8; //Team
    int unk9; //0x01000000
    int unk10;
    int unk12;
    int unk13;
    int Ready;
    int Character; //0x8C
    int unk15;
    int unk16;
    int team; //red = 0xA, blue = 0x14
    int unk17;
    int unk18;
    int magictype;
    int weapontype;
    int armortype;
    int pettype; //maybe
    int magiclevel;
    int weaponlevel;
    int armorlevel;
    int petlevel; //maybe
    int magicgf;
    int weapongf;
    int armorgf;
    int petgf; //maybe
    int magicskill;
    int weaponskill;
    int armorskill;
    int petskill; //maybe
    int scroll[3];
    int foot;
    int body;
    int hand1;
    int hand2;
    int face;
    int hair;
    int head;
    int Start; //2
    int unk20; //-1
    int unk21; //-1
    //int unk22; //0x01010000
	bool bunk1;
	bool bunk2;
	bool bunk3;
	bool bunk4;
    int mission;
    int missionlevel; //maybe
    int unk24;
    int unk25;
    int unk26; //-1
};

struct ChatResponse
{
    int size; //0x7C
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int chatType; //0 All, 7 Trade
    char senderId[13];
    char recieverId[13];
    char msg[52];
    short unk2;
    int unk3;
    int unk4; //1
    int unk5;
    int unk6; //0x0018F9C4
    int unk7; //0x74D2FF16
};

struct UserInfoResponse
{
    int size; //0xF0
    int type;
    int unk1; //11036
    int checksum;
    int state;
    bool bunk1; //1
    char username[14];
    int level;
    int gender;
    int unk2;
    int unk3;
    int unk4;
    int unk5;
    int unk6;
    int unk7;
    int defaultcharacter; //0x14
    unsigned __int64 Points;
    int wins;
    int losses;
    int KO;
    int Down;
    unsigned __int64 Codes;
    unsigned __int64 Coins;
    int magic;
    int weapon;
    int armour;
    int pet;
    int magicgf;
    int weapongf;
    int armourgf;
    int petgf;
    int magiclevel;
    int weaponlevel;
    int armourlevel;
    int petlevel;
    int magicskill;
    int weaponskill;
    int armourskill;
    int petskill;
    int mission;
    int foot;
    int body;
    int hand1;
    int hand2;
    int face;
    int hair;
    int head;
    int zeros[7];
};

struct LobbyRoomResponse
{
    int size; //0xB0
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //1
    int roomnumber;
    char title[29];
    int mode; //0x1b
    int map; //0x1b
    int unk4; //0x100
    int maxplayers; //8
    int unk5; //0x100
    int unk6; //0x00551C00
    int unk7; //-1
    int characters[8]; //0x46
    int zeros[13];
    int unk9; //0x100
};

struct RoomListResponse
{
    int size; //0xC90
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int roomnumber[22];
    char title[22][29];
    short zero1;
    int mode[22];
    int map[22];
    int unks2[22]; //1
    int maxplayers[22];
    int zeros[5];
    short szero;
    bool bPotion[22];
    bool bClosed[22];
    short szero1;
    int unk3[11];
    int unks4[22]; //-1,-1
    int players[22][16]; //0x8C
    int unks6[115];
    short zero2;
    bool bunk[22]; //1..
    int zeros1[5];
    int unk4; // 0x500000
};

struct RoomPlayerListResponse
{
    int size; //0xCC
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //0
    int plevel[8]; //22, -99
    bool genders[8];
    char username[8][13];
    int zeros[8];
    int master;
};

struct RoomJoinResponse
{
    int size; //0x7C
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //0
    int roomnumber;
    char title[32];
    int mode;
    int map;
    int unk01; //0x04A30000
    int unk02; //0x7C96A144
    int unk03; //0x04A307D8
    int unk04; //0x0012FB8C
    int maxp;
    int unk05; //0x7C96A101
    int unk06;
    int unk07; //0x04A30000
    int Slot; //1
    int unk09; //0xA
    int unk10;
    int unk11; //-1
    int unk12;
    int unk13; //0x77DF0001
};

struct RoomJoinResponse2
{
    int size; //0x24
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int unks[4];
};

struct RoomExitResponse
{
    int size; //0x28
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //0
    char username[16];
};

struct ShopJoinResponse
{
    int size; //0x18
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int cash;
};

struct ShopBuyResponse
{
    int size; //0x698
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //1
    bool bMyCard[96];
    int TypeMyCard[96];
    int GFMyCard[96];
    int LevelMyCard[96];
    int SkillMyCard[96];
    unsigned __int64 Slots;
    unsigned __int64 Code;
    unsigned __int64 Cash;
    unsigned __int64 unk4;
};

struct ShopSellResponse
{
    int size; //0x30
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //1
    int item_slot;
    int unk3;
    unsigned __int64 Code;
    unsigned __int64 unk4;
};

struct CardUpgradeResponse
{
    int size; //0x58
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int Slot;
    int UpgradeType; //1 = Lvl, 2 = Skill
    int Upgraded; //1 lvl, 5 skill
    int Level;
    int Skill;
    int Type;
    int GF;
    int unk5;
    int UpgradeType2;
    int Returned;
    int unk7;
    unsigned __int64 Code;
    int WaterElements;
    int FireElements;
    int EarthElements;
    int WindElements;
};

struct AfterRoomJoinResponse
{
    int size; //0x24
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //-1
    int unk3; //-1
    int unk4; //-1
};

struct NewKingResponse
{
    int size; //0x18
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int slot;
};

struct PlayerKilledResponse
{
    int size; //0xAC
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int DeadplayerSlot;
    int KillerSlot;
    int PointsMiltiplier;
    int unk2; //3,2
    int unk3; //1
    int unk4; //1
    int unk5; //1
    int unk6; //1
    int unk7; //1
    int unk8; //1
    int GainedPoints;
    int LostPoints;
    int zeros[6];
    int unks[16]; //-1
    int unk01; //maybe kills
    int unk02; //0,1 maybe king
    int unk03; //1
    int canRespawn; //0
};

struct NewMasterResponse
{
    int size; //0x1C
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int Slot;
    int unk2;
};

struct ReviveResponse
{
    int size; //0x20
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int Slot;
    int unk2;
    int unk3;
};

struct RoundClearResponse
{
    int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int Slot; //maybe
    unsigned __int64 Points;
    unsigned __int64 Code;
    int unk2;
    int unk3; //1
	int unk4; //-75
	int unk5; //-75
};

struct BuyScrollResponse
{
    int size; //0x30
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int buy;
    int zero1;
    int unk2; //2
    int scrollid; //0xC
    int zero2;
    unsigned __int64 Code;
};

struct PickScrollResponse
{
    int size; //0x20
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int zero;
	int scroll;
	int slot;
};

struct ResultsResponse
{
	int size; //0x90
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int uk1[8];
	int unk2; //1
	int unk3; //1
	int points[8];
	int code[8];
	int zero;
	unsigned __int64 Points;
	unsigned __int64 Code;
};

struct SpawnResponse
{
	int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int slots[8]; //0 = on; -1 = off
	int zero;
};

struct MissionCompleteResponse
{
	int size; //0x1A0
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int uk1[8]; //1 or -1, 1= Win, 2= Lose
	int bluewins; //maybe
	int redwins;
	int negative_exp;
	unsigned __int64 Points;
	unsigned __int64 Code;
	unsigned __int64 dzero;
	unsigned __int64 dunk; //180
	unsigned __int64 dzero1;
	unsigned __int64 dzero2;
	unsigned __int64 dzero3;
	unsigned __int64 dunk1; //180
	unsigned __int64 dzeros[11];
	int ones[8]; //1
	int unk2; //10
	int maxrounds[8]; //1
	int unk4; //7
	int unks[16]; //-1
	int zeros[8];
	int ones3[8]; //1
	int unk5; //268487332
};

struct MissionAfterResponse
{
	int size; //0x1C
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int unk2; //3
	int unk3; //2
};

struct BigBattleNpcMultiplier
{
	int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
	int state;
	BYTE x[36];
};

struct CardSearchResponse
{
	int size; //0x108
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int total;
	int rooms[5]; //670000+ US, -1 none
	char name[5][13];
	int levels[5];
	bool gender[5];
	bool zeros[3];
	int unk2;
	unsigned __int64 price[5];
	int card[5];
	int gf[5];
	int level[5];
	int skill[5];
};

struct BigBattleNpcKoResponse
{
    int size; //0xA4
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int npcn;
	int zero;
	int unk2; //1
	int multiplier;
	int unk3; //1
	int unk4; //1
	int pointbase;
	int sub; //0xFFFFFFFA
	int zeros[3];
	int npcn2;
	int unks[20]; //-1
	int eleType;
	int eleBase;
	int eleMul; //1
	int one; //1
	int zero1;
	int unk5; //-1
};

struct QuestGainResponse
{
    int size; //0xB0
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int npc_num;
	int killerslot;
	int zeros;
	int timeStamp;
	//ExpGain exp;
	int unks[16];
	int eleType;
	int eleBase;
	int eleMul;
};

struct NpcListResponse
{
    int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
	int state;
	BYTE levels[36];
};

struct PlayerKickResponse
{
    int size; //0x18
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int slot;
};

struct RoomTitleChangeResponse
{
    int size; //0x34
    int type;
    int unk1; //11036
    int checksum;
	int state;
	char title[32];
};

struct TradeSuccessResponse
{
	int size; //0x6A0
    int type;
    int unk1; //11036
    int checksum;
	int state;
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
};

struct OpenUserShopProd
{
	int size; //0x40
    int type;
    int unk1; //11036
    int checksum;
	int state;
	char username[13];
	char shopname[15];
	int one; //1
	int zero;
	int zero1;
	int zero2;
};

struct UserShopBuyResponse
{
	int size; //0x34
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int zeros[8];
};

struct CloseUserShopProd
{
	int size; //0x6A8
    int type;
    int unk1; //11036
    int checksum;
	int state;
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
	int unk2; //-1, 0 = sold
};

struct SearchShopBuyResponse
{
	int size; //0x698
    int type;
    int unk1; //11036
    int checksum;
	int state;
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
};

struct MissionNpcKillResponse
{
    int size; //0xB4
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int npc_num;
	int killerslot;
	int unk2; //0x77B94A01
	int timeStamp;
	int ones[8];
	int zeros[8];
	int unks[16]; //-1
	int zero1;
	int zero2;
	int one;
	int zero3;
};

struct StartCountDownResponse
{
    int size; //0x24
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int zero1;
	int timestamp; //0x025A0214
	int time; //6000
	int zero2;
};

struct SendMemoResponse
{
    int size; //0x28
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int unk2; //1
	char username[16];
};

struct RcvMemoResponse
{
    int size; //0xB0
    int type;
    int unk1; //11036
    int checksum;
	int state;
	char username[16];
	int unk2; //5
	int unk3; //0x000008FD
	int zero;
	char msg[120];
	int time;
	int unk4;
};

struct ConfirmIdResponse
{
    int size; //0x18
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int response; //1 = OK, 0 = Not found
};

struct FindUserResponse
{
    int size; //0x4C
    int type;
    int unk1; //11036
    int checksum;
	int state;
	char username[16];
	int zeros[7];
	int room;
	int unk2; //-1
	int unk3; //-1
};

struct FriendListResponse
{
    int size; //0x20C
    int type;
    int unk1; //11036
    int checksum;
	int state;
	char names[24][13];
	int online[24]; //-1
	int unks[24]; //-1
};

struct LevelUpResponse
{
	int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int slot[8]; //0 = Levelup, -1
	int zero;
};

struct LevelUp
{
	int size; //0x6A0
    int type;
    int unk1; //11036
    int checksum;
	int state;
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
};

struct SendGiftResponse
{
    int size; //0x38
    int type;
    int unk1; //11036
    int checksum;
	int state; // 0 = Nothing, 1 = OK, 2 = Error, 3 = No Code, 
	int sent; //1
	char username[16];
	int gift_type;
	int unk2; //0xFFFF764C
	int slot;
	int unk;
};

struct UseUSResponse
{
    int size; //0x24
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int unk2; //4 = Add, 6 = Del
	int unk3; //1
	int slot;
	unsigned __int64 price;
};

struct GoalResponse
{
    int size; //0x28
    int type;
    int unk1; //11036
    int checksum;
	int state;
	int team;
	int bluewins;
	int redwins;
	int unk4;
	int unk5;
};

#endif
