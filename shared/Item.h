#ifndef __ITEM_H__
#define __ITEM_H__

class Item
{
public:
	Item();
	Item(int uniqueId, int type, int remainingForceDays, int levelOrRemainingUses, int skills);
	void SetItem(int uniqueId, int type, int remainingForceDays, int levelOrRemainingUses, int skills);
	int GetUniqueId() const;
	int GetType() const;
	int GetRemainingForceDays() const;
	int GetLevelOrRemainingUses() const;
	int GetSkills() const;

private:
    int uniqueId;
    int type;
    int remainingForceDays;
    int levelOrRemainingUses;
    int skills;
};

#endif // __ITEM_H__