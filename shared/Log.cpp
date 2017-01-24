#include <iostream>
#include <Windows.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Log.h"

using namespace std;

string GetCurrentDateTimeString()
{
	return boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::local_time());
}

TempStream::TempStream(std::streambuf* buffer)
: ostream(buffer), buffer(buffer)
{
	*this << "[" << GetCurrentDateTimeString() << "] ";
}

TempStream::TempStream(const TempStream& other)
	: ostream(other.buffer), buffer(other.buffer)
{
}

TempStream::~TempStream()
{
	delete buffer;
}

LogBuffer::LogBuffer(Log& log, const LogMessageType messageType)
	: log(log), messageType(messageType)
{
}

int LogBuffer::sync()
{
	const std::string message = this->str();
	if (this->log.mode & LOG_MODE_CONSOLE)
	{
		WORD textAttribute;
		if (this->messageType == LOG_TYPE_IMPORTANT)
		{
			textAttribute = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}
		else if (this->messageType == LOG_TYPE_WARNING)
		{
			textAttribute = FOREGROUND_RED | FOREGROUND_INTENSITY;
		}
		else
		{
			textAttribute = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		}

		SetConsoleTextAttribute(this->log.hConsoleOutput, textAttribute);
		cout << message << flush;
	}
	if (this->log.mode & LOG_MODE_FILE)
	{
		// TODO
	}
	this->setp(0, 0);
	return 0;
}

Log Log::out(LOG_MODE_CONSOLE);

Log::Log(const LogMode mode)
	: mode(mode), hConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

void Log::SetMode(const LogMode mode)
{
	this->mode = mode;
}

TempStream Log::operator()(LogMessageType messageType)
{
	return TempStream(new LogBuffer(*this, messageType));
}

