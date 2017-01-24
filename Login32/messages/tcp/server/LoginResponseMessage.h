#ifndef __LOGINRESPONSEMESSAGE_H__
#define __LOGINRESPONSEMESSAGE_H__

#include <ServerEnum.h>
#include <Message.h>

class LoginResponseMessage : public Message
{
public:
	int responseType;
    int userType; //Not sure, but It control/close servers 0x1E open all servers
    int defaultCharacter;
    int userLevel1;
    int userLevel2;
    int unk2;
    int unk3;
    int ageCheck; //1 is ok, other will give korean announcement
    int unk4; //Always 0x40000000, can be 0
    long long int points;
    long long int code;
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

	LoginResponseMessage(LoginResponseType responseType);
	LoginResponseMessage(LoginResponseType responseType, int userType, int defaultCharacter, int userLevel, long long int points, long long int code);
};

#endif // __LOGINRESPONSEMESSAGE_H__
