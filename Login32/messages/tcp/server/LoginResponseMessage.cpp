#include <cstring>

#include "LoginResponseMessage.h"
#include <MessageTypes.h>

LoginResponseMessage::LoginResponseMessage(LoginResponseType responseType)
	: Message(sizeof(LoginResponseMessage), MESSAGE_TYPE_LOGIN_RESPONSE),
	  responseType(responseType)
{
}

LoginResponseMessage::LoginResponseMessage(LoginResponseType responseType,
	int userType, int defaultCharacter, int userLevel, long long int points, long long int code)
	: Message(sizeof(LoginResponseMessage), MESSAGE_TYPE_LOGIN_RESPONSE),
	  responseType(responseType), userType(userType), defaultCharacter(defaultCharacter), userLevel1(userLevel), userLevel2(userLevel),
	  points(points), code(code)
{
	this->ageCheck = 1;
	memset(&this->unk5, 0, 20 * sizeof(int));
}
