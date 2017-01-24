#include "Item.h"

Item::Item()
{
}

Item::Item(int uniqueId, int type, int remainingForceDays, int levelOrRemainingUses, int skills)
	: uniqueId(uniqueId), type(type), remainingForceDays(remainingForceDays),
	  levelOrRemainingUses(levelOrRemainingUses), skills(skills)
{

}

void Item::SetItem(int uniqueId, int type, int remainingForceDays, int levelOrRemainingUses, int skills)
{
	this->uniqueId = uniqueId;
    this->type = type;
    this->remainingForceDays = remainingForceDays;
    this->levelOrRemainingUses = levelOrRemainingUses;
    this->skills = skills;
}

int Item::GetUniqueId() const
{
	return uniqueId;
}

int Item::GetType() const
{
	return type;
}

int Item::GetRemainingForceDays() const
{
	return remainingForceDays;
}

int Item::GetLevelOrRemainingUses() const
{
	return levelOrRemainingUses;
}

int Item::GetSkills() const
{
	return skills;
}
