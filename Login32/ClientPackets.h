#ifndef __CLIENTPACKETS_H__
#define __CLIENTPACKETS_H__

#define LOGIN_REQ    9991
#define SERVERINFO_REQ    10503
#define AFTER_SERVERINFO_REQ    10519
#define CHANGE_DEFAULT_CHARACTER_REQ    10513
#define TRAINING_DONE_REQ		10517

struct LoginInfo
{
    int size;
    int type;
    int unk1; //11036
    int checksum;
    int state;
    unsigned char verhash[36];
    int vercode1;
    char username[13];
    char password[13];
    short unk2;
    int unk3[11];
    int pid;
};

struct ServerInfoRequest
{
    int size;
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2;
    int serverType;
};

struct DefaultCharacterChangeRequest
{
    int size;
    int type;
    int unk1; //11036
    int checksum;
    int state;
    int unk2[4];
    Character character;
};

struct TrainingDoneRequest
{
    int size;
    int type;
    int unk1; //11036
    int checksum;
    int state;
};

#endif
