#include "MySQL.h"
#include "ini.h"

extern CIni config;

MySQL::MySQL()
{
	/*
	config.SetSection("DB");
	char * ip = config.ReadString("ip", "127.0.0.1");
	uint32 port = config.ReadInteger("port", 3306);
	char * user = config.ReadString("user", "root");
	char * pw = config.ReadString("pw", "");
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

int MySQL::Login(const char* id, const char* ip, bool& VisitRewards)
{
    char buffer[200];
    sprintf(buffer,"SELECT usr_id, DATEDIFF(CURRENT_TIMESTAMP, usr_bonus) FROM users WHERE usr_name = \'%s\' AND usr_ip = \'%s\'",id,ip);
    mysql_query(connection,buffer);
    MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
    MYSQL_ROW result = mysql_fetch_row(res);
    if(!result)return 0;
    int x = atoi(result[0]);
	int v = atoi(result[1]);
	if (v > 0)
		VisitRewards = true;
	else 
		VisitRewards = false;
    mysql_free_result(res);
    return x;
}

void MySQL::AddUserToActiveList(char *username)
{
	//char buffer[200];
	_snprintf(buffer,999,"INSERT INTO active_list VALUES (\'%s\',CURRENT_TIMESTAMP,2)",username);
	mysql_query(connection,buffer);
}

void MySQL::UpdateTime(char *username)
{
	//char buffer[200];
	_snprintf(buffer,999,"UPDATE active_list SET time = CURRENT_TIMESTAMP WHERE usr_name = \'%s\'",username);
	mysql_query(connection,buffer);
}

void MySQL::RemoveUserFromActiveList(char *username)
{
	//char buffer[200];
	_snprintf(buffer,999,"DELETE FROM active_list WHERE usr_name = \'%s\'",username);
	mysql_query(connection,buffer);
}

void MySQL::SetUserIP(char *name,char* ip)
{
	//char buffer[200];
	_snprintf(buffer,999,"UPDATE users SET usr_ip = \'%s\' WHERE usr_name = \'%s\'",ip,name);
	mysql_query(connection,buffer);
}

void MySQL::GetUserIP(int id,char *ip)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT usr_ip FROM users WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return;
	}
	strcpy(ip,result[0]);
	mysql_free_result(res);
}

void MySQL::GetUserInfo(char *name, MyCharInfo &info)
{
	//char buffer[300];
	_snprintf(buffer,999,"SELECT usr_id, usr_gender, usr_char, usr_points, usr_code, usr_level, usr_mission, usr_nslots, usr_water, usr_fire, usr_earth, usr_wind, usr_coins, usr_ip, usr_hwid FROM users WHERE usr_name = \'%s\'",name);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return;
	}
	info.usr_id = atoi(result[0]);
	info.gender = atoi(result[1]);
	info.DefaultCharacter = atoi(result[2]);
	info.Points = _atoi64(result[3]);
	info.Code = _atoi64(result[4]);
	info.Level = atoi(result[5]);
	info.Mission = atoi(result[6]);
	info.nSlots = atoi(result[7]);
	info.UserType = 30;
	info.Water = atoi(result[8]);
	info.Fire = atoi(result[9]);
	info.Earth = atoi(result[10]);
	info.Wind = atoi(result[11]);
	info.Coins = atoi(result[12]);
	strcpy(info.usr_name, name);
	strcpy(info.ip, result[13]);
	strcpy(info.hwid, result[14]);
	mysql_free_result(res);
}

void MySQL::UpdateUserInfo(MyCharInfo &info)
{
	//char buffer[300];
	_snprintf(buffer,999,"SELECT usr_id, usr_gender, usr_char, usr_points, usr_code, usr_level, usr_mission, usr_nslots, usr_water, usr_fire, usr_earth, usr_wind, usr_cash FROM users WHERE usr_id = %d",info.usr_id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	info.usr_id = atoi(result[0]);
	info.gender = atoi(result[1]);
	info.DefaultCharacter = atoi(result[2]);
	info.Points = _atoi64(result[3]);
	info.Code = _atoi64(result[4]);
	info.Level = atoi(result[5]);
	info.Mission = atoi(result[6]);
	info.nSlots = atoi(result[7]);
	info.UserType = 30;
	info.Water = atoi(result[8]);
	info.Fire = atoi(result[9]);
	info.Earth = atoi(result[10]);
	info.Wind = atoi(result[11]);
	info.Coins = atoi(result[12]);
	mysql_free_result(res);
}

void MySQL::GetUserItems(int id,bool *bMyCard,int *IDMyCard,int *TypeMyCard,int *GFMyCard,int *LevelMyCard,int *SkillMyCard)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT itm_id, itm_slot, itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM items WHERE itm_usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result;
	for(int i = 0; i < 96; i++)bMyCard[i] = false;
	while(result = mysql_fetch_row(res))
	{
		int slot = atoi(result[1]);
		bMyCard[slot] = true;
		if(IDMyCard)IDMyCard[slot] = atoi(result[0]);
		TypeMyCard[slot] = atoi(result[2]);
		GFMyCard[slot] = atoi(result[3]);
		LevelMyCard[slot] = atoi(result[4]);
		SkillMyCard[slot] = atoi(result[5]);
	}
	if(IDMyCard){
		for (int i = 0; i < 96; i++) {
			if (!bMyCard[i])IDMyCard[i] = TypeMyCard[i] = GFMyCard[i] = LevelMyCard[i] = SkillMyCard[i] = 0;
			if (GFMyCard[i] < 0)
				GFMyCard[i] = 0;
		}
	}else {
		for(int i = 0; i < 96; i++)
			if(!bMyCard[i])TypeMyCard[i] = GFMyCard[i] = LevelMyCard[i] = SkillMyCard[i] = 0;
	}
	mysql_free_result(res);
}

int MySQL::GetnSlots(int id)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT usr_nslots FROM users WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 96;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)return 96;
	int slots = atoi(result[0]);
	mysql_free_result(res);
	return slots;
}

int MySQL::GetValidSlot(int id,int maxslots)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT itm_slot FROM items WHERE itm_usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return -1;
	MYSQL_ROW result;
	for(int i = 0; i < maxslots; i++)
		buffer[i] = i;
	while(result = mysql_fetch_row(res))
	{
		int n = atoi(result[0]);
		buffer[n] = -1;
	}
	mysql_free_result(res);
	for(int i = 0; i < maxslots; i++)
		if(buffer[i] != -1)return buffer[i];
	return -1;
}
int MySQL::InsertNewItem(MyCharInfo *Info,int item,int gf,int level,int skill)
{
	int validslot = GetValidSlot(Info->usr_id,Info->nSlots);
	if(validslot == -1)return validslot;
	//char buffer[200];
	if(item < 2000 && level > 8 && Info->usr_id > 10)
		level = 0;
	_snprintf(buffer,999,"INSERT INTO items VALUES (0,%d,%d,%d,DATE_ADD(NOW(), INTERVAL %d DAY),%d,%d)",validslot,Info->usr_id,item,gf,level,skill);
	mysql_query(connection,buffer);
	return validslot;
}

int MySQL::DeleteItem(int id,int slotn)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT itm_type FROM items WHERE itm_usr_id = %d AND itm_slot = %d",id,slotn);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return 0;
	}
	int itm_type = atoi(result[0]);
	mysql_free_result(res);
	_snprintf(buffer,999,"DELETE FROM items WHERE itm_usr_id = %d AND itm_slot = %d",id,slotn);
	mysql_query(connection,buffer);
	return itm_type;
}

void MySQL::GetShopItemCost(int item, int gf,int quantity,int &code,int &cash)
{
	//char buffer[250];
	_snprintf(buffer,999,"SELECT itm_gf, itm_code_cost, itm_cash_cost, itm_coins_cost FROM shop WHERE itm_type = %d AND itm_quantity = %d",item,quantity);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result;
	while(result = mysql_fetch_row(res))
	{
		int x = atoi(result[0]);
		if(gf == x || (!gf && !x))
		{
			cash = atoi(result[2]);
			break;
		}
		else if(!gf && x)
		{
			code = atoi(result[1]);
			break;
		}
	}
	mysql_free_result(res);

}

void MySQL::InsertMsg(char *sender,char *reciever,char *msg)
{
	//char buffer[200];
	_snprintf(buffer,999,"INSERT INTO chats VALUES (0,1,\'%s\',\'%s\',\'%s\')",sender,reciever,msg);
	mysql_query(connection,buffer);
}

void MySQL::ChangeEquips(int id,int mag,int wpn,int arm,int pet,int foot,int body,int hand1,int hand2,int face,int hair,int head)
{
	_snprintf(buffer,999,"UPDATE equipments SET eqp_mag = %d, eqp_wpn = %d, eqp_arm = %d, eqp_pet = %d, eqp_foot = %d, eqp_body = %d, eqp_hand1 = %d, eqp_hand2 = %d, eqp_face = %d, eqp_hair = %d, eqp_head = %d WHERE usr_id = %d",mag,wpn,arm,pet,foot,body,hand1,hand2,face,hair,head,id);
	mysql_query(connection,buffer);
}

void MySQL::GetUserData(UserInfoResponse* UIR)
{
	//char buffer[500];
	_snprintf(buffer,999,"SELECT usr_id, usr_gender, usr_char, usr_points, usr_code, usr_coins, usr_level, usr_mission, usr_wins, usr_losses, usr_ko, usr_down FROM users WHERE usr_name = \'%s\'",UIR->username);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return;
	}
	int uid = atoi(result[0]);
	UIR->gender = atoi(result[1]);
	UIR->defaultcharacter = atoi(result[2]);
	UIR->Points = _atoi64(result[3]);
	UIR->Codes = _atoi64(result[4]);
	UIR->Coins = atoi(result[5]);
	UIR->level = atoi(result[6]);
	UIR->mission = atoi(result[7]);
	UIR->wins = atoi(result[8]);
	UIR->losses = atoi(result[9]);
	UIR->KO = atoi(result[10]);
	UIR->Down = atoi(result[11]);

	mysql_free_result(res);

	_snprintf(buffer,999,"SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM equipments INNER JOIN items WHERE itm_usr_id = %d AND usr_id = %d AND (itm_slot = eqp_mag OR itm_slot = eqp_wpn OR itm_slot = eqp_arm OR itm_slot = eqp_pet OR itm_slot = eqp_foot OR itm_slot = eqp_body OR itm_slot = eqp_hand1 OR itm_slot = eqp_hand2 OR itm_slot = eqp_face OR itm_slot = eqp_hair OR itm_slot = eqp_head)",uid,uid);
	mysql_query(connection,buffer);
	res = mysql_use_result(connection);
	if(!res)
		return;
	ItemId Item_id;
	while(result = mysql_fetch_row(res))
	{
		int itm_type = atoi(result[0]), itm_gf = atoi(result[1]), itm_level = atoi(result[2]), itm_skill = atoi(result[3]);
		int id1 = Item_id.Identify(itm_type);
		if(id1 == black || id1 == gold || id1 == pet || id1 == 11)
		{
			switch (Item_id.IdentifyItem(itm_type))
			{
			case ct_mag:
				UIR->magic = itm_type;
				UIR->magicgf = itm_gf;
				UIR->magiclevel = itm_level;
				UIR->magicskill = itm_skill;
				break;
			case ct_wpn:
				UIR->weapon = itm_type;
				UIR->weapongf = itm_gf;
				UIR->weaponlevel = itm_level;
				UIR->weaponskill = itm_skill;
				break;
			case ct_arm:
				UIR->armour = itm_type;
				UIR->armourgf = itm_gf;
				UIR->armourlevel = itm_level;
				UIR->armourskill = itm_skill;
				break;
			case ct_pet:
				UIR->pet = itm_type;
				UIR->petgf = itm_gf;
				UIR->petlevel = itm_level;
				break;
			default:
				break;
			}
		}
		else if(id1 == avatar)
		{
			switch (Item_id.IdentifyItem(itm_type))
			{
			case ct_foot:
				UIR->foot = itm_type;
				break;
			case ct_body:
				UIR->body = itm_type;
				break;
			case ct_hand1:
				UIR->hand1 = itm_type;
				break;
			case ct_hand2:
				UIR->hand2 = itm_type;
				break;
			case ct_face:
				UIR->face = itm_type;
				break;
			case ct_hair:
				UIR->hair = itm_type;
				break;
			case ct_head:
				UIR->head = itm_type;
				break;
			default:
				break;
			}
		}
	}
	mysql_free_result(res);
}

void MySQL::GetEquipData(int id, int &magictype,int &weapontype,int &armortype,int &pettype,int &magiclevel,int &weaponlevel,int &armorlevel,int &petlevel,int &magicgf,int &weapongf,int &armorgf,int &petgf,int &magicskill,int &weaponskill,int &armorskill,int &petskill,int &foot,int &body,int &hand1,int &hand2,int &face,int &hair,int &head)
{
	//char buffer[500];
	_snprintf(buffer,999,"SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM equipments INNER JOIN items WHERE itm_usr_id = %d AND usr_id = %d AND (itm_slot = eqp_mag OR itm_slot = eqp_wpn OR itm_slot = eqp_arm OR itm_slot = eqp_pet OR itm_slot = eqp_foot OR itm_slot = eqp_body OR itm_slot = eqp_hand1 OR itm_slot = eqp_hand2 OR itm_slot = eqp_face OR itm_slot = eqp_hair OR itm_slot = eqp_head)",id,id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result;
	ItemId Item_id;
	while(result = mysql_fetch_row(res))
	{
		int itm_type = atoi(result[0]), itm_gf = atoi(result[1]), itm_level = atoi(result[2]), itm_skill = atoi(result[3]);
		int id1 = Item_id.Identify(itm_type);
		if(id1 == black || id1 == gold || id1 == pet || id1 == 11)
		{
			if (id1 == 11)
				itm_type = itm_type % 10000;
			switch (Item_id.IdentifyItem(itm_type))
			{
			case ct_mag:
				magictype = itm_type;
				magicgf = itm_gf;
				magiclevel = itm_level;
				magicskill = itm_skill;
				break;
			case ct_wpn:
				weapontype = itm_type;
				weapongf = itm_gf;
				weaponlevel = itm_level;
				weaponskill = itm_skill;
				break;
			case ct_arm:
				armortype = itm_type;
				armorgf = itm_gf;
				armorlevel = itm_level;
				armorskill = itm_skill;
				break;
			case ct_pet:
				pettype = itm_type;
				petgf = itm_gf;
				petlevel = itm_level;
				break;
			default:
				break;
			}
		}
		else if(id1 == avatar)
		{
			switch (Item_id.IdentifyItem(itm_type))
			{
			case ct_foot:
				foot = itm_type;
				break;
			case ct_body:
				body = itm_type;
				break;
			case ct_hand1:
				hand1 = itm_type;
				break;
			case ct_hand2:
				hand2 = itm_type;
				break;
			case ct_face:
				face = itm_type;
				break;
			case ct_hair:
				hair = itm_type;
				break;
			case ct_head:
				head = itm_type;
				break;
			default:
				break;
			}
		}
	}
	mysql_free_result(res);
}

void MySQL::GetMoneyAmmount(int id,int *cash,unsigned __int64 *code,char sign,int cashcost,unsigned __int64 codecost)
{
	//char buffer[300];
	if(sign)
	{
		if(cashcost)
			_snprintf(buffer,999,"UPDATE users SET usr_cash = (usr_cash%c%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",sign,cashcost,id);

		if(codecost)
			_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code%c%I64u), time=CURRENT_TIMESTAMP WHERE usr_id = %d",sign,codecost,id);

		if(cashcost || codecost)
			mysql_query(connection,buffer);
	}
	_snprintf(buffer,999,"SELECT usr_cash, usr_code FROM users WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return;
	}
	if(cash)*cash = atoi(result[0]);
	if(code)*code = _atoi64(result[1]);
	mysql_free_result(res);
}

bool MySQL::UpgradeCard(MyCharInfo *Info,CardUpgradeResponse *CUR)
{
	bool Upgraded = false, fail = false;
	//char buffer[300];
	//_snprintf(buffer,999,"SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM items WHERE itm_usr_id = %d AND itm_slot = %d",Info->usr_id,CUR->Slot);
	_snprintf(buffer, 999, "SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM equipments INNER JOIN items WHERE usr_id = %d AND itm_usr_id = %d AND itm_slot = %d AND !(itm_slot = eqp_mag OR itm_slot = eqp_wpn OR itm_slot = eqp_arm OR itm_slot = eqp_pet OR itm_slot = eqp_foot OR itm_slot = eqp_body OR itm_slot = eqp_hand1 OR itm_slot = eqp_hand2 OR itm_slot = eqp_face OR itm_slot = eqp_hair OR itm_slot = eqp_head)", Info->usr_id, Info->usr_id, CUR->Slot);
	
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return false;
	MYSQL_ROW result = mysql_fetch_row(res);
	ItemId Item;
	if(!result)
	{
		printf("No Data\n");
		return false;
	}
	CUR->Type = atoi(result[0]);
	CUR->GF = atoi(result[1]);
	CUR->Level = atoi(result[2]);
	int EleCost = 0;
	if(CUR->UpgradeType == 1)EleCost = Item.GetUpgradeCost(CUR->Type,CUR->Level);
	else if(CUR->UpgradeType == 2)EleCost = Item.GetSkillCost(CUR->Type,CUR->Level);
	else if(CUR->UpgradeType == 5){
		_snprintf(buffer,999,"UPDATE items SET itm_level = (itm_level-1) WHERE itm_type = 2015 AND itm_usr_id = %d",Info->usr_id);
	}else if(CUR->UpgradeType == 6){
		_snprintf(buffer,999,"UPDATE items SET itm_level = (itm_level-1) WHERE itm_type = 2016 AND itm_usr_id = %d",Info->usr_id);
	}
	else {
		return false;
	}

	int	ItemSpirite = (CUR->Type % 100) / 10;
	if (ItemSpirite == 1 && Info->Water < EleCost)
		return false;
	if (ItemSpirite == 2 && Info->Fire < EleCost)
		return false;
	if (ItemSpirite == 3 && Info->Earth < EleCost)
		return false;
	if (ItemSpirite == 4 && Info->Wind < EleCost)
		return false;
	int CodeCost = EleCost*400;
	Info->Code -= CodeCost;

	if (CUR->UpgradeType == 1) {
		if (Item.UpgradeItem(CUR->GF, CUR->Level)) {
			CUR->Level += 1;
			Upgraded = true;
		}
		else
		{
			fail = true;
			CUR->UpgradeType = 2;
			CUR->Upgraded = 5;
		}
	}

	if(EleCost)
	{
		CUR->Returned = EleCost / ((rng() * 5) + 2);
		if (CUR->Upgraded == 5 && CUR->UpgradeType == 2 && fail)
			EleCost -= CUR->Returned;
		if(ItemSpirite == 1)
		{
			Info->Water -= EleCost;
			_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%d),usr_water = (usr_water-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",CodeCost,EleCost,Info->usr_id);
		}
		else if(ItemSpirite == 2)
		{
			Info->Fire -= EleCost;
			_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%d),usr_fire = (usr_fire-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",CodeCost,EleCost,Info->usr_id);
		}
		else if(ItemSpirite == 3)
		{
			Info->Earth -= EleCost;
			_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%d),usr_earth = (usr_earth-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",CodeCost,EleCost,Info->usr_id);
		}
		else if(ItemSpirite == 4)
		{
			Info->Wind -= EleCost;
			_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%d),usr_wind = (usr_wind-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",CodeCost,EleCost,Info->usr_id);
		}
	}
	else {
		return false;
	}

	CUR->WaterElements = Info->Water;
	CUR->FireElements = Info->Fire;
	CUR->EarthElements = Info->Earth;
	CUR->WindElements = Info->Wind;


	if(Info->GM_new_skill){
		CUR->Skill = Info->GM_new_skill;
		Info->GM_new_skill = 0;
	}else CUR->Skill = Item.GenerateSkill(CUR->Level,CUR->Type);
	if(CUR->UpgradeType == 5)
	{
		int skill = atoi(result[3]);
		int skill1 = (skill / 1000) % 1000;
		CUR->Skill = skill - (skill1*1000) + (((CUR->Skill / 1000) % 1000)*1000);
	}else if(CUR->UpgradeType == 6)
	{
		int skill1 = (atoi(result[3]) / 1000) % 1000;
		CUR->Skill = CUR->Skill - (((CUR->Skill / 1000) % 1000)*1000) + (skill1*1000);
	}
	CUR->Code = Info->Code;
	mysql_free_result(res);
	mysql_query(connection,buffer);
	if(CUR->Type < 2000){
		if(CUR->Level < 9 || Info->usr_id < 10){
			_snprintf(buffer,999,"UPDATE items SET itm_level = %d, itm_skill = %d WHERE itm_usr_id = %d AND itm_slot = %d",CUR->Level,CUR->Skill,Info->usr_id,CUR->Slot);
			mysql_query(connection,buffer);
		}
	}else {
			_snprintf(buffer,999,"UPDATE items SET itm_level = %d, itm_skill = %d WHERE itm_usr_id = %d AND itm_slot = %d",CUR->Level,CUR->Skill,Info->usr_id,CUR->Slot);
			mysql_query(connection,buffer);
	}

	if(CUR->UpgradeType == 5 || CUR->UpgradeType == 6)
	{
	_snprintf(buffer,999,"DELETE FROM items WHERE itm_usr_id = %d AND (itm_type = 2015 OR itm_type = 2016) AND itm_level = 0",Info->usr_id);
	mysql_query(connection,buffer);
	}
	return Upgraded;
}

void MySQL::GetScrolls(MyCharInfo *Info)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT usr_scroll1,usr_scroll2,usr_scroll3 FROM users WHERE usr_id = %d",Info->usr_id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result){
		printf("No Data\n");
		return;
	}
	for(int i = 0; i < 3; i++)
		Info->scrolls[i] = atoi(result[i]);
	mysql_free_result(res);
}

void MySQL::UpdateScrolls(int id,int slot,int scroll)
{
	//char buffer[200];
	_snprintf(buffer,999,"UPDATE users SET usr_scroll%d = %d WHERE usr_id = %d",slot+1,scroll,id);
	mysql_query(connection,buffer);
}

void MySQL::IncreaseMission(int id,int n)
{
	//char buffer[200];
	_snprintf(buffer,999,"UPDATE users SET usr_mission = usr_mission+%d WHERE usr_id = %d",n,id);
	mysql_query(connection,buffer);
}

void MySQL::InsertItem(MyCharInfo *info, unsigned __int64 price, int type, int gf, int level, int skill)
{
	ItemId Itemid;
	int shop_type = Itemid.IdentifyShopType(type);
	int room = info->usr_room;
	if(room < 0)room = 6000;
	//char buffer[300];
	_snprintf(buffer,999,"INSERT INTO cardshop VALUES (0,%d,%d,\'%s\',%d,%d,%I64u,%d,%d,%d,%d)",
		shop_type,room,info->usr_name,info->Level,info->gender,price,type,gf,level,skill);
	mysql_query(connection,buffer);
}

void MySQL::RemoveItems(MyCharInfo *info)
{
	//char buffer[200];
	_snprintf(buffer,999,"DELETE FROM cardshop WHERE card_room = %d AND usr_name = \'%s\'",info->usr_room, info->usr_name);
	mysql_query(connection,buffer);
}

void MySQL::AddToShop(MyCharInfo *info, OpenUserShopRequest* OUSR)
{
	//char buffer[300];
	if(OUSR)
	{
		for(int i = 0; i < 4; i++)
			if(OUSR->items[i] != -1 && OUSR->items[i] < 10000)
			{
				_snprintf(buffer,999,"SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM items WHERE itm_slot = %d AND itm_usr_id = %d", OUSR->items[i], info->usr_id);
				mysql_query(connection,buffer);
				MYSQL_RES *res = mysql_use_result(connection);
				if(!res)return;
				MYSQL_ROW result = mysql_fetch_row(res);
				if(result)
				{
					int type = atoi(result[0]);
					int gf = atoi(result[1]);
					int level = atoi(result[2]);
					int skill = atoi(result[3]);
					mysql_free_result(res);
					InsertItem(info,OUSR->price[i],type,gf,level,skill);
				}
			}
			else if (OUSR->items[i] > 10000) {
				int type = OUSR->items[i] / 10000;
				int ammount = OUSR->items[i] % 10000;
				if (type == 1 && ammount > info->Water)
					ammount = info->Water;
				if (type == 2 && ammount > info->Fire)
					ammount = info->Fire;
				if (type == 3 && ammount > info->Earth)
					ammount = info->Earth;
				if (type == 4 && ammount > info->Wind)
					ammount = info->Wind;
				InsertItem(info, OUSR->price[i], OUSR->items[i], -1, -1, -1);
			}
		_snprintf(buffer,999,"SELECT shop_id FROM cardshop WHERE card_room = %d AND usr_name = \'%s\'",info->usr_room, info->usr_name);
		mysql_query(connection,buffer);
		MYSQL_RES *res = mysql_use_result(connection);
		if(!res)return;
		MYSQL_ROW result = 0;
		int i = 0;
		while((result = mysql_fetch_row(res)) && i < 4)
			info->Shop_id[i++] = atoi(result[0]);
		mysql_free_result(res);
	}
}

void MySQL::AddItemToShop(MyCharInfo *info, int slot, unsigned __int64 price)
{
	if(slot < 10000)
	{
		_snprintf(buffer,999,"SELECT itm_type, DATEDIFF(itm_gf, NOW()), itm_level, itm_skill FROM items WHERE itm_slot = %d AND itm_usr_id = %d", slot, info->usr_id);
		mysql_query(connection,buffer);
		MYSQL_RES *res = mysql_use_result(connection);
		if(!res)return;
		MYSQL_ROW result = mysql_fetch_row(res);
		if(result)
		{
			int type = atoi(result[0]);
			int gf = atoi(result[1]);
			int level = atoi(result[2]);
			int skill = atoi(result[3]);
			mysql_free_result(res);
			InsertItem(info,price,type,gf,level,skill);
		}
	}else if(slot > 10000)InsertItem(info,price,slot,-1,-1,-1);
}

void MySQL::GetFromShop(MyCharInfo *info, OpenUserShopRequest* OUSR)
{
	//char buffer[400];
	if(OUSR)
	{
		for(int i = 0; i < 4; i++)
			if(OUSR->items[i] != -1 && info->Shop_id[i] != -1)
			{
				_snprintf(buffer,999,"SELECT card_price, card_type, card_gf, card_level, card_skill FROM cardshop WHERE shop_id = %d", info->Shop_id[i]);
				mysql_query(connection,buffer);
				MYSQL_RES *res = mysql_use_result(connection);
				if(!res)return;
				MYSQL_ROW result = mysql_fetch_row(res);
				if(result)
				{
					OUSR->price[i] = _atoi64(result[0]);
					OUSR->itemType[i] = atoi(result[1]);
					OUSR->itemGF[i] = atoi(result[2]);
					OUSR->itemLevel[i] = atoi(result[3]);
					OUSR->itemSkill[i] = atoi(result[4]);
					mysql_free_result(res);
				}
			}
	}
}

void MySQL::SearchShop(CardSearchResponse *CSR,SearchType type)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT * FROM cardshop WHERE shop_type = %d",type);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return;
	CSR->total = res->row_count;
	MYSQL_ROW result = 0;
	int i = 0;
	while((result = mysql_fetch_row(res)) != 0 && i < 5){
		CSR->rooms[i] = atoi(result[2]);
		strcpy(CSR->name[i],result[3]);
		CSR->levels[i] = atoi(result[4]);
		CSR->gender[i] = atoi(result[5]);
		CSR->price[i] = _atoi64(result[6]);
		CSR->card[i] = atoi(result[7]);
		CSR->gf[i] = atoi(result[8]);
		CSR->level[i] = atoi(result[9]);
		CSR->skill[i] = atoi(result[10]);
		i++;
	}
	while(i < 5){
		CSR->rooms[i] = -1;
		CSR->name[i][0] = 0;
		CSR->levels[i] = -1;
		CSR->gender[i] = 0;
		CSR->price[i] = -1;
		CSR->card[i] = -1;
		CSR->gf[i] = -1;
		CSR->level[i] = -1;
		CSR->skill[i] = -1;
		i++;
	}
	mysql_free_result(res);
}

void MySQL::GetExp(int usr_id, int usr_exp,const char *Elements, int Ammount)
{
	if (usr_exp > 1000000000)
		return;
	//char buffer[300];
	if(Elements)
		_snprintf(buffer,999,"UPDATE users SET usr_points = (usr_points+%d),usr_code = (usr_code+%d),usr_%s = (usr_%s+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",usr_exp,usr_exp,Elements,Elements,Ammount,usr_id);
	else _snprintf(buffer,999,"UPDATE users SET usr_points = (usr_points+%d),usr_code = (usr_code+%d), time=CURRENT_TIMESTAMP  WHERE usr_id = %d",usr_exp,usr_exp,usr_id);
	mysql_query(connection,buffer);
}


void MySQL::GetBonus(int usr_id, int usr_code, int usr_cash, const char *Elements, int Ammount)
{
	if (usr_code > 1000000000)
		return;
	//char buffer[300];
	if (Elements)
		_snprintf(buffer, 999, "UPDATE users SET usr_cash = (usr_cash+%d),usr_code = (usr_code+%d),usr_%s = (usr_%s+%d), usr_bonus=CURRENT_TIMESTAMP, time=CURRENT_TIMESTAMP WHERE usr_id = %d", usr_cash, usr_code, Elements, Elements, Ammount, usr_id);
	else _snprintf(buffer, 999, "UPDATE users SET usr_cash = (usr_cash+%d),usr_code = (usr_code+%d), time=CURRENT_TIMESTAMP  WHERE usr_id = %d", usr_cash, usr_code, usr_id);
	mysql_query(connection, buffer);
}

void MySQL::SetLevel(int usr_id, int level)
{
	_snprintf(buffer,999,"UPDATE users SET usr_level = %d, time=CURRENT_TIMESTAMP WHERE usr_id = %d",level,usr_id);
	mysql_query(connection,buffer);
}

bool MySQL::ItemTransfer(MyCharInfo sender, MyCharInfo reciever, int itm_slot)
{
	//char buffer[300];
	if(itm_slot > 10000)
	{
		int eleType = itm_slot/10000;
		int ammount = itm_slot%10000;
		if (eleType == 1 && sender.Water < ammount)
			return false;
		if (eleType == 2 && sender.Fire < ammount)
			return false;
		if (eleType == 3 && sender.Earth < ammount)
			return false;
		if (eleType == 4 && sender.Wind < ammount)
			return false;
		_snprintf(buffer,999,"UPDATE users SET usr_%s = (usr_%s-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ElementTypes[eleType],ElementTypes[eleType],ammount,sender.usr_id);
		mysql_query(connection,buffer);
		_snprintf(buffer,999,"UPDATE users SET usr_%s = (usr_%s+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ElementTypes[eleType],ElementTypes[eleType],ammount,reciever.usr_id);
		mysql_query(connection,buffer);
	}else if(itm_slot != -1){
		int validslot = GetValidSlot(reciever.usr_id,GetnSlots(reciever.usr_id));
		if(validslot == -1)return false;
		_snprintf(buffer,999,"UPDATE items SET itm_slot = %d, itm_usr_id = %d WHERE itm_slot = %d AND itm_usr_id = %d",
			validslot,reciever,itm_slot,sender);
		mysql_query(connection,buffer);
	}
	return true;
}


void MySQL::ItemTransfer(int sender, int reciever, int itm_slot, int itm_type, int itm_gf, int itm_level, int itm_skill)
{
	//char buffer[500];
	if(itm_slot > 10000)
	{
		int eleType = itm_slot/10000;
		int ammount = itm_slot%10000;
		_snprintf(buffer,999,"UPDATE users SET usr_%s = (usr_%s-%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ElementTypes[eleType],ElementTypes[eleType],ammount,sender);
		mysql_query(connection,buffer);
		_snprintf(buffer,999,"UPDATE users SET usr_%s = (usr_%s+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ElementTypes[eleType],ElementTypes[eleType],ammount,reciever);
		mysql_query(connection,buffer);
	}else if(itm_slot != -1){
		int validslot = GetValidSlot(reciever,GetnSlots(reciever));
		if(validslot == -1)return;
		_snprintf(buffer,999,"UPDATE items SET itm_slot = %d, itm_usr_id = %d WHERE itm_slot = %d AND itm_usr_id = %d AND itm_type = %d AND itm_level = %d AND itm_skill = %d",
			validslot,reciever,itm_slot,sender,itm_type,itm_level,itm_skill);
		mysql_query(connection,buffer);
	}
}

bool MySQL::ItemCheck(int usr_id, int itm_type, int itm_level, int itm_skill)
{
	_snprintf(buffer,999,"SELECT * FROM items WHERE itm_usr_id = %d AND itm_id > 0 AND itm_type = %d AND itm_level = %d AND itm_skill = %d",usr_id,itm_type,itm_level,itm_skill);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return false;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
		return false;
	mysql_free_result(res);
	return true;
}

bool MySQL::ElementCheck(int usr_id, int element)
{

	int eleType = element/10000;
	int ammount = element%10000;
	_snprintf(buffer,999,"SELECT usr_%s FROM users WHERE usr_id = %d",ElementTypes[eleType],usr_id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return false;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
		return false;
	int currentAmmount = atoi(result[0]);
	mysql_free_result(res);
	if(ammount > currentAmmount)
		return false;
	return true;
}

void MySQL::CodeTransfer(int sender, int reciever, unsigned __int64 ammount)
{
	if (ammount > 1000000000)
		return;
	//char buffer[200];
	_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%I64u), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ammount,sender);
	mysql_query(connection,buffer);
	_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code+%I64u), time=CURRENT_TIMESTAMP WHERE usr_id = %d",ammount,reciever);
	mysql_query(connection,buffer);
}

void MySQL::IssueTrade(TradeStruct *Player1, TradeStruct *Player2, int usr1_id, int usr2_id)
{
	if(Player1 && Player2)
	{
		for(int i = 0; i < 4; i++)
			ItemTransfer(usr1_id,usr2_id,Player1->itemID[i],Player1->itemType[i],Player1->itemGF[i],Player1->itemLevel[i],Player1->itemSkill[i]);

		for(int i = 0; i < 4; i++)
			ItemTransfer(usr2_id,usr1_id,Player2->itemID[i],Player2->itemType[i],Player2->itemGF[i],Player2->itemLevel[i],Player2->itemSkill[i]);

		if(Player1->Code)
			CodeTransfer(usr1_id,usr2_id,Player1->Code);

		if(Player2->Code)
			CodeTransfer(usr2_id,usr1_id,Player2->Code);
	}
}

void MySQL::IssueUserShopBuy(MyCharInfo *seller, MyCharInfo *buyer, OpenUserShopRequest *OUSR)
{
	if(OUSR)
	{
		for(int i = 0; i < 4; i++)
			if(OUSR->price[i] != -1 && OUSR->price[i] > 0)
			{
				//ItemTransfer(seller->usr_id, buyer->usr_id, seller->Shop_Items[i]);
				if(ItemTransfer(*seller, *buyer, seller->Shop_Items[i]))
					CodeTransfer(buyer->usr_id, seller->usr_id, OUSR->price[i]);
				seller->Shop_Items[i] = -1;
				break;
			}
	}
}

int MySQL::GetCardShopInfo(int room, SearchShopBuyRequest *SSBR, unsigned __int64 &price)
{
	//char buffer[200];
	if(room == SSBR->room)
	{
		_snprintf(buffer,999,"SELECT shop_id, card_price FROM cardshop WHERE usr_name = \'%s\' AND card_type = %d",SSBR->username, SSBR->itm_type);
		mysql_query(connection,buffer);
		MYSQL_RES *res = mysql_use_result(connection);
		if(!res)return 0;
		MYSQL_ROW result = mysql_fetch_row(res);
		if(!result){
			printf("No Data\n");
			return 0;
		}
		price = _atoi64(result[1]);
		int id = atoi(result[0]);
		mysql_free_result(res);
		return id;
	}
	return 0;
}

void MySQL::IssueUserShopBuy(MyCharInfo *seller, MyCharInfo *buyer, SearchShopBuyRequest *SSBR)
{
	if(SSBR && seller && buyer)
	{
		unsigned __int64 price = 0;
		int Shop_id = GetCardShopInfo(seller->usr_room, SSBR, price);
		if(!Shop_id)return;
		int i = 0;
		while(seller->Shop_id[i] != Shop_id && i < 4)i++;
		if(i >= 4)return;
		if(price != -1 && price > 0)
		{
			if(ItemTransfer(*seller, *buyer, seller->Shop_Items[i]))
			CodeTransfer(buyer->usr_id, seller->usr_id, price);
			seller->Shop_Items[i] = -1;
		}
	}
}

void MySQL::SaveMemo(char *sender,char *username, char *msg, bool sent)
{
	//char buffer[500];
	_snprintf(buffer,999,"INSERT INTO messages VALUES (0,\'%s\',\'%s\',\'%s\',%d)",sender,username,msg,sent);
	mysql_query(connection,buffer);
}

bool MySQL::CheckId(char *name)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT usr_id FROM users WHERE usr_name = \'%s\'",name);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return false;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)return false;
	mysql_free_result(res);
	return true;
}

int MySQL::GetStoredMessages(RcvMemoResponse *RMR, char *receiver)
{
	//char buffer[300];
	_snprintf(buffer,999,"SELECT msg_id, msg_sender, msg_text FROM messages WHERE msg_receiver = \'%s\' AND msg_sent = 0",receiver);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
	MYSQL_ROW result = 0;
	int i = 0, msg_id = 0;
	bool copy = true;
	while(result = mysql_fetch_row(res))
	{
		if(copy){
			msg_id = atoi(result[0]);
			strcpy(RMR->username,result[1]);
			strcpy(RMR->msg,result[2]);
			copy = false;
		}
		i++;
	}
	mysql_free_result(res);
	if(i){
		_snprintf(buffer,999,"UPDATE messages SET msg_sent = 1 WHERE msg_id = %d",msg_id);
		mysql_query(connection,buffer);
	}
	return i;
}

void MySQL::AddFriend(int id, char *name)
{
	//char buffer[200];
	_snprintf(buffer,999,"INSERT INTO friends VALUES (0,%d,\'%s\')",id,name);
	mysql_query(connection,buffer);
}

void MySQL::DeleteFriend(int id, char *name)
{
	//char buffer[200];
	_snprintf(buffer,999,"DELETE FROM friends WHERE usr_id = %d AND frd_name = \'%s\'",id,name);
	mysql_query(connection,buffer);
}

int MySQL::GetFriendList(int id, FRIEND *Friend)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT frd_name FROM friends WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
	MYSQL_ROW result = 0;
	int i = 0;
	while(result = mysql_fetch_row(res))
	{
		strcpy(Friend[i].name,result[0]);
		Friend[i].room = -1;
		i++;
	}
	mysql_free_result(res);
	return i;
}

bool MySQL::IsUserActive(char *name)
{
	//char buffer[200];
	_snprintf(buffer,999,"SELECT time FROM active_list WHERE usr_name = \'%s\'",name);
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return false;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
		return false;
	mysql_free_result(res);
	return true;
}

void MySQL::AddDeath(int id)
{
	_snprintf(buffer,999,"UPDATE users SET usr_down = usr_down+1 WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
}

void MySQL::AddKill(int id)
{
	_snprintf(buffer,999,"UPDATE users SET usr_ko = usr_ko+1 WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
}

void MySQL::AddWin(int id)
{
	_snprintf(buffer,999,"UPDATE users SET usr_wins = usr_wins+1 WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
}

void MySQL::AddLose(int id)
{
	_snprintf(buffer,999,"UPDATE users SET usr_losses = usr_losses+1 WHERE usr_id = %d",id);
	mysql_query(connection,buffer);
}

int MySQL::BuyElements(MyCharInfo *info,int element, int amount)
{
	int id = info->usr_id;
	unsigned __int64 codecost = 30000 * amount;
	if(codecost > info->Code)
		return 0;
	if(element == 6000)
		_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%I64u), usr_water = (usr_water+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",codecost,amount,id);
	else if(element == 6001)
		_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%I64u), usr_fire = (usr_fire+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",codecost,amount,id);
	else if(element == 6002)
		_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%I64u), usr_earth = (usr_earth+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",codecost,amount,id);
	else if(element == 6003)
		_snprintf(buffer,999,"UPDATE users SET usr_code = (usr_code-%I64u), usr_wind = (usr_wind+%d), time=CURRENT_TIMESTAMP WHERE usr_id = %d",codecost,amount,id);
	mysql_query(connection,buffer);

	_snprintf(buffer,999,"SELECT usr_code, usr_water, usr_fire, usr_earth, usr_wind FROM users WHERE usr_id = %d",id);
	//cout << buffer << endl;
	mysql_query(connection,buffer);
	MYSQL_RES *res = mysql_use_result(connection);
	if(!res)return 0;
	MYSQL_ROW result = mysql_fetch_row(res);
	if(!result)
	{
		printf("No Data\n");
		return 0;
	}
	info->Code = _atoi64(result[0]);
	info->Water = atoi(result[1]);
	info->Fire = atoi(result[2]);
	info->Earth = atoi(result[3]);
	info->Wind = atoi(result[4]);
	mysql_free_result(res);
	return 1;
}

int MySQL::ChargeForce(int id, int itemslot, int itemtype, int itemgf, int gfslot, int gftype)
{
	int gfdays = 30;
	if(gftype > 3009)
		gfdays = 365;
	_snprintf(buffer,999,"UPDATE items SET itm_gf = DATE_ADD(NOW(), INTERVAL %d DAY) WHERE itm_usr_id = %d AND itm_slot = %d AND itm_type = %d",itemgf+gfdays,id,itemslot,itemtype);
	mysql_query(connection,buffer);
	_snprintf(buffer,999,"DELETE FROM items WHERE itm_usr_id = %d AND itm_slot = %d AND itm_type = %d",id,gfslot,gftype);
	mysql_query(connection,buffer);
	return true;
}

void MySQL::SetGender(int id, int gender)
{
	_snprintf(buffer,999,"UPDATE users SET usr_gender = %d WHERE usr_id = %d",gender,id);
	mysql_query(connection,buffer);
}