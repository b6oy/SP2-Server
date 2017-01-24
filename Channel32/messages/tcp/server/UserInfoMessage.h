#ifndef __USERINFOMESSAGE_H__
#define __USERINFOMESSAGE_H__

#include <Message.h>

class UserInfoMessage : public Message
{
public:
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

    UserInfoMessage(char* username, int level, int gender, int defaultcharacter, unsigned __int64 Points, int wins, int losses, int KO, int Down, unsigned __int64 Codes, unsigned __int64 Coins, int magic, int weapon, int armour, int pet, int magicgf, int weapongf, int armourgf, int petgf, int magiclevel, int weaponlevel, int armourlevel, int petlevel, int magicskill, int weaponskill, int armourskill, int petskill, int mission, int foot, int body, int hand1, int hand2, int face, int hair, int head);
};

#endif // __USERINFOMESSAGE_H__
