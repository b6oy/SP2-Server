#include <cstring>
#include <cstdlib>
#include <time.h>
#include "Room.h"

int nulled[20] = {0};
int ChannelType = 1;

void Room::SetChannelType(int ct)
{
	ChannelType = ct;
}

Room::Room()
{
	username = new char *[8];
	for( int i = 0 ; i < 8 ; i++ )
		username[i] = new char[13];
	Reset();
}

bool Room::Create(User *Master, int n, char title[29], char password[16], int mode, int map, int maxp, char allowscrolls, char autoteam, int maxcardlevel, char allowcritsheild)
{
	if(this->n != -1)return false;
	Reset();
	deadNpc.clear();
	users[0] = Master;
	this->n = n;
	strcpy(this->title,title);
	strcpy(this->password,password);
	this->mode = mode;
	this->map = map;
	if(mode == 1)
		this->maxp = 6;
	else this->maxp = maxp;
	this->allowscrolls = allowscrolls;
	this->autoteam = autoteam;
	this->maxcardlevel = maxcardlevel;
	this->allowcritsheild = allowcritsheild;
	mapType = -1;
	MyCharInfo *Info = Master->GetInfo();
	chars[0] = Info->DefaultCharacter;
	level[0] = Info->Level;
	gender[0] = Info->gender;
	strcpy(username[0],Info->usr_name);
	Master->SetInRoomData(n,0,0,chars[0],0,mode,GetTeam(0),-1);
	p = 1;
	if(mode == MISSION_MODE)
		mission = Info->Mission;
	if(mode == BB_SURVIVAL)
		for(int i = 0; i < 36; i++)
			BBX[i] = 10;
	if(mode == COMMUNITY_MODE || mode == FIGHT_CLUB_MODE)
		started = true;
	return true;
}

int Room::Join(User *Player, char *password)
{
	if(n == -1)return 1;
	if(strcmp(this->password, password) != 0 && strcmp("@master", password) != 0)return 2;
	if(p == maxp)return 3;
	if(progress >= 35)return 4;
	if (mode == MISSION_MODE && started)return 4;
	slotLock.lock();
	int slot = GetValidSlot();
	if(slot == -1){
		slotLock.unlock();
		return false;
	}
	MyCharInfo *Info = Player->GetInfo();
	users[slot] = Player;
	chars[slot] = Info->DefaultCharacter;
	level[slot] = Info->Level;
	gender[slot] = Info->gender;
	strcpy(username[slot],Info->usr_name);
	Player->SetInRoomData(n,0,slot,chars[slot],master,mode,GetTeam(slot),-1);
	p++;
	slotLock.unlock();
	return 0;
}

void Room::Reset()
{
	for(int i = 0; i < 8; i++){
		users[i] = 0;
		level[i] = -99;
		gender[i] = false;
		chars[i] = 0;
		kills[i] = 0;
		crystals[i] = 0;
		for(int j = 0; j < 13; j++)
			username[i][j] = 0;
	}
	p = master = progress = mission = king = 0;
	Team1 = Team2 = 0;
	mode = map = maxp = 0;
	started = false;
	for(int i = 0; i < 29; i++)title[i] = 0;
	for(int i = 0; i < 16; i++)password[i] = 0;
	n = -1;
	deadNpc.clear();
}

bool Room::ExitPlayer(User *player)
{
	slotLock.lock();
	roomLock.lock();
	MyCharInfo *Info = player->GetInfo();
	int team = Info->usr_team, Master = -1, King = -1, islot = Info->usr_slot;
	users[islot] = 0;
	slotLock.unlock();
	Info->TradeProgress = 0;
	player->SetInRoomData(-1,0,0,0,0,0,0,0);
	p--; 
	if(p && islot == master){
		for(int i = 0; i < maxp; i++)
			if(users[i] && i != master)
			{
				Master = i;
				break;
			}
			if(IsKingMode())
				for(int i = 0; i < maxp; i++)
					if(users[i] && i != king)
					{
						King = i;
						break;
					}
	}
	roomLock.unlock();
	if(Master != -1)
		Send(&NewMasterResponseMessage(master=Master));
	if(IsKingMode()){
		if(King != -1)
			Send(&NewKingResponseMessage(king=King));
	}
	if(started){
		if(IsVSMode() && !GetTeamPlayersCount(team))
			SetWinningTeam(team == 10 ? 10: 20, team == 10 ? 3-Team2: 3-Team1);
		else if(IsTeamlessMode() && GetTeamPlayersCount(team) == 1)
			SetWinningPlayer(master,master, 3);
	}
	if(p == 0){
		Reset();
		return true;
	}
	return false;
}

void Room::Send(const Message* message, int slot, int exclude)
{
	roomLock.lock();
	__try {
	if(slot == -1){
		for(int i = 0; i < maxp; i++)
			if(i != exclude)if(users[i])users[i]->GetTcpSocket().Send((Message &)*message);
	}else if(slot >= 0 && slot < maxp)
		if(users[slot])
			if(users[slot]->GetInfo())users[slot]->GetTcpSocket().Send((Message &)*message);
	}__except(true){
		cout << "Room Send Crash" << endl;
		roomLock.unlock();
		return;
	}
	roomLock.unlock();
}

void Room::SendTo(const Message* message, int slot, UdpServer *udp)
{
	roomLock.lock();
	if(slot >= 0 && slot < maxp)
		if(users[slot])udp->ForwardTo((Message &)*message,users[slot]->GetUdpEndpoint());
	roomLock.unlock();
}

bool Room::Started()
{
	return started;
}

void Room::GetPlayerData(MySQL *MySql, User *Player, int slot)
{
	if(slot >= 0 && slot < 8){
		roomLock.lock();
		if(users[slot]){
		MyCharInfo *Info = users[slot]->GetInfo();
		int magictype = 0, weapontype = 0, armortype = 0, pettype = 0;
		int magiclevel = 0, weaponlevel = 0, armorlevel = 0, petlevel = 0;
		int magicgf = 0, weapongf = 0, armorgf = 0, petgf = 0;
		int magicskill = 0, weaponskill = 0, armorskill = 0, petskill = 0;
		int foot = 0, body = 0, hand1 = 0, hand2 = 0, face = 0, hair = 0, head = 0;
		int character = Info->usr_char;
		int Gamestart = 2;
		if(started == true && Player->GetInfo()->usr_ready)Gamestart = 0;
		if(character == 0 || character > 1000)character = Info->DefaultCharacter+Info->premium;
		if(Info->usr_power)
			magiclevel = weaponlevel = armorlevel = Info->usr_power;
		MySql->GetEquipData(Info->usr_id,magictype,weapontype,armortype,pettype,magiclevel,weaponlevel,armorlevel,petlevel,magicgf,weapongf,armorgf,petgf,magicskill,weaponskill,armorskill,petskill,foot,body,hand1,hand2,face,hair,head);
		
		int maxLevel = 8;
		if (ChannelType == 2)
			maxLevel = 5;
		if (ChannelType == 1)
			maxLevel = 3;
		if (magiclevel > maxLevel)
			magictype = magicskill = magicgf = magiclevel = 0;
		if (weaponlevel > maxLevel)
			weapontype = weaponskill = weapongf = weaponlevel = 0;
		if (armorlevel > maxLevel)
			armortype = armorskill = armorgf = armorlevel = 0;
		
		Player->GetTcpSocket().Send(RoomUserDataMessage(Info->usr_slot,users[slot]->GetGlobalIP(),users[slot]->GetLocalIP(),Info->Level,Info->usr_name,Info->gender,
			Info->usr_ready,character,Info->usr_team,magictype,weapontype,armortype,pettype,magiclevel,
			weaponlevel,armorlevel,petlevel,magicgf,weapongf,armorgf,petgf,magicskill,weaponskill,armorskill,petskill,
			Info->scrolls, foot, body, hand1, hand2, face, hair, head, Gamestart, false, mission, Info->Mission));
		}
		roomLock.unlock();
	}
}

void Room::SendPlayerData(MySQL *MySql, int slot, bool wasReady)
{
	if(slot >= 0 && slot < 8){
		if(users[slot] == 0)return;
		slotLock.lock();
		MyCharInfo *Info = users[slot]->GetInfo();
		int magictype = 0, weapontype = 0, armortype = 0, pettype = 0;
		int magiclevel = 0, weaponlevel = 0, armorlevel = 0, petlevel = 0;
		int magicgf = 0, weapongf = 0, armorgf = 0, petgf = 0;
		int magicskill = 0, weaponskill = 0, armorskill = 0, petskill = 0;
		int foot = 0, body = 0, hand1 = 0, hand2 = 0, face = 0, hair = 0, head = 0;
		int character = Info->usr_char;
		int Gamestart = 2;
		bool join = !wasReady && started ? true : false;
		if(Info->usr_ready){
			StartGame();
			if(started == true)Gamestart = 0;
		}else 
			join = false;
		if(character == 0 || character > 1000)character = Info->DefaultCharacter+Info->premium;
		MySql->GetEquipData(Info->usr_id,magictype,weapontype,armortype,pettype,magiclevel,weaponlevel,armorlevel,petlevel,magicgf,weapongf,armorgf,petgf,magicskill,weaponskill,armorskill,petskill,foot,body,hand1,hand2,face,hair,head);
		
		int maxLevel = 8;
		if (ChannelType == 2)
			maxLevel = 5;
		if (ChannelType == 1)
			maxLevel = 3;
		if (magiclevel > maxLevel)
			magictype = magicskill = magicgf = magiclevel = 0;
		if (weaponlevel > maxLevel)
			weapontype = weaponskill = weapongf = weaponlevel = 0;
		if (armorlevel > maxLevel)
			armortype = armorskill = armorgf = armorlevel = 0;
		
		for(int i = 0; i < maxp; i++)
		{
			if(users[i])
			{
				int gameStarted = Gamestart;
				MyCharInfo uInfo;
				users[i]->GetCharInfo(uInfo);
				if(uInfo.usr_ready == 0)
					gameStarted = 2;
				if(uInfo.usr_power)
					magiclevel = weaponlevel = armorlevel = uInfo.usr_power;
				Send(&RoomUserDataMessage(Info->usr_slot,users[slot]->GetGlobalIP(),users[slot]->GetLocalIP(),Info->Level,Info->usr_name,Info->gender,
					Info->usr_ready,character,Info->usr_team,magictype,weapontype,armortype,pettype,magiclevel,
					weaponlevel,armorlevel,petlevel,magicgf,weapongf,armorgf,petgf,magicskill,weaponskill,armorskill,petskill,
					Info->scrolls, foot, body, hand1, hand2, face, hair, head, gameStarted, join, mission, Info->Mission),i);
			}
		}
		slotLock.unlock();
	}
}

void Room::SendNpcListMsg(const NpcListMessage *msg)
{
	slotLock.lock();
	for(int i = 0; i < maxp; i++)
	{
		if(users[i])
		{
			MyCharInfo *uInfo = users[i]->GetInfo();
			if(uInfo->usr_ready)
				Send(msg,i);
		}
	}
	slotLock.unlock();
}

void Room::SendResultsResponse(int *results)
{
	int zeros[8] = {0,0,0,0,0,0,0,0};
	roomLock.lock();
	for(int i = 0; i < maxp; i++){
		if(users[i]){
			MyCharInfo *uInfo = users[i]->GetInfo();
			users[i]->GetTcpSocket().Send(ResultsResponseMessage(results,zeros,zeros,uInfo->Points,uInfo->Code));
		}
	}
	roomLock.unlock();
}

void Room::StartGame()
{
	if(!started){
		for(int i = 0; i < maxp; i++)
			if(users[i])
				if(users[i]->GetInfo()->usr_ready == 0)return;
		if(IsVSMode()){
			if(mode == HERO_MODE){
				if(p <= 1)return;
			}else if(GetTeamPlayersCount(10) != GetTeamPlayersCount(20))return;
		}
		time = clock();
		started = true;
		Team1 = Team2 = 0;
		BBMTeam1 = BBMTeam2 = 0;
		deadNpc.clear();
		for(int i = 0; i < 8; i++)
			kills[i] = 0;
		if(mode == CRYSTAL_MODE)
		{
			InitCrystals();
		}
	}
}

int* Room::GetChars()
{
	roomLock.lock();
	for(int i = 0; i < 8; i++){
		__try {
		if(users[i]){
			//chars[i] = users[i]->GetInfo()->usr_char;
			MyCharInfo info;
			users[i]->GetCharInfo(info);
			chars[i] = info.usr_char;
		}else chars[i] = 0;
		}__except(true){
			cout << "Char Crash Blocked" << endl;
			//chars[i] = 0;
			roomLock.unlock();
			return nulled;
		}
	}
	roomLock.unlock();
	return chars;
}

int* Room::GetLevels()
{
	roomLock.lock();
	for(int i = 0; i < maxp; i++){
		__try {
		if(users[i]){
			MyCharInfo info;
			users[i]->GetCharInfo(info);
			level[i] = info.Level;
		}else level[i] = -99;
		}__except(true){
			cout << "Level Crash Blocked" << endl;
			roomLock.unlock();
			return nulled;
		}
	}
	roomLock.unlock();
	return level;
}

bool* Room::GetGenders()
{
	return gender;
}

char* Room::GetTitle()
{
	return title;
}

int Room::GetMode()
{
	return mode;
}

char** Room::GetUsernames()
{
	return username;
}

int Room::GetMap()
{
	return map;
}

int Room::GetCapacity()
{
	if(maxp > 8)
		maxp = 6;
	return maxp;
}

int Room::GetMaster()
{
	return master;
}

int Room::GetProgress()
{
	return progress;
}

int Room::GetKing()
{
	return king;
}

void Room::SetKing(int newking)
{
	king = newking;
}

User* Room::GetUser(int slot)
{
	User* user = 0;
	roomLock.lock();
	if(users[slot])user = users[slot];
	roomLock.unlock();
	return user;
}

MyCharInfo* Room::GetUserInfo(int slot)
{
	MyCharInfo* uInfo = 0;
	roomLock.lock();
	if(users[slot])uInfo = users[slot]->GetInfo();
	roomLock.unlock();
	return uInfo;
}

bool Room::IsOpen()
{
	return n != -1;
}

bool Room::IsStarted()
{
	return started;
}

bool Room::IsPotion()
{
	return false;
}

bool Room::IsClosed()
{
	if(progress >= 35)return true;
	if(IsVSMode() && started)return true;
	if(p == maxp) return true;
	if (mode == MISSION_MODE)return true;
	return false;
}

bool Room::IsPremium()
{
	return false;
}

bool Room::IsAllowScrolls()
{
	return allowscrolls;
}

bool Room::IsAllowCritShield()
{
	if(IsQuestMode())
		return true;
	return allowcritsheild;
}

bool Room::IsPassworded()
{
	return password[0] != 0;
}

bool Room::IsQuestMode()
{
	if(mode == MISSION_MODE)return true;
	if(mode >= DUNGEON_QUEST_1 && mode <= DUNGEON_QUEST_4)return true;
	return mode >= DUNGEON_QUEST_5 && mode <= FLAME_QUEST_5;
}

bool Room::Is5WinsMode()
{
	if(mode == SURVIVAL_MODE)return true;
	if(mode == K_SURVIVAL_MODE)return true;
	if(mode == BB_SURVIVAL)return true;
	return false;
}

bool Room::Is3WinsMode()
{
	if(mode == TEAMPLAY_MODE)return true;
	if(mode == DUEL_MODE)return true;
	if(mode == ASSAULT_MODE)return true;
	if(mode == SOCCER_MODE)return true;
	if(mode == HOKEY_MODE)return true;
	if(mode == DODGE_MODE)return true;
	if(mode == HERO_MODE)return true;
	if(mode == CRYSTAL_MODE)return true;
	return false;
}

bool Room::Is3KillsMode()
{
	if(mode == LUCKY_3_MODE)return true;
	if(mode == MAGIC_LUCKY_3)return true;
	return false;
}

bool Room::IsSingleWinMode()
{
	if(mode == SYMBOL_MODE)return true;
	if(mode == RACING_MODE)return true;
	if(mode == MOLE_MODE)return true;
	if(mode == SYMBOL_MODE)return true;
	return false;
}

bool Room::IsVSMode()
{
	if(mode == TEAMPLAY_MODE)return true;
	if(mode == DUEL_MODE)return true;
	if(mode == ASSAULT_MODE)return true;
	if(mode == SOCCER_MODE)return true;
	if(mode == HOKEY_MODE)return true;
	if(mode == SYMBOL_MODE)return true;
	if(mode == RACING_MODE)return true;
	if(mode == LUCKY_3_MODE)return true;
	if(mode == MAGIC_LUCKY_3)return true;
	if(mode == MOLE_MODE)return true;
	if(mode == CRYSTAL_MODE)return true;
	if(mode == HERO_MODE)return true;
	if(mode == INFINITY_SURVIVAL)return true;
	if(mode == DODGE_MODE)return true;
	if(mode == TOURNAMENT_MODE)return true;
	return false;
}

bool Room::IsTeamlessMode()
{
	if(mode == LUCKY_3_MODE)return true;
	if(mode == MAGIC_LUCKY_3)return true;
	if(mode == INFINITY_SURVIVAL)return true;
	if(mode == FIGHT_CLUB_MODE)return true;
	return false;
}

bool Room::IsKingMode()
{
	if(mode == K_SURVIVAL_MODE)return true;
	return false;
}

int Room::GetValidSlot()
{
	for(int i = 0; i < maxp; i++)
		if(users[i] == 0)return i;
	return -1;
}

void Room::SetTitle(char *title)
{
	strcpy(this->title,title);
}

bool Room::UpdateProgress(int progress)
{
	this->progress = progress;
	if(this->progress >= 100)
		started = false;
	return !started;
}

int Room::GetTeam(int slot)
{
	if((IsVSMode() && !IsTeamlessMode()) || mode == BM_DEATH_MATCH){
		if(slot%2 == 0)return 10;
		else return 20;
	}
	if(IsQuestMode())return 10;
	if(mode == MISSION_MODE)return 10;
	return 0;
}

int Room::GetTeamWins(int team)
{
	if(team == 10)return Team1;
	return Team2;
}

int Room::GetUserTeam(int slot)
{
	int team = 0;
	roomLock.lock();
	if(slot >= 0 && slot < maxp)
		if(users[slot])
			team = users[slot]->GetInfo()->usr_team;
	roomLock.unlock();
	return team;
}

int Room::GetBBMKills(int team)
{
	if(team == 10)return BBMTeam1;
	return BBMTeam2;
}

void Room::SetBBMKills(int team, int kills)
{
	if(team == 10)BBMTeam1 = kills;
	else BBMTeam2 = kills;
}

void Room::GetResults(int team, int result)
{
	int results[8], points[8], codes[8];
	int opTeam = team == 10 ? 20 : 10, opResult = result == 1 ? 2 : 1;
	roomLock.lock();
	for(int i = 0; i < 8; i++){
		if(users[i]){
			int uteam = users[i]->GetInfo()->usr_team;
			if(uteam == team)results[i] = result;
			else if(uteam == opTeam)results[i] = opResult;
		}else results[i] = -1;
		points[i] = 0;
		codes[i] = 0;
	}
	MySQL MySql;
	for(int i = 0; i < maxp; i++)
		if(users[i]){
			MyCharInfo *Info = users[i]->GetInfo();
			users[i]->GetTcpSocket().Send(ResultsResponseMessage(results,points,codes,Info->Points,Info->Code));
			if(results[i] == 1)
				MySql.AddWin(Info->usr_id);
			else if(results[i] == 2)
				MySql.AddLose(Info->usr_id);
			Info->usr_ready = 0;
			Info->usr_life = 0;
		}
		started = false;
		progress = 0;
		roomLock.unlock();
}

int Room::GetUserGameLife(bool questlife)
{
	if(IsQuestMode())
		return questlife ? 1 : 0;
	if(Is5WinsMode())
		return 5;
	if(mode == BM_DEATH_MATCH)
		return 10;
	return 0;
}

bool Room::IsAllDead()
{
	bool result = true;
	roomLock.lock();
	for(int i = 0; i < maxp; i++)
		if(users[i])
			if(users[i]->GetInfo()->usr_life >= 0){
				result = false;
				break;
			}
			roomLock.unlock();
			return result;
}

bool Room::IsTeamDead(int team)
{
	bool result = true;
	roomLock.lock();
	for(int i = 0; i < maxp; i++)
		if(users[i])
			if(users[i]->GetInfo()->usr_team == team)
				if(users[i]->GetInfo()->usr_life >= 0){
					result = false;
					break;
				}
				roomLock.unlock();
				return result;
}

void Room::SetWinningTeam(int team, int wincount)
{
	MySQL MySql;
	if(team == 10)Team1+=wincount;
	else if(team == 20)Team2+=wincount;
	int results[8], maxrounds[8], EndGame = 0;
	int rounds = 0, eleType = 0, eleBase = 0, eleMul = 0;
	if(Is3WinsMode())rounds = 3;
	if(mode == BM_DEATH_MATCH)rounds = 10;
	if(mode == MISSION_MODE)rounds = 8;
	if(IsSingleWinMode())rounds = 1;
	if(rounds){
		for(int i = 0; i < 8; i++)
			maxrounds[i] = rounds;
		EndGame = (Team1 >= rounds || Team2 >= rounds) ? -1 : 0;
		for(int i = 0; i < 8; i++)
			if(users[i]){
				MyCharInfo *Info = users[i]->GetInfo();
				int uteam = Info->usr_team;
				if(EndGame == -1){
					if(uteam == team)results[i] = 1;
					else results[i] = 2;
					if(results[i] == 1)
						MySql.AddWin(Info->usr_id);
					else if(results[i] == 2)
						MySql.AddLose(Info->usr_id);
					Info->usr_ready = 0;
					if(mode != MISSION_MODE)started = false;
				}else results[i] = 0;
				Info->usr_life = 0;
			}else results[i] = -1;
	}
	int Exp = 20000;

	if (mode == MISSION_MODE)
	{
		for (int i = 0; i < 8; i++) {
			maxrounds[i] = rng100() % 10 + 1;
			int g = rng100() % 4;
			if (g == 0)
				maxrounds[i] = 1;
			else if (g == 1)
				maxrounds[i] = 2;
			else if (g == 2)
				maxrounds[i] = 3;
		}
		Exp = mission%300 * 30;
		if (mission / 300)
		{
			Exp *= pow(1.2, (mission / 300) + 1.0);
		}
	}

	int ExpGain[8];
	if(EndGame == -1){
		eleType = (rng100() % 4) + 1;
		eleBase = (rng100() % 5) + 1;
		eleMul = (rng100() % 4) + 1;

		if (mode == MISSION_MODE)
		{
			eleMul = (rng100() % 4) + 1;
		}

		int nerf = rng100();
		if (nerf % 5 && eleBase > 1) {
			eleBase /= 2;
		}
		if (nerf%2 && eleMul > 6) {
			eleMul -= 3;
		}
		if (mode == MISSION_MODE && mission % 10 == 0)
		{

			if (mission % 301 < 100) {
				//Exp *= (rng100() % 3) + 1;
				//eleMul *= 1;
			}
			else if (mission % 301 < 200) {
				Exp *= (rng100() % 3) + 1;
				eleMul *= 1.2;
			}
			else if (mission % 301 < 270) {
				Exp *= (rng100() % 5) + 2;
				eleMul *= 1.3;
			}
			else {
				Exp *= (rng100() % 7) + 3;
				eleMul *= 2;
			}
		}
		if (mode == MISSION_MODE && mission % 10 == 9)
		{

			if (mission % 301 < 100) {
				//Exp *= (rng100() % 3) + 1;
				//eleMul *= 1;
			}
			else if (mission % 301 < 200) {
				eleMul *= 1.2;
			}
			else if (mission % 301 < 270) {
				eleMul *= 1.3;
			}
			else {
				eleMul *= 2;
			}
		}
	}

	if (p > 3 && p < 8)
	{
		Exp *= 2;
		eleMul *= 1.2;
	}
	else if (p == 8) {
		Exp *= 3;
		eleMul *= 1.5;
	}

	if (clock() - time < 10000) {
		eleMul = 0;
		Exp = 0;
	}
	else if (clock() - time < 30000) {
		eleMul = 1;
		Exp /= 10;
	}
	else if (clock() - time < 60000) {
		eleMul /= 3;
		Exp /= 3;
	}
	else if (clock() - time < 90000) {
		eleMul /= 2;
		Exp /= 2;
	}
	else if (clock() - time < 120000) {
		eleMul /= 1.5;
		Exp /= 1.5;
	}
	else if (clock() - time < 180000) {
		eleMul /= 1.2;
		Exp /= 1.2;
	}
	time = clock();
	if (eleBase > 0 && ChannelType == 1)
	{
		eleBase = 1;
		eleMul = eleMul / 2 + 1;
		Exp /= 5;
	}
	if (eleBase > 0 && ChannelType == 2)
	{
		eleBase = 3;
		eleMul = eleMul / 2 + 1;
		Exp /= 3;
	}

	for(int i = 0; i < 8; i++) {
		if(results[i] == 0)
			ExpGain[i] = 0;
		else if(results[i] == 1)
			ExpGain[i] = Exp;
		else if(results[i] == 2)
			ExpGain[i] = Exp/4;
		else ExpGain[i] = 0;
	}
	//Send(&FightCompleteMessage(results,Team1,Team2,0,0,0,team,maxrounds,EndGame));
	int levels[16];
	for (int i = 0; i < 16; i++)
		levels[i] = -1;
	roomLock.lock();
	for (int i = 0; i < maxp; i++) {
		if (users[i]) {
			MyCharInfo *info = users[i]->GetInfo();
			if (EndGame == -1)
			{
				if (info)
				{
					if (mode == MISSION_MODE)
					{
						if (abs(info->Mission - mission) > 2)
						{
							if (rng100() % 10)
							{
								eleType = 0;
								ExpGain[i] = ExpGain[i] / 100;
							}
							else ExpGain[i] = ExpGain[i] / 10;
						}
						if (info->npc_kills == 0)
						{
							eleType = 0;
							ExpGain[i] = 0;
						}
						else {
							eleMul *= (info->npc_kills % 2) + 1;
							ExpGain[i] *= (info->npc_kills % 3) + 2;
						}

						if (ExpGain[i] * maxrounds[i] > 300000 && mission % 300 < 240)
							maxrounds[i] = 1;
						if (eleMul > 50)
							eleMul = 30 + rng100() % 20;

						if (eleType > 0 && eleType < 5) {
							MySql.GetExp(info->usr_id, ExpGain[i] * maxrounds[i], ElementTypes[eleType], eleBase*eleMul);
						}
						else MySql.GetExp(info->usr_id, ExpGain[i] * maxrounds[i]);
					}
					else {
						if (eleType > 0 && eleType < 5) {
							MySql.GetExp(info->usr_id, ExpGain[i], ElementTypes[eleType], eleBase*eleMul);
						}
						else MySql.GetExp(info->usr_id, ExpGain[i]);
					}
					MySql.UpdateUserInfo(*info);

					Level lvl;
					int l = lvl.getLevel(info->Points);
					if (l > info->Level) {
						levels[i] = l;
					}
				}
			}
		}
	}

	for (int i = 0; i < maxp; i++) {
		if (users[i]) {
			MyCharInfo *info = users[i]->GetInfo();
			if(info)
				users[i]->GetTcpSocket().Send(FightCompleteMessage(results, Team1, Team2, 5, info->Points, info->Code, team, maxrounds, EndGame, ExpGain, eleType, eleBase, eleMul, levels));
			
			/*
			bool bMyCard[96];
			int IDMyCard[96];
			int TypeMyCard[96];
			int GFMyCard[96];
			int LevelMyCard[96];
			int SkillMyCard[96];
			for (int i = 0; i < 96; i++)
			{
				bMyCard[i] = false;
				IDMyCard[i] = 0; TypeMyCard[i] = 0; GFMyCard[i] = 0; LevelMyCard[i] = 0; SkillMyCard[i] = 0;
			}
			MySql.GetUserItems(users[i]->GetId(), bMyCard, IDMyCard, TypeMyCard, GFMyCard, LevelMyCard, SkillMyCard);

			users[i]->GetTcpSocket().Send(LevelUpResponseMessage(bMyCard, TypeMyCard, GFMyCard, LevelMyCard, SkillMyCard, users[i]->GetInfo()->Code, 10, 20, 30, 40));
				/*Item items[10];
				int r = rng100() % 4 + 1;
				for (int i = 0; i < 9; i++)
				{
					int Type = t_items[i] + (r * 10);
					items[i].SetItem(i, Type, 100, 1, 0);
					//MySql.InsertNewItem(user->GetId(), i, Type, 100, 0, 0);
				}
				items[9].SetItem(9, t_items[9] + r, 30, 1, 0);
				Level level;
				users[i]->GetTcpSocket().Send(TrainingCompleteResponseMessage(items));*/

		}
	}
	roomLock.unlock();
}

void Room::SetWinningPlayer(int player,int killer, int wincount)
{
	if(mode == FIGHT_CLUB_MODE)return;
	MySQL MySql;
	int results[8], maxrounds[8], EndGame = 0;
	int rounds = 1, eleType = 0, eleBase = 0, eleMul = 0;
	for(int i = 0; i < 8; i++)
		maxrounds[i] = rounds;
	if(killer >= 0 && killer < 8)
		kills[killer]+=wincount;
	if(kills[killer] >= 3)
		EndGame = -1;
	for(int i = 0; i < 8; i++)
		if(users[i]){
			MyCharInfo *Info = users[i]->GetInfo();
			int uteam = Info->usr_team;
			if(EndGame == -1){
				if(Info->usr_slot == killer)results[i] = 1;
				else results[i] = 2;
				if(results[i] == 1)
					MySql.AddWin(Info->usr_id);
				else if(results[i] == 2)
					MySql.AddLose(Info->usr_id);
			}else if(Info->usr_slot == player)results[i] = 0;
			else results[i] = -1;
			Info->usr_ready = 0;
			Info->usr_life = 0;
			started = false;
		}else results[i] = -1;
	//Send(&FightCompleteMessage(results,0,0,0,0,0,0,maxrounds,EndGame));

	int Exp = 100000;
	int ExpGain[8];
	if (EndGame == -1) {
		eleType = (rng100() % 4) + 1;
		eleBase = (rng100() % 5) + 1;
		eleMul = (rng100() % 10) + 1;
		int nerf = rng100();
		if (nerf % 5 && eleBase > 1) {
			eleBase /= 2;
		}
		if (mode == MISSION_MODE && mission % 10 == 0)
		{
			if (mission % 301 < 100)
				Exp *= (rng100() % 3) + 2;
			else if (mission % 301 < 200)
				Exp *= (rng100() % 7) + 3;
			else {
				Exp *= (rng100() % 10) + 3;
				eleMul *= (rng100() % 10) + 3;
			}
			
			eleMul *= (rng100() % 4) + 3;

			Exp *= pow(1.1, (mission-1) % 10);
		}
	}

	if (p > 3 && p < 8)
	{
		Exp *= 2;
		eleMul *= 2;
	}
	else if (p == 8) {
		Exp *= 3;
		eleMul *= 3;
	}

	if (clock() - time < 30000) {
		eleMul = 0;
		Exp = 0;
	}
	else if (clock() - time < 60000) {
		eleMul /= 4;
		Exp /= 20;
	}
	else if (clock() - time < 120000) {
		eleMul /= 2;
		Exp /= 10;
	}

	if (eleBase > 0 && ChannelType == 1)
	{
		eleBase = 1;
		eleMul = eleMul / 2 + 1;
		Exp /= 10;
	}
	if (eleBase > 0 && ChannelType == 2)
	{
		eleBase = 3;
		eleMul = eleMul / 2 + 1;
		Exp /= 6;
	}

	int levels[16];
	for (int i = 0; i < 16; i++)
		levels[i] = -1;
	roomLock.lock();
	for(int i = 0; i < maxp; i++){
		if(users[i]){
			MyCharInfo *info = users[i]->GetInfo();
			if(EndGame == -1)
			{
				if(info)
				{
					if(eleType > 0 && eleType < 5){
						MySql.GetExp(info->usr_id,ExpGain[i],ElementTypes[eleType],eleBase*eleMul);
					}else MySql.GetExp(info->usr_id,ExpGain[i]);
					MySql.UpdateUserInfo(*info);

					Level lvl;
					int l = lvl.getLevel(info->Points);
					if (l > info->Level) {
						levels[i] = l;
					}
				}
			}
			users[i]->GetTcpSocket().Send(FightCompleteMessage(results,0,0,0,info->Points,info->Code,0,maxrounds,EndGame,ExpGain,eleType,eleBase,eleMul, levels));
		}
	}
	roomLock.unlock();
}

int  Room::GetTeamPlayersCount(int team)
{
	int result = 0;
	for(int i = 0; i < maxp; i++)
		if(users[i])
			if(users[i]->GetInfo()->usr_team == team)result++;
	return result;
}

int  Room::GetTeamReadyPlayersCount(int team)
{
	int result = 0;
	for(int i = 0; i < maxp; i++)
		if(users[i])
			if(users[i]->GetInfo()->usr_team == team && users[i]->GetInfo()->usr_ready == 1)result++;
	return result;
}

void Room::SetMapType(int type)
{
	mapType = type;
	if(mode == SYMBOL_MODE){
		if(type == 1){
			Symbol[0] = 10;
			Symbol[1] = 10;
			Symbol[2] = 20;
			Symbol[3] = 20;
		}else if(type == 2){
			Symbol[0] = 0;
			Symbol[1] = 0;
			Symbol[2] = 0;
			Symbol[3] = 0;
		}else if(type == 3){
			Symbol[0] = 0;
			Symbol[1] = 0;
			Symbol[2] = 20;
			Symbol[3] = 10;
		}
	}
}

bool Room::SetSymbolTeam(int symbol, int team)
{
	if(symbol >= 0 && symbol < 4){
		Symbol[symbol] = team;
		for(int i = 0; i < 4; i++)
			if(Symbol[i] != team)return false;
		return true;
	}
	return false;
}

void Room::GetSlots(int slots[8])
{
	for(int i = 0; i < 8; i++)
		if(users[i])
			slots[i] = i;
		else slots[i] = -1;
}

char* Room::GetBBX()
{
	return BBX;
}

int Room::GetNewMission()
{
	return ++mission;
}

void Room::GetOpenShops(User* user)
{
	roomLock.lock();
	__try {
	for(int i = 0; i < maxp; i++){
		if(users[i])
		{
			MyCharInfo *info = users[i]->GetInfo();
			if(info->usershop_open)
				user->GetTcpSocket().Send(OpenUserShopResponseMessage(info->usr_name,info->Shop_Title));
		}
	}
	}__except(true){
		cout << "Open Shop Crash" << endl;
	}
	roomLock.unlock();
}

bool Room::AddMolePoints(int team, int points)
{
	if(team == 10){
		Team1 += points;
		if(Team1 >= 100){
			Team1 = Team2 = 0;
			return true;
		}
	}else if(team == 20){
		Team2 += points;
		if(Team2 >= 100){
			Team1 = Team2 = 0;
			return true;
		}
	}
	return false;
}

int Room::AddGoal(int goal)
{
	if(goal == 0){
		Team2++;
		if(Team2 >= 3)return 20;
	}else if(goal == 1){
		Team1++;
		if(Team1 >= 3)return 10;
	}
	return 0;
}

void Room::EnterUserTurn(User* user)
{
	/*MyCharInfo *info = users[i]->GetInfo();
	if(max <= info->usr_turn && user->GetInfo()->usr_id != info->usr_id && info->usr_ready){
	max = info->usr_turn;
	user->GetInfo()->usr_turn = max+1;
	}*/
	roomLock.lock();
	for(int i = 0; i < maxp; i++){
		bool found = false;
		for(int j = 0; j < maxp; j++)
		{
			if(users[j])
			{
				MyCharInfo *info = users[j]->GetInfo();
				if(i == info->usr_turn && user->GetInfo()->usr_id != info->usr_id && info->usr_ready){
					found = true;
					break;
				}
			}
		}
		if(!found)
		{
			user->GetInfo()->usr_turn = i;
			break;
		}
	}
	roomLock.unlock();
}

void Room::LeaveUserTurn(User* user)
{
	roomLock.lock();
	__try {
	int turn = user->GetInfo()->usr_turn;
	for(int i = 0; i < maxp; i++){
		if(users[i])
		{
			MyCharInfo *info = users[i]->GetInfo();
			if(turn < info->usr_turn && info->usr_turn > 0)
				if(info->usr_ready)info->usr_turn--;
		}
	}
	user->GetInfo()->usr_turn = -1;
	}__except(true){
		cout << "Leave User Crash" << endl;
		roomLock.unlock();
	}
	/*int turn = user->GetInfo()->usr_turn;
	int max = 0;
	for(int i = 0; i < maxp; i++){
	if(users[i])
	{
	MyCharInfo *info = users[i]->GetInfo();
	if(max <= info->usr_turn)
	max = info->usr_turn;
	}
	}
	user->GetInfo()->usr_turn = max;
	for(int i = 0; i < maxp; i++){
	if(users[i])
	{
	MyCharInfo *info = users[i]->GetInfo();
	if(turn < info->usr_turn && info->usr_turn > 0 && user->GetInfo()->usr_id != info->usr_id)
	if(info->usr_ready)info->usr_turn--;
	}
	}*/
	roomLock.unlock();
}

void Room::GetTurns(int *slots)
{
	roomLock.lock();
	__try {
	int count = 0;
	for(int i = 0; i < maxp; i++){
		for(int j = 0; j < maxp; j++)
		{
			if(users[j])
			{
				MyCharInfo *info = users[j]->GetInfo();
				if(info->usr_ready && info->usr_turn == i){
					slots[count++] = info->usr_slot;
					break;
				}
			}
		}
	}
	}__except(true){
		cout << "Get turns crash" << endl;
	}
	roomLock.unlock();
}

void Room::NpcKilled(int npcNum)
{
	deadNpc.push_back(npcNum);
}

bool Room::IsNpcKilled(int npcNum)
{
	for(int i = 0; i < deadNpc.size(); i++)
	{
		if(deadNpc.at(i) == npcNum)
				return true;
	}
	return false;
}

void Room::InitCrystals()
{


}