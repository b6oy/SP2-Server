#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <time.h>
#include <iostream>
#include <mysql.h>
#include "ServerEnum.h"
#include "ClientPackets.h"
#include "ServerPackets.h"
#include <wininet.h>

using namespace std;

class MySQL
{
private:
MYSQL *connection;
char buffer[1000];

public:
MySQL();
~MySQL();
int Login(const char* id, const char* ip, bool& VisitRewards);
bool Connect();
void Disconnect();
void AddUserToActiveList(char*);
void UpdateTime(char*);
void RemoveUserFromActiveList(char*);
void SetUserIP(char*,char*);
void GetUserIP(int,char*);
void GetUserInfo(char*,MyCharInfo&);
void UpdateUserInfo(MyCharInfo&);
void GetUserItems(int id,bool*,int*,int*,int*,int*,int*);
int GetnSlots(int);
int GetValidSlot(int,int);
int InsertNewItem(MyCharInfo*,int,int,int,int);
void GetShopItemCost(int,int,int,int&,int&);
int DeleteItem(int,int);
void InsertMsg(char *,char *, char *);
void ChangeEquips(int id,int mag,int wpn,int arm,int pet,int foot,int body,int hand1,int hand2,int face,int hair,int head);
void GetUserData(UserInfoResponse*);
void GetEquipData(int id, int &magictype,int &weapontype,int &armortype,int &pettype,int &magiclevel,int &weaponlevel,int &armorlevel,int &petlevel,int &magicgf,int &weapongf,int &armorgf,int &petgf,int &magicskill,int &weaponskill,int &armorskill,int &petskill,int &foot,int &body,int &hand1,int &hand2,int &face,int &hair,int &head);
void GetMoneyAmmount(int,int*,unsigned __int64*,char=0,int=0,unsigned __int64=0);
bool UpgradeCard(MyCharInfo *,CardUpgradeResponse*);
void GetScrolls(MyCharInfo *);
void UpdateScrolls(int id,int slot,int scroll);
void IncreaseMission(int id,int n);
void InsertItem(MyCharInfo *info, unsigned __int64 price, int type, int gf, int level, int skill);
void RemoveItems(MyCharInfo *info);
void AddToShop(MyCharInfo *info,OpenUserShopRequest*);
void AddItemToShop(MyCharInfo *info, int slot, unsigned __int64 price);
void GetFromShop(MyCharInfo *info, OpenUserShopRequest* OUSR);
void SearchShop(CardSearchResponse*,SearchType);
void GetExp(int usr_id, int usr_exp,const char *Elements=0, int Ammount=0);
void GetBonus(int usr_id, int usr_code, int usr_cash, const char *Elements, int Ammount);
void SetLevel(int usr_id, int level);
//void ItemTransfer(int sender, int reciever, int itm_slot);
bool ItemTransfer(MyCharInfo sender, MyCharInfo reciever, int itm_slot);
void ItemTransfer(int sender, int reciever, int itm_slot, int itm_type, int itm_gf, int itm_level, int itm_skill);
bool ItemCheck(int itm_id, int itm_type, int itm_level, int itm_skill);
bool ElementCheck(int usr_id, int element);
void CodeTransfer(int sender, int reciever, unsigned __int64 ammount);
void IssueTrade(TradeStruct *Player1, TradeStruct *Player2, int usr1_id, int usr2_id);
void IssueUserShopBuy(MyCharInfo *seller, MyCharInfo *buyer, OpenUserShopRequest *OUSR);
int GetCardShopInfo(int room, SearchShopBuyRequest *SSBR, unsigned __int64 &price);
void IssueUserShopBuy(MyCharInfo *seller, MyCharInfo *buyer, SearchShopBuyRequest *SSBR);
void SaveMemo(char *sender,char *username, char *msg, bool sent);
bool CheckId(char *name);
int GetStoredMessages(RcvMemoResponse *RMR, char *receiver);
void AddFriend(int id, char *name);
void DeleteFriend(int id, char *name);
int GetFriendList(int id, FRIEND *Friend);
bool IsUserActive(char *name);
void AddDeath(int id);
void AddKill(int id);
void AddWin(int id);
void AddLose(int id);
int BuyElements(MyCharInfo *info,int element, int amount);
int ChargeForce(int id, int itemslot, int itemtype, int itemgf, int gfslot, int gftype);
void SetGender(int id, int gender);
};

struct LobbyUser
{
    string name;
    bool gender;
    int level, mission;
    LobbyUser *ptr;
};

class LobbyList
{
private:
    int count;
    LobbyUser *root;

public:
    LobbyList();
    void Insert(LobbyUser);
    void Delete(string);
    int GetList(unsigned char*);
};

#endif
