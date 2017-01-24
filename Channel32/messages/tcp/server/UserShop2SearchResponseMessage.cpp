#include "UserShop2SearchResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

UserShop2SearchResponseMessage::UserShop2SearchResponseMessage(int total,int rooms[5],char name[5][13],int levels[5],bool gender[5],unsigned __int64 price[5],int card[5],int gf[5],int level[5],int skill[5])
    : Message(sizeof(UserShop2SearchResponseMessage), MESSAGE_TYPE_CARD_SEARCH_RESPONSE), total(total)
{
	for(int i = 0; i < 5; i++){
		this->rooms[i] = rooms[i];
		for(int j = 0; j < 13; j++)
			this->name[i][j] = name[i][j];
		this->levels[i] = levels[i];
		this->gender[i] = gender[i];
		this->price[i] = price[i];
		this->card[i] = card[i];
		this->gf[i] = gf[i];
		this->level[i] = level[i];
		this->skill[i] = skill[i];
	}
}