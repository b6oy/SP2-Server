#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <Windows.h> // for console logging

class Log;

enum LogMessageType
{
	LOG_TYPE_NORMAL,
	LOG_TYPE_IMPORTANT,
	LOG_TYPE_WARNING
};

enum LogMode
{
	LOG_MODE_CONSOLE = 1,
	LOG_MODE_FILE = 2,
	LOG_MODE_BOTH = LOG_MODE_CONSOLE | LOG_MODE_FILE
};

class TempStream : public std::ostream
{
public:
	TempStream(Log& log, std::streambuf* buffer, const LogMessageType messageType);
	TempStream(std::streambuf * buffer);
	TempStream(const TempStream & other);
	~TempStream();

private:
	std::streambuf* buffer;
};

class LogBuffer : public std::stringbuf
{
public:
	LogBuffer(Log& log, const LogMessageType messageType);

protected:
	int sync(); // triggers on endline

private:
	Log& log;
	LogMessageType messageType;
};

class Log
{
public:
	void SetMode(const LogMode mode);
	TempStream operator()(LogMessageType messageType = LOG_TYPE_NORMAL);
	static Log out;

private:
	Log(const LogMode mode);
	LogMode mode;
	HANDLE hConsoleOutput;
	friend class LogBuffer;
};

#endif // __LOG_H__
