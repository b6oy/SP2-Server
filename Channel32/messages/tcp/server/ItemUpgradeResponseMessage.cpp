#include "ItemUpgradeResponseMessage.h"
#include <MessageTypes.h>

ItemUpgradeResponseMessage::ItemUpgradeResponseMessage(int Slot,int UpgradeType,int Upgraded,int Level,int Skill,int Type,int GF, int userSlot,int UpgradeType2,unsigned __int64 Code,int WaterElements,int FireElements,int EarthElements,int WindElements, int Returned)
    : Message(sizeof(ItemUpgradeResponseMessage), MESSAGE_TYPE_ITEM_UPGRADE_RESPONSE), Slot(Slot), UpgradeType(UpgradeType), Upgraded(Upgraded), Level(Level), Skill(Skill), Type(Type), GF(GF), userSlot(userSlot), UpgradeType2(UpgradeType2), Code(Code), WaterElements(WaterElements), FireElements(FireElements), EarthElements(EarthElements), WindElements(WindElements), Returned(Returned)
{
	unk7 = 0;
}