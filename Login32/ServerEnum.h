#ifndef __SERVERENUM_H__
#define __SERVERENUM_H__

enum Character
{
    None = 0,
    Xyrho = 10,
    Shamoo = 20,
    Seven = 30,
    Cream = 40,
    Roland = 50,
    Aurelli = 60,
    Hawk = 70,
    Hazel = 80,
    Cara = 90,
    Warren = 100,
    Lucy = 110,
    Will = 120,
};

enum LoginResponseType
{
    WrongPasswd = 0,
    CorrectPasswd = 1,
	AlreadyIn = -4
};

struct MyCharInfo
{
    int UserType;
    int DefaultCharacter;
    int Level;
    unsigned __int64 Points;
    unsigned __int64 Code;
	int eleType;
};

class Level
{
public:
int getLevel(unsigned __int64 points)
{
	if(points >= 26843545600)
		return 32;
	else if(points >= 13421772800)
		return 31;
	else if(points >= 6710886400 )
		return 30;
	else if(points >= 3355443200 )
		return 29;
	else if(points >= 1677721600 )
		return 28;
	else if(points >= 838860800 )
		return 27;
	else if(points >= 419430400 )
		return 26;
	else if(points >= 209715200 )
		return 25;
	else if(points >= 104857600 )
		return 24;
	else if(points >= 52428800 )
		return 23;
	else if(points >= 26214400 )
		return 22;
	else if(points >= 13107200 )
		return 21;
	else if(points >= 6553600 )
		return 20;
	else if(points >= 3276800 )
		return 19;
	else if(points >= 1638400 )
		return 18;
	else if(points >= 819200 )
		return 17;
	else if(points >= 409600 )
		return 16;
	else if(points >= 204800 )
		return 15;
	else if(points >= 102400 )
		return 14;
	else if(points >= 51200 )
		return 13;
	else if(points >= 25600 )
		return 12;
	else if(points >= 12800 )
		return 11;
	else if(points >= 6400 )
		return 10;
	else if(points >= 3200 )
		return 9;
	else if(points >= 2400 )
		return 8;
	else if(points >= 1600 )
		return 7;
	else if(points >= 800 )
		return 6;
	else if(points >= 400 )
		return 5;
	else if(points >= 200 )
		return 4;
	else if(points >= 100 )
		return 3;
	else if(points >= 50 )
		return 2;
	else if(points > 0)
		return 1;

	return 0;

}
};

static const char * ElementTypes[] = {"none","water","fire","earth","wind"};

#endif
