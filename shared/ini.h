#ifndef INI_H
#define INI_H
#pragma once

#include <string>

#include "typedefs.h"

class CIni
{
public:
	CIni(char * fileName, char * section = NULL); 
	~CIni();

	void SetSection(const char * section)
	{
		_section = section;
	}

	int ReadInteger(const char * key, int defaultValue, const char* section = NULL) const;
	float ReadFloat(const char * key, float defaultValue, const char* section = NULL) const;
	bool ReadBoolean(const char * key, bool defaultValue, const char* section = NULL) const;
	char * ReadString(const char * key, const char * defaultValue, const char* section = NULL) const;

	void WriteInteger(const char * key, int val, const char* section = NULL) const;
	void WriteFloat(const char * key, float val, const char* section = NULL) const;
	void WriteBoolean(const char * key, bool val, const char* section = NULL) const;
	void WriteString(const char * key, char * val, const char* section = NULL) const;

private:
	const string _fileName;
	string _section;
};

#endif