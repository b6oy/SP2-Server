#include <ctime>

#include "UserInfo.h"

UserLoginInfo::UserLoginInfo(const string& password, bool isDeleted, int banExpirationDate)
    : isDeleted(isDeleted), banExpirationDate(banExpirationDate), password(password)
{
}

const string& UserLoginInfo::GetPassword() const
{
    return this->password;
}

bool UserLoginInfo::IsDeleted() const
{
    return this->isDeleted;
}

bool UserLoginInfo::IsBanned() const
{
    return this->IsPermanentlyBanned() || (int)time(0) < this->banExpirationDate;
}

bool UserLoginInfo::IsPermanentlyBanned() const
{
    return this->banExpirationDate == -1;
}

pt::ptime UserLoginInfo::GetBanExpirationDate() const
{
    return pt::from_time_t((time_t)this->banExpirationDate);
}

IpBanInfo::IpBanInfo(int banExpirationDate)
    : banExpirationDate(banExpirationDate)
{
}

bool IpBanInfo::IsBanned() const
{
    return this->IsPermanentlyBanned() || (int)time(0) < this->banExpirationDate;
}

bool IpBanInfo::IsPermanentlyBanned() const
{
    return this->banExpirationDate == -1;
}

pt::ptime IpBanInfo::GetBanExpirationDate() const
{
    return pt::from_time_t((time_t)this->banExpirationDate);
}

UserPostLoginInfo::UserPostLoginInfo(bool isMale, int auth, int defaultCharacter,
    int rank, int rankRecord, long long int points, long long int code)
    : isMale(isMale), auth(auth), defaultCharacter(defaultCharacter), rank(rank),
    rankRecord(rankRecord), points(points), code(code)
{
}

bool UserPostLoginInfo::IsMale() const
{
    return this->isMale;
}

int UserPostLoginInfo::GetAuth() const
{
    return this->auth;
}

bool UserPostLoginInfo::HasDefaultCharacter() const
{
    return (this->defaultCharacter != 0);
}

int UserPostLoginInfo::GetDefaultCharacter() const
{
    return this->defaultCharacter;
}

Rank UserPostLoginInfo::GetRank() const
{
    return (Rank)this->rank;
}

bool UserPostLoginInfo::IsDoneTraining() const
{
    return (this->GetRankRecord() > 0);
}

Rank UserPostLoginInfo::GetRankRecord() const
{
    return (Rank)this->rankRecord;
}

long long int UserPostLoginInfo::GetPoints() const
{
    return this->points;
}

long long int UserPostLoginInfo::GetCode() const
{
    return this->code;
}

bool UserPostLoginInfo::HasGuild() const
{
    return false; // TODO
}

const string& UserPostLoginInfo::GetGuildName() const
{
    return string(); // TODO
}

const string& UserPostLoginInfo::GetGuildTitle() const
{
    return string(); // TODO
}

