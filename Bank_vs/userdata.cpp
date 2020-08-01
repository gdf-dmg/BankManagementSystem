#include <iostream>
#include "userdata.h"
#include <cstring>
#include <cstdlib>
using namespace std;
//建立user信息
void UserData::SetUser(long a, string n, string p, double b, string i, string h, int s)
{
	accNumber = a;
	accName = n;
	password = p;
	balance = b;
	identity = i;
	homeads = h;
	state = s;
}
//检验用户密码是否正确
bool UserData::CheckUserPass()
{
	string pass;
	int wrong = 0;
	while (1)
	{
		cout << "请输入密码：";
		cin >> pass;
		if (pass == password)
			return true;
		else
		{
			cerr << "密码输入错误，请重新输入。" << endl;
			wrong++;
			if (wrong > 2)
			{
				cout << "User密码输入错误超过3次，即将退出系统..." << endl;
				system("PAUSE");
				return false;
			}
			continue;
		}
	}
}