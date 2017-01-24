#include <Windows.h>
#include "Ini.h"

CIni::CIni(char * fileName, char * section) : _fileName(fileName), _section(section)
{
	ASSERT(_fileName.size() < 256);
}

CIni::~CIni()
{
}

int CIni::ReadInteger(const char* key, int defaultValue, const char* section) const
{
	if(!section)
		section = _section.c_str();

	return GetPrivateProfileInt(section,  key, defaultValue, _fileName.c_str());
}

float CIni::ReadFloat(const char* key, float defaultValue, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char defaultVal[256];
	sprintf(defaultVal, "%f", defaultValue);

	char result[256];
	GetPrivateProfileString(section,  key, defaultVal, result, sizeof(result), _fileName.c_str()); 

	return (float)atof(result);
}

bool CIni::ReadBoolean(const char* key, bool defaultValue, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char defaultVal[256];
	sprintf(defaultVal, "%s", defaultValue ? "true" : "false");

	char result[256];
	GetPrivateProfileString(section, key, defaultVal, result, sizeof(result), _fileName.c_str()); 

	return (strcmp(result, "true") == 0) ? true : false;
}

char * CIni::ReadString(const char* key, const char* defaultValue, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char* result = new char[256];
	ZeroMemory(result, sizeof(result));
	GetPrivateProfileString(section,  key, defaultValue, result, 256, _fileName.c_str()); 
	return result;
}


void CIni::WriteInteger(const char* key, int val, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char _val[256];
	sprintf(_val, "%d", val);
	WritePrivateProfileString(section,  key, _val, _fileName.c_str()); 
}

void CIni::WriteFloat(const char* key, float val, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char _val[256];
	sprintf(_val, "%f", val);
	WritePrivateProfileString(section,  key, _val, _fileName.c_str()); 
}

void CIni::WriteBoolean(const char* key, bool val, const char* section) const
{
	if(!section)
		section = _section.c_str();

	char _val[256];
	sprintf(_val, "%s", val ? "true" : "false");
	WritePrivateProfileString(section,  key, _val, _fileName.c_str()); 
}

void CIni::WriteString(const char* key, char* val, const char* section) const
{
	if(!section)
		section = _section.c_str();

	WritePrivateProfileString(section,  key, val, _fileName.c_str());
}
