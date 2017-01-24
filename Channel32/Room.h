#ifndef __ROOM_H__
#define __ROOM_H__
#include <vector>
#include <SpServer.h>
#include "User.h"
#include "MySQL.h"
#include "all_messages.h"

class Room
{
public:
	Room();
	void SetChannelType(int ct);
	bool Create(User *Master, int n, char title[29], char password[16], int mode, int map, int maxp, char allowscrolls, char autoteam, int maxcardlevel, char allowcritsheild);
	int Join(User *Player, char *password);
	void Reset();
	bool ExitPlayer(User *player);
	void Send(const Message* message, int slot=-1, int exclude=-1);
	void SendTo(const Message* message, int slot, UdpServer *udp);
	bool Started();
	void GetPlayerData(MySQL *MySql, User *Player, int slot);
	void SendPlayerData(MySQL *MySql, int slot, bool wasReady = false);
	void SendNpcListMsg(const NpcListMessage *msg);
	void SendResultsResponse(int *results);
	void StartGame();
	int* GetChars();
	int* GetLevels();
	bool* GetGenders();
	char* GetTitle();
	char** GetUsernames();
	int GetMode();
	int GetMap();
	int GetCapacity();
	int GetMaster();
	int GetProgress();
	int GetKing();
	void SetKing(int newking);
	User* GetUser(int slot);
	MyCharInfo* GetUserInfo(int slot);
	bool IsOpen();
	bool IsStarted();
	bool IsPassworded();
	bool IsPotion();
	bool IsClosed();
	bool IsPremium();
	bool IsAllowScrolls();
	bool IsAllowCritShield();
	bool IsQuestMode();
	bool Is5WinsMode();
	bool Is3WinsMode();
	bool Is3KillsMode();
	bool IsSingleWinMode();
	bool IsVSMode();
	bool IsTeamlessMode();
	bool IsKingMode();
	int GetValidSlot();
	void SetTitle(char *title);
	bool UpdateProgress(int progress);
	int GetTeam(int slot);
	int GetTeamWins(int team);
	int GetUserTeam(int slot);
	int GetBBMKills(int team);
	void SetBBMKills(int team, int kills);
	void GetResults(int team, int result);
	int GetUserGameLife(bool questlife);
	bool IsAllDead();
	bool IsTeamDead(int team);
	void SetWinningTeam(int team, int wincount=1);
	void SetWinningPlayer(int player, int killer, int wincount=1);
	int  GetTeamPlayersCount(int team);
	int  GetTeamReadyPlayersCount(int team);
	void SetMapType(int type);
	bool SetSymbolTeam(int symbol, int team);
	void GetSlots(int slots[8]);
	char* GetBBX();
	int GetNewMission();
	void GetOpenShops(User* user);
	bool AddMolePoints(int team, int points);
	int AddGoal(int goal);
	void EnterUserTurn(User* user);
	void LeaveUserTurn(User* user);
	void GetTurns(int *slots);
	void NpcKilled(int npcNum);
	bool IsNpcKilled(int npcNum);
	void InitCrystals();

	boost::mutex roomLock;
	boost::mutex slotLock;

private:
	int n, p, master, progress, mission,king, time;
    bool started;
    char title[29];
	char password[16];
    int mode,map,maxp,mapType;
    int level[8];
	int life[8];
    bool gender[8];
	int Team1, Team2, BBMTeam1, BBMTeam2;
	int Symbol[4];
	char allowscrolls; //1
    char autoteam; //0
    int maxcardlevel; //-1
    char allowcritsheild;
	User* users[8];
	int chars[8];
	char** username;
	char BBX[36];
	int kills[8];
	short crystals[8];
	std::vector<int> deadNpc;
};

#endif // __ROOM_H__
