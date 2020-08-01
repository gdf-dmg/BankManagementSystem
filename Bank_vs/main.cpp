#include <iostream>
#include "userdata.h"
#include "bankdata.h"
#include <cstdlib>
#include <Windows.h>
#define OS_TYPE_WINDOWS_CC
#include "ColorfulConsole.h"

#pragma comment(lib, "winmm.lib")
using namespace std;





int main()
{
	SetConsoleTitleA("GDF银行储蓄管理系统");
	system("mode con cols=60 lines=35");
	BankData bank;
	system("color 03f");
	mciSendString("open BGM.mp3", 0, 0, 0);
	mciSendString("play BGM.mp3", 0, 0, 0);
	//wcout << ConsoleColor::Red << endl;
	while (true)
	{
		system("cls");
		int main_choice = bank.HomePage();
		
		if (main_choice == 1)
		{
			char choice1;
			char flag1 = 'c';
			while (true)
			{
				system("cls");
				bank.MenuShow1();
				cout << "请输入操作指令:";
				cin >> choice1;
				switch (choice1)
				{
				case '0':flag1 = 'b'; break;
				case '1':bank.AddMoney(); bank.SaveUserData(); break;
				case '2':bank.DelMoney(); bank.SaveUserData(); break;
				case '3':bank.ShowInfo(); break;
				case '4':bank.TransferMoney(); bank.SaveUserData(); break;
				case '5':bank.LossReport(); bank.SaveUserData(); break;
				case 'i':bank.about(); break;
				default:
					cerr << "输入错误，请重新输入." << endl;
					system("pause");
					continue;
				}
				if (flag1 == 'b')
				{
					break;
				}
				if(flag1 == 'c')
				{
					continue;
				}
	
				
			}
		}
		if (main_choice == 2)
		{
			string name;
			char choice2;
			int n, flag2, flag3 =-1;
			system("cls");
			cout << "            **********业务员身份验证**********" << "\n";
			cout << "              请输入业务员用户名与密码以验证" << "\n";
			cout << "                   请输入业务员用户名：";
			cin >> name;
			n = bank.SearchAdmin(name, bank.OpenAdmin());
			while (true)
			{
				if (n >= 0)
				{
					if (bank.CheckAdminPass(n))
					{
						cerr << "Welcome！" << endl;
						system("pause");
						flag2 = 1;
						break;
					}
				}
				else
				{
					cerr << "没有找到此管理员！" << endl;
					flag2 = 0;
					system("pause");
					break;
				}
			}
			if (flag2 == 1)
			{
				while (true)
				{
					system("cls");
					bank.MenuShow2();
					cout << "请输入操作指令:";
					cin >> choice2;
					switch (choice2)
					{
					case '0':flag3 = 1; break;
					case '1':bank.AddNumber(bank.UserNum); break;
					case '2':bank.DelNumber(); bank.SaveUserData(); break;
					case '3':bank.SolutionLinked(); bank.SaveUserData(); break;
					case '4':bank.ChangePass(); bank.SaveUserData(); break;
					default:
						cerr << "输入错误，请重新输入." << endl;
						system("pause");
						continue;
					}
					if (flag3 == 1)
					{
						break;
					}
					else
					{
						continue;
					}

				}
			}

		}
	}
	system("pause");
	return 0;
}