#ifndef __USERSHOP2SEARCHRESPONSEMESSAGE_H__
#define __USERSHOP2SEARCHRESPONSEMESSAGE_H__

#include <Message.h>

class UserShop2SearchResponseMessage : public Message
{
public:
    int total;
	int rooms[5]; //670000+ US, -1 none
	char name[5][13];
	int levels[5];
	bool gender[5];
	bool zeros[3];
	int unk2;
	unsigned __int64 price[5];
	int card[5];
	int gf[5];
	int level[5];
	int skill[5];

    UserShop2SearchResponseMessage(int total,int rooms[5],char name[5][13],int levels[5],bool gender[5],unsigned __int64 price[5],int card[5],int gf[5],int level[5],int skill[5]);
};

#endif // __USERSHOP2SEARCHRESPONSEMESSAGE_H__
