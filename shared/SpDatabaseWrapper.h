#ifndef __SPDATABASEWRAPPER_H__
#define __SPDATABASEWRAPPER_H__

#include "UserInfo.h"

class ConnectionSettings
{
public:
    ConnectionSettings(const string& host, unsigned int port, const string& userName, const string& password);
    const string& GetHost() const;
    unsigned int GetPort() const;
    const string& GetUserName() const;
    const string& GetPassword() const;

private:
    string host;
    unsigned int port;
    string userName;
    string password;
};

class SpDatabaseWrapperImpl;

class SpDatabaseWrapper
{
public:
    SpDatabaseWrapper(const string& host, unsigned int port, const string& userName, const string& password);
    SpDatabaseWrapper(ConnectionSettings settings);
    SpDatabaseWrapper();
    ~SpDatabaseWrapper();

    static void SetDefaultConnectionSettings(ConnectionSettings settings);

    int CreateUser(const string& name, const string& password, bool isMale, const string& creationIp = string());
    int GetUserId(const string& userName); // returns 0 if there isn't any user with that name
    UserLoginInfo GetUserLoginInfo(int userId);
    IpBanInfo GetIpBanInfo(const string& ip);
    int CreateUserBan(int userId, time_t banExpirationDate = -1);
    int CreateIpBan(const string& ip, time_t banExpirationDate = -1);
    void CreateOrUpdateUserIp(int userId, const string& ip);
    void UpdateUserLastLoginDate(int userId);
    void UpdateUserLastLoginServerOnlineDate(int userId);
    void UpdateUserLastGameServerOnlineDate(int userId);
    UserPostLoginInfo GetUserPostLoginInfo(int userId);

private:
    static ConnectionSettings defaultConnectionSettings;

    SpDatabaseWrapperImpl* impl;
};

#endif // __SPDATABASEWRAPPER_H__