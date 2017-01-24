#include "ResultsResponseMessage.h"
#include <MessageTypes.h>
#include <cstring>

ResultsResponseMessage::ResultsResponseMessage(int *results, int *points, int *code, unsigned __int64 Points, unsigned __int64 Code)
    : Message(sizeof(ResultsResponseMessage), MESSAGE_TYPE_RESULTS_RESPONSE),
	Points(Points), Code(Code)
{
	unk2 = unk3 = 1;
	zero = 0;
	for(int i = 0; i < 8; i++){
		this->results[i] = results[i];
		this->points[i] = points[i];
		this->code[i] = code[i];
	}
}
