#ifndef __ROOMUSERDATAMESSAGE_H__
#define __ROOMUSERDATAMESSAGE_H__

#include <Message.h>

class RoomUserDataMessage : public Message
{
public:
    int Slot; //0
    char netip[16];
    char locip[16];
    int level;
    char username[12];
    short unk3; //0
    int unk4; //0
    int unk5;
    int unk6;
    int unk7;
    int unk8; //Team
	bool bunk01;
	bool bunk02;
	bool bunk03;
	bool gender;
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
    bool isJoined;
    bool bunk2;
    bool bunk3;
    bool bunk4;
    int mission;
    int missionlevel; //maybe
    int unk24;
    int unk25;
    int unk26; //-1

    RoomUserDataMessage(int Slot, char* netip, char* locip, int level, char* username, bool gender, int Ready, int Character, int team, int magictype, int weapontype, int armortype, int pettype, int magiclevel, int weaponlevel, int armorlevel, int petlevel, int magicgf, int weapongf, int armorgf, int petgf, int magicskill, int weaponskill, int armorskill, int petskill, int* scroll, int foot, int body, int hand1, int hand2, int face, int hair, int head, int Start, bool isJoined, int mission, int missionlevel);
};

#endif // __ROOMUSERDATAMESSAGE_H__
