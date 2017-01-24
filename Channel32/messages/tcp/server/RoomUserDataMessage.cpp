#include "RoomUserDataMessage.h"
#include <MessageTypes.h>
#include <cstring>

RoomUserDataMessage::RoomUserDataMessage(int Slot, char* netip, char* locip, int level, char* username, bool gender, int Ready, int Character, int team, int magictype, int weapontype, int armortype, int pettype, int magiclevel, int weaponlevel, int armorlevel, int petlevel, int magicgf, int weapongf, int armorgf, int petgf, int magicskill, int weaponskill, int armorskill, int petskill, int* scroll, int foot, int body, int hand1, int hand2, int face, int hair, int head, int Start, bool isJoined, int mission, int missionlevel)
    : Message(sizeof(RoomUserDataMessage), MESSAGE_TYPE_ROOM_USER_DATA),
      Slot(Slot), level(level), gender(gender), Ready(Ready), Character(Character), team(team), magictype(magictype), weapontype(weapontype), armortype(armortype), pettype(pettype), magiclevel(magiclevel), weaponlevel(weaponlevel), armorlevel(armorlevel), petlevel(petlevel), magicgf(magicgf), weapongf(weapongf), armorgf(armorgf), petgf(petgf), magicskill(magicskill), weaponskill(weaponskill), armorskill(armorskill), petskill(petskill), foot(foot), body(body), hand1(hand1), hand2(hand2), face(face), hair(hair), head(head), Start(Start), isJoined(isJoined), mission(mission), missionlevel(missionlevel)
{
    strcpy(this->netip, netip);
    strcpy(this->locip, locip);
    strcpy(this->username, username);
	for(int i = 0; i < 3; i++)
    this->scroll[i] =  scroll[i];
	unk3 = 0; //0
    unk4 = 0; //0
    unk5 = 0;
    unk6 = 0;
    unk7 = 0;
    unk8 = 0; //Team
    unk10 = 0;
    unk12 = 0;
    unk13 = 0;
	unk15 = unk16 = unk17 = unk18 = 0;
	bunk2 = bunk3 = bunk4 = false;
	bunk2 = true; //QuestLife
	bunk01 = bunk02 = bunk03 = false;
	//unk9 = 0x01000000; //0x01000000
	unk20 = -1; //-1
	unk21 = -1; //-1
	unk24 = unk25 = 0;
	unk26 = -1; //-1
}
