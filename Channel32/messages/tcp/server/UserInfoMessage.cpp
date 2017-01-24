#include "UserInfoMessage.h"
#include <MessageTypes.h>
#include <cstring>

UserInfoMessage::UserInfoMessage(char* username, int level, int gender, int defaultcharacter, unsigned __int64 Points, int wins, int losses, int KO, int Down, unsigned __int64 Codes, unsigned __int64 Coins, int magic, int weapon, int armour, int pet, int magicgf, int weapongf, int armourgf, int petgf, int magiclevel, int weaponlevel, int armourlevel, int petlevel, int magicskill, int weaponskill, int armourskill, int petskill, int mission, int foot, int body, int hand1, int hand2, int face, int hair, int head)
    : Message(sizeof(UserInfoMessage), MESSAGE_TYPE_USER_INFO_RESPONSE),
      level(level), gender(gender), defaultcharacter(defaultcharacter), Points(Points), wins(wins), losses(losses), KO(KO), Down(Down), Codes(Codes), Coins(Coins), magic(magic), weapon(weapon), armour(armour), pet(pet), magicgf(magicgf), weapongf(weapongf), armourgf(armourgf), petgf(petgf), magiclevel(magiclevel), weaponlevel(weaponlevel), armourlevel(armourlevel), petlevel(petlevel), magicskill(magicskill), weaponskill(weaponskill), armourskill(armourskill), petskill(petskill), mission(mission), foot(foot), body(body), hand1(hand1), hand2(hand2), face(face), hair(hair), head(head)
{
    strcpy(this->username, username);
	bunk1 = 1;
    unk2 = unk3 = unk4 = unk5 = unk6 = unk7 = 0;
    for(int i = 0; i < 7; i++)zeros[i] = 0;
}
