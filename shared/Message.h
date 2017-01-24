#ifndef __MESSAGE_H__
#define __MESSAGE_H__

class Message
{
public:
    int size;
    int type;
    int thirdField; // I don't know what this is used for, but it's always 11036.
    int checksum;
    int state;

	static const int THIRD_FIELD = 11036;

protected:
	Message(int size, int type);

};

#endif // __MESSAGE_H__
