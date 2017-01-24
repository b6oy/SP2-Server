#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <Windows.h>
#include <stdio.h>
#include <process.h>
#include "ServerEnum.h"
#include <mysql.h>
#include <wininet.h>
#include <string>

class MySQL
{
private:
MYSQL *connection;

public:
MySQL();
~MySQL();
bool MySQL::CheckPassword(char *pw, char *salt, char *hash);
int Login(const char* id, const char* pw, const char* ip, const char* hwid);
int Login(const char* id, const char* ip);
void GetUserInfo(int,MyCharInfo&);
void SetDefaultCharacter(int,Character);
bool IsUserActive(const char*);
void GetExp(int usr_id, int usr_exp,const char *Elements, int Ammount, int Level);
void InsertNewItem(int usr_id,int validslot,int item,int gf,int level,int skill);
bool IsUser(const char *name);
bool MySQL::RegisterUser(const char* id, const char* pw, const char* ip);
bool VerifyLogin(const char* id, const char* pw, const char* ip, const char* hwid);
std::string GetSyncData();
};


#endif
