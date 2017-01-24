#ifndef __ROSULTSRESPONSEMESSAGE_H__
#define __ROSULTSRESPONSEMESSAGE_H__

#include <Message.h>

class ResultsResponseMessage : public Message
{
public:
	int results[8];
	int unk2; //1
	int unk3; //1
	int points[8];
	int code[8];
	int zero;
	unsigned __int64 Points;
	unsigned __int64 Code;

    ResultsResponseMessage(int *results, int *points, int *code, unsigned __int64 Points, unsigned __int64 Code);
};

#endif // __ROSULTSRESPONSEMESSAGE_H__
