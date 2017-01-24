#ifndef __USERINFO_H__
#define __USERINFO_H__

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pt = boost::posix_time;

using namespace std;

class UserInfoHelper;
class UserLoginInfo;
class UserPostLoginInfo;
class IpBanInfo;

enum LoginResultType
{
    LOGIN_RESULT_SUCCESS = 1,
    LOGIN_RESULT_WRONG_PASSWORD = 0,
    LOGIN_RESULT_ALREADY_CONNECTED = -4
};

enum ChannelAccessLevel
{
    CHANNEL_ACCESS_NONE = 0,
    CHANNEL_ACCESS_BEGINNER = 10,
    CHANNEL_ACCESS_HERO = 20,
    CHANNEL_ACCESS_EPIC = 30
};

enum Rank
{
    RANK_STONE = 0,
    RANK_JADE_1 = 1,
    RANK_JADE_2 = 2,
    RANK_JADE_3 = 3,
    RANK_JADE_4 = 4,
    RANK_TOPAZ_1 = 5,
    RANK_TOPAZ_2 = 6,
    RANK_TOPAZ_3 = 7,
    RANK_TOPAZ_4 = 8,
    RANK_OPAL_1 = 9,
    RANK_OPAL_2 = 10,
    RANK_OPAL_3 = 11,
    RANK_OPAL_KING = 12,
    RANK_GOLD_1 = 13,
    RANK_GOLD_2 = 14,
    RANK_GOLD_3 = 15,
    RANK_GOLD_KING = 16,
    RANK_STAR_1 = 17,
    RANK_STAR_2 = 18,
    RANK_STAR_3 = 19,
    RANK_KING_STAR = 20,
    RANK_MOON_1 = 21,
    RANK_MOON_2 = 22,
    RANK_MOON_3 = 23,
    RANK_MOON_KING = 24,
    RANK_SUN_1 = 25,
    RANK_SUN_2 = 26,
    RANK_SUN_3 = 27,
    RANK_KING_SUN = 28,
    RANK_SOLAR_1 = 29,
    RANK_SOLAR_2 = 30,
    RANK_SOLAR_3 = 31,
    RANK_SOLAR_KING = 32
};

class UserLoginInfo
{
public:
    UserLoginInfo(const string& password, bool isDeleted, int banExpirationUnixDate);
    const string& GetPassword() const;
    bool IsDeleted() const;
    bool IsBanned() const;
    bool IsPermanentlyBanned() const;
    pt::ptime GetBanExpirationDate() const;

private:
    string password;
    bool isDeleted;
    int banExpirationDate; // -1 for permanently banned
};

class UserPostLoginInfo
{
public:
    UserPostLoginInfo(bool isMale, int auth, int defaultCharacter,
        int rank, int rankRecord, long long int points, long long int code);
    bool IsMale() const;
    int GetAuth() const;
    bool HasDefaultCharacter() const;
    int GetDefaultCharacter() const;
    Rank GetRank() const;
    bool IsDoneTraining() const;
    Rank GetRankRecord() const;
    long long int GetPoints() const;
    long long int GetCode() const;
    bool HasGuild() const; // TODO
    const string& GetGuildName() const; // TODO
    const string& GetGuildTitle() const; // TODO

private:
    bool isMale;
    int auth;
    int defaultCharacter; // 0 for not set
    int rank;
    int rankRecord;
    long long int points;
    long long int code;
};

class IpBanInfo
{
public:
    IpBanInfo(int banExpirationDate);
    bool IsBanned() const;
    bool IsPermanentlyBanned() const;
    pt::ptime GetBanExpirationDate() const;

private:
    int banExpirationDate; // -1 for permanently banned
};

#endif // __USERINFO_H__