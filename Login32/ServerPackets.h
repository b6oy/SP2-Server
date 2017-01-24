#ifndef __SERVERPACKETS_H__
#define __SERVERPACKETS_H__

#define LOGIN_RESPONSE   10247
#define SERVERINFO_RESPONSE   10504
#define CHANGE_DEFAULT_CHARACTER_RESPONSE    10514
#define TRAINING_DONE_RESPONSE	10531

struct LoginResponse
{
    int size;  //0xA8
    int type; //10247
    int unk1; //11036
    int checksum;
    int state;
    ResponseType Response;
    int UserType; //Not sure, but It control/close servers 0x1E open all servers
    Character DefaultCharacter;
    int UserLevel1;
    int UserLevel2;
    int unk2;
    int unk3;
    int AgeCheck; //1 is ok, other will give korean announcement
    int unk4; //Always 0x40000000, can be 0
    unsigned __int64 Points;
    unsigned __int64 Code;
    int unk5;
    int unk6;
    int unk7;
    int unk8; //5
    int unk9;
    int unk10;
    int unk11; //2
    int unk12;
    int unk13; //5
    int unk14; //2
    int unk15;
    int unk16;
    int unk17;
    int unk18;
    int unk19;
    int unk20;
    int unk21;
    int unk22;
    int unk23; //-1
    int unk24; //7
    int unk25; //64

};

struct ServerInfo
{
    int size;  //0x68
    int type; //10504
    int unk1; //11036
    int checksum;
    int state;
    short channel;
    short servernumber;
    char ip[14];
    short unk2; //0x49
    int port;
    int serverload; //or maybe number of users in the server
    char chname[18];
    short unk3;
    int unk4;
    int unk5; //zero
    char gname[14];
    int unk6; //0x258
    int unk7;
    int unk8;
};

struct DefaultCharacterChangeResponse
{
    int size; //0x1C
    int type; //10514
    int unk1; //11036
    int checksum;
    int state;
    int unk2; //1
    Character character;
    int unk3;
    int unk4;
    int unk5;
};
//const int t_items[] = {11204, 11203, 11202, 11201, 11101, 11102, 11103, 11104, 11301, 2910};
const int t_items[] = {1204, 1203, 1202, 1201, 1101, 1102, 1103, 1104, 1301, 2910};
struct TrainingDoneResponse
{
    int size; //0x98
    int type;
    int unk1; //11036
    int checksum;
    int state;
	int items[10];
	int zeros[10];
	int gf[10];
	int unk2; // -1
	int unk3; //1005
	int unk4; //1243904
};

#endif
