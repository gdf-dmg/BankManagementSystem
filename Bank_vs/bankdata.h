#pragma once
#ifndef BANKDATA_H_INCLUDED
#define BANKDATA_H_INCLUDED
#include <iostream>
#include "userdata.h"
using namespace std;
class BankData//银行数据类
{
public:
	BankData();
	~BankData();
	Admin admin[10];
	UserData *user = new UserData[2000];
	int UserNum;
	int HomePage();
	int OpenAdmin();
	int SearchAdmin(string, int);
	bool CheckAdminPass(int);
	void MenuShow1();
	void MenuShow2();
	bool CheckUser(long acc);

	void OpenUserData();
	void SaveUserData();
	void AddNumber(int);
	void DelNumber(void);
	void AddMoney(void);
	void DelMoney(void);
	void ShowInfo(void);
	void TransferMoney(void);
	void LossReport(void);
	void SolutionLinked(void);
	void ChangePass(void);
						  
	string int2str(int num);
	string gettime();
	void SaveUserLog(int, int);
	void about();
};
#endif
