#include <iostream>
#include "userdata.h"
#include <cstring>
#include <cstdlib>
using namespace std;
//����user��Ϣ
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
//�����û������Ƿ���ȷ
bool UserData::CheckUserPass()
{
	string pass;
	int wrong = 0;
	while (1)
	{
		cout << "���������룺";
		cin >> pass;
		if (pass == password)
			return true;
		else
		{
			cerr << "��������������������롣" << endl;
			wrong++;
			if (wrong > 2)
			{
				cout << "User����������󳬹�3�Σ������˳�ϵͳ..." << endl;
				system("PAUSE");
				return false;
			}
			continue;
		}
	}
}