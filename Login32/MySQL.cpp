#include "MySQL.h"
#include "ini.h"
#include <md5.h>

extern CIni config;

MySQL::MySQL()
{
	/*config.SetSection("DB");
	char * ip = config.ReadString("ip", "178.162.181.68");
	uint32 port = config.ReadInteger("port", 3306);
	char * user = config.ReadString("user", "sp");
	char * pw = config.ReadString("pw", "pserver1");
	char * db = config.ReadString("db", "sp_db");*/
	connection = mysql_init(0);
	//95.211.178.168
	int failed = 0;
	while(!mysql_real_connect(connection, "127.0.0.1", "root", "spservertest", "sp_db", 3306, 0, 0) && failed < 6){
		failed++;
		Sleep(1000);
	}
       
	if(failed >= 6){
		printf("Unable to connect to MySQL server\n");
		ExitProcess(0);
	}
}

MySQL::~MySQL()
{
	mysql_close(connection);
}

bool MySQL::CheckPassword(char *pw, char *salt, char *hash)
{
	return true;
	MD5 md5 ;
	char pw5[63];
	for(int i = 0; i < 63; i++)
		pw5[i] = 0;
	strcpy((char*)pw5,md5.digestString(pw));
	//printf("pw5 %s\n", pw5);
	strncpy((char*)(pw5+32),salt,30);
	//printf("pw5 %s\n", pw5);
	//printf("md5 %s\n", md5.digestString(pw5));
	if(strncmp(hash,md5.digestString(pw5),32) == 0)
		return true;
	return false;
}

int MySQL::Login(const char* id, const char* pw, const char* ip, const char* hwid)
{
	if(VerifyLogin(id,pw, ip, hwid))
	{
    char buffer[200];
    sprintf(buffer,"SELECT usr_id FROM users WHERE usr_name = \'%s\'",id);
    mysql_query(connection,buffer);
    MYSQL_RES *res = mysql_use_result(connection);
	if(!res)
		return 0;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)return 0;
    int x = atoi(result[0]);
    mysql_free_result(res);

    return x;
	}
	return 0;
}

int MySQL::Login(const char* id, const char* ip)
{
    char buffer[200];
    sprintf(buffer,"SELECT usr_id FROM users WHERE usr_name = \'%s\' AND usr_ip = \'%s\'",id,ip);
    mysql_query(connection,buffer);
    MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)return 0;
    int x = atoi(result[0]);
    mysql_free_result(res);
    return x;
}

void MySQL::GetUserInfo(int id, MyCharInfo &info)
{
    char buffer[200];
    sprintf(buffer,"SELECT usr_char, usr_points, usr_code, usr_level, usr_type FROM users WHERE usr_id = %d",id);
    if(mysql_query(connection,buffer))
        printf(mysql_error(connection));
    MYSQL_RES *res = mysql_use_result(connection);
	if(!res)
		return;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)
    {
        printf("No Data\n");
        return;
    }
    info.DefaultCharacter = atoi(result[0]);
    info.Points = _atoi64(result[1]);
    info.Code = _atoi64(result[2]);
    info.Level = (int)_atoi64(result[3]);
	info.eleType = atoi(result[4]);
	if(info.Level > 0 && info.Level <= 12)
		info.UserType = 10;
	else if(info.Level > 12 && info.Level <= 16)
		info.UserType = 20;
	else if(info.Level > 16)
		info.UserType = 30;
	else info.UserType = 0;
    mysql_free_result(res);
	Level level;
	int l = level.getLevel(info.Points);
	if(info.Level != l){
			sprintf(buffer,"UPDATE users SET usr_level = %d WHERE usr_id = %d",l,id);
		if(mysql_query(connection,buffer))
			printf(mysql_error(connection));
		info.Level = l;
	}
}

void MySQL::SetDefaultCharacter(int id,Character DefaultCharacter)
{
    char buffer[200];
    sprintf(buffer,"UPDATE users SET usr_char = %d WHERE usr_id = %d",DefaultCharacter,id);
    mysql_query(connection,buffer);
}

bool MySQL::IsUserActive(const char *username)
{
	return false;
	char buffer[200];
	sprintf(buffer,"SELECT * FROM active_list WHERE usr_name = \'%s\' AND time > date_sub(CURRENT_TIMESTAMP, INTERVAL 1 MINUTE)",username);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)
		return false;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)
		return false;
     mysql_free_result(res);
	 return true;
}

void MySQL::GetExp(int usr_id, int usr_exp,const char *Elements, int Ammount, int Level)
{
	char buffer[300];
	if(Elements)
	sprintf(buffer,"UPDATE users SET usr_level = %d,usr_points = (usr_points+%d),usr_code = (usr_code+%d),usr_%s = %d  WHERE usr_id = %d",Level,usr_exp,usr_exp,Elements,Ammount,usr_id);
	else sprintf(buffer,"UPDATE users SET usr_points = (usr_points+%d),usr_code = (usr_code+%d)  WHERE usr_id = %d",usr_exp,usr_exp,usr_id);
	mysql_query(connection,buffer);
}

void MySQL::InsertNewItem(int usr_id,int validslot,int item,int gf,int level,int skill)
{
    char buffer[200];
    //sprintf(buffer,"INSERT INTO items VALUES (0,%d,%d,%d,%d,%d,%d)",validslot,usr_id,item,gf,level,skill);
	sprintf(buffer,"INSERT INTO items VALUES (0,%d,%d,%d,DATE_ADD(NOW(), INTERVAL %d DAY),%d,%d)",validslot,usr_id,item,gf,level,skill);
	mysql_query(connection,buffer);
}

bool MySQL::IsUser(const char *name)
{
	char buffer[200];
    sprintf(buffer,"SELECT usr_id FROM users WHERE usr_name = \'%s\'",name);
    mysql_query(connection,buffer);
    MYSQL_RES *res = mysql_use_result(connection);
	if(!res)
		return false;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)return false;
    int x = atoi(result[0]);
    mysql_free_result(res);
    return x > 0;
}

bool MySQL::RegisterUser(const char* id, const char* pw, const char* ip)
{
	return true;
	char buffer[300];
	MYSQL *forum;
	forum = mysql_init(0);
	//95.211.178.168
	mysql_real_connect(forum, "127.0.0.1", "sp", "pserver1", "forum", 3306, 0, 0);
	sprintf(buffer,"SELECT userid, password, salt FROM user WHERE userid > 0 AND username = \'%s\'",id);
	mysql_query(forum,buffer);
	MYSQL_RES *res = mysql_use_result(forum);
	if(!res){
		mysql_close(forum);
		return false;
	}
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result){
		mysql_close(forum);
		return false;
	}
	int userid = atoi(result[0]);
	char hash[33];
	char salt[31];
	int gender = 0;
	strcpy(hash,result[1]);
	strcpy(salt,result[2]);
	mysql_free_result(res);

	sprintf(buffer,"SELECT field5 FROM userfield WHERE userid = %d",userid);
	mysql_query(forum,buffer);
	res = mysql_use_result(forum);
	if(!res){
		mysql_close(forum);
		return false;
	}
    result = mysql_fetch_row(res);
    if(!result){
		mysql_close(forum);
		return false;
	}

	if(strcmp(result[0],"Male") == 0)
		gender = 1;

	mysql_free_result(res);
	mysql_close(forum);

	if(!CheckPassword((char*)pw,salt,hash))
		return false;
	sprintf(buffer,"INSERT INTO equipments(usr_id) VALUES (0)");
	mysql_query(connection,buffer);
    sprintf(buffer,"INSERT INTO users(usr_gender,usr_name,usr_pw,usr_ip) VALUES (%d,\'%s\',\'%s\',\'%s\')",gender,id,"pw",ip);
    mysql_query(connection,buffer);
	return true;
}

bool MySQL::VerifyLogin(const char* id, const char* pw, const char* ip,  const char* hwid)
{
	//return true;

	static CHAR hdrs[] = "Content-Type: application/x-www-form-urlencoded";
	static CHAR frmdata[1000];
	sprintf(frmdata, "r=auth&id=%s&pw=%s", id, pw);
	static LPCSTR accept[2] = { "*/*", NULL };
	HINTERNET hSession = InternetOpenA("spserver", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	HINTERNET hConnect = InternetConnectA(hSession, "spgame.net", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
	HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/sp.php", NULL, NULL, accept, INTERNET_FLAG_SECURE, 1);
	HttpSendRequestA(hRequest, hdrs, strlen(hdrs), frmdata, strlen(frmdata));
	char szBuffer[1025];
	DWORD dwRead = 0;
	while (InternetReadFile(hRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead) {
		szBuffer[dwRead] = 0;
		dwRead = 0;
	}

	InternetCloseHandle(hSession);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hRequest);
	int gender = 0;
	if (szBuffer[0] == '1')
	{
		if (strncmp(&szBuffer[2], "Male", 4) == 0)
			gender = 1;
		int index = 3, type = 0;
		while (szBuffer[index] != ';' && index < 50)
		{
			index++;
		}
		if (strncmp(&szBuffer[index + 1], "Water", 5) == 0)
			type = 1;
		if (strncmp(&szBuffer[index + 1], "Fire", 4) == 0)
			type = 2;
		if (strncmp(&szBuffer[index + 1], "Earth", 5) == 0)
			type = 3;
		if (strncmp(&szBuffer[index + 1], "Wind", 4) == 0)
			type = 4;
		if (!IsUser(id))
		{
			char buffer[500];
			sprintf(buffer, "INSERT INTO equipments(usr_id) VALUES (0)");
			mysql_query(connection, buffer);
			sprintf(buffer, "INSERT INTO users(usr_gender,usr_name,usr_hwid,usr_ip,usr_type) VALUES (%d,\'%s\',\'%s\',\'%s\',%d)", gender, id, hwid, ip,type);
			mysql_query(connection, buffer);
		}
		else {
			char buffer[500];
			sprintf(buffer, "UPDATE users SET usr_gender = %d, usr_hwid = \'%s\', usr_ip = \'%s\', usr_type = %d WHERE usr_name = \'%s\' AND usr_id >= 0", gender, hwid, ip, type, id);
			mysql_query(connection, buffer);

		}

		return true;
	}
	return false;
}

std::string MySQL::GetSyncData()
{
	string data = "";

	char buffer[1000];
	sprintf(buffer, "SELECT usr_name, usr_level, usr_code, usr_cash, usr_water, usr_fire, usr_earth, usr_wind FROM users WHERE time > date_sub(CURRENT_TIMESTAMP, INTERVAL 1 MINUTE)");
	mysql_query(connection, buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if (!res)
		return data;
	MYSQL_ROW result;
	//int x = atoi(result[0]);

	while (result = mysql_fetch_row(res))
	{
		for (int i = 0; i < 8; i++)
		{
			data.append(result[i]);
			data.append(";");
		}
	}


	mysql_free_result(res);

	//return "Milk;1;1;1;2;2;2;2;";
	return data;
}