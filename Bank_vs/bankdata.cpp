#include <iostream>
#include "bankdata.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>
#include <graphics.h>
#include <conio.h>
#include<time.h>

using namespace std;

BankData::BankData()//构造函数
{
	long number;
	string name, pass, id, h;
	double balance;
	int state;
	UserNum = 0;
	//开始读取User的信息
	fstream infile;
	infile.open("BankUser.dat", ios::app | ios::in);
	if (!infile)
	{
		cerr << "打开数据库(BankUser.dat)文件失败！";
		exit(1);
	}
	while (infile >> number >> name >> pass >> balance >> id >> h >> state)
	{
		user[UserNum].SetUser(number, name, pass, balance, id, h, state);
		UserNum++;
	}
	infile.close();
	//User信息读取完毕，总数存入UserNum
}

BankData::~BankData()//析构函数
{
	delete[]user;
}

string BankData::int2str(int num)//int 2 str
{
	if (num == 0)
		return "0";
	string str = "";
	int num_ = num>0 ? num : -1 * num;
	while (num_)
	{
		str = (char)(num_ % 10 + 48) + str;
		num_ /= 10;
	}
	if (num<0)
		str = "-" + str;
	return str;
}

string BankData::gettime()//获取系统时间
{
	time_t curtime = time(0);
	tm tim = *localtime(&curtime);
	int day, mon, year;
	int hour, min, sec;
	string time;
	hour = tim.tm_hour;//时
	min = tim.tm_min;//分
	sec = tim.tm_sec;//秒
	day = tim.tm_mday;//日
	mon = tim.tm_mon;//月
	year = tim.tm_year;//年
	time = int2str(year + 1900) + "-" + int2str(mon + 1) + "-" + int2str(day) + "_" + int2str(hour) + ":" + int2str(min) + ":" + int2str(sec);
	return time;
}

void BankData::about()//星空
{
	struct STAR
	{
		double x; 
		int y; 
		double step; 
		int color;
	};
	STAR star[200];
	srand((unsigned)time(NULL)); // 随机种子 
	initgraph(640, 480); // 打开图形窗口 
	for (int i = 0; i < 200; i++)
	{
		star[i].x = 0;
		star[i].y = rand() % 480;
		star[i].step = (rand() % 5000) / 1000.0 + 1;
		star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5); // 速度越快，颜色越亮 
		star[i].color = RGB(100, 200, 230);
		star[i].x = rand() % 640;
	}
	while (!_kbhit())
	{
		for (int i = 0; i < 200; i++)
		{
			putpixel((int)star[i].x, star[i].y, 0);// 计算新位置 
			star[i].x += star[i].step;
			if (star[i].x > 640)
			{
				star[i].x = 0;
				star[i].y = rand() % 480;
				star[i].step = (rand() % 5000) / 1000.0 + 1;
				star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5); // 速度越快，颜色越亮 
				star[i].color = RGB(100, 200, 230);  //合成颜色
			}
			putpixel((int)star[i].x, star[i].y, star[i].color);  //画点
		}
		Sleep(20);
	}
	closegraph(); // 关闭图形窗口
	cout << "欢迎使用银行储蓄系统1.0！" << endl;
	cout << "使用中有任何问题请联系GDF：13218886562" << endl;
	system("PAUSE");
}

void BankData::OpenUserData()
{
	long number;
	string name, pass, id, h;
	double balance;
	int state;
	UserNum = 0;
	//开始读取User的信息
	ifstream infile("BankUser.dat", ios::in);
	if (!infile)
	{
		cerr << "打开数据库(BankUser.dat)文件失败！";
		exit(1);
	}
	while (infile >> number >> name >> pass >> balance >> id >> h >> state)
	{
		user[UserNum].SetUser(number, name, pass, balance, id, h, state);
		UserNum++;
	}
	infile.close();
	//User信息读取完毕，总数存入UserNum
}
//查找用户名
bool BankData::CheckUser(long acc)
{
	for (int i = 0; i < UserNum;)
	{
		if (user[i].get_accNumber() == acc)
			return true;
		else
		{
			i++;
		}
	}
	cout << "没有找到此账户。" << endl;
	system("PAUSE");
	return false;
}

void BankData::SaveUserLog(int i, int acc)//记录用户日志
{
	string type, time, state;
	switch (i)
	{
	case 1:state = "开户"; break;
	case 2:state = "销户"; break;
	case 3:state = "存款"; break;
	case 4:state = "取款"; break;
	case 6:state = "转账"; break;
	case 7:state = "挂失"; break;
	case 8:state = "解挂"; break;
	case 9:state = "改密"; break;
	}
	time = gettime();
	type = int2str(acc + 10001);
	//strcpy(p,type.data());类型转换：string 2 char*
	char ch1[25] = "BankUser";
	char ch2[8] = ".log";
	char ch[8];
	strcpy(ch, type.c_str());
	char *typen = new char[50];
	typen = strcat(strcat(ch1, ch), ch2);
	ofstream outfile(typen, ios::app);
	if (!outfile)
	{
		cerr << "打开用户名数据库文件失败！";
		exit(1);
	}
	outfile << user[acc].get_accName() << " " << time << " " << state << endl;
	outfile.close();
}
//保存用户数据
void BankData::SaveUserData()
{
	ofstream outfile("BankUser.dat", ios::out);
	if (!outfile)
	{
		cerr << "打开数据库(BankUser.dat)文件失败！";
		exit(1);
	}
	int i;
	for (i = 0; i<UserNum; i++)
	{
		outfile << user[i].get_accNumber() << " " << user[i].get_accName() << " " << user[i].get_password() << " " << user[i].get_balance() << " " << user[i].get_id() << " " << user[i].get_homeads() << " " << user[i].get_state() << endl;
	}
	outfile.close();

}

int BankData::HomePage()//主页
{
	
	int choice;
	
	cout << "                ┏*************************┓" << endl;
	cout << "                ┃     欢迎光临GDF银行     ┃"<< endl;
	cout << "                ┗*************************┛" << endl;
	cout << "                       1.自助业务办理" << endl;
	cout << "                       2.柜台业务办理" << endl;
	cout << "                          请选择:";
	cin >> choice;
	while (true)
	{
		if (choice == 1)
		{
			return 1;
		}

		else if (choice == 2)
		{
			return 2;
		}
		else
		{
			cout << "输入有误，请输入选项前的数字(1或2)！" << endl;
			cout << "请重新输入：";
			cin >> choice;
		}
	}
	
}

int BankData::OpenAdmin()//读取Admin的信息
{
	int anum;
	//开始读取Admin信息到admin数组中
	ifstream infile("BankAdmin.dat", ios::in);
	anum = 0;
	if (!infile)
	{
		cerr << "打开管理员(BankAdmin.dat)文件失败!" << endl;
		exit(1);
	}
	while (!infile.eof())
	{
		infile >> admin[anum].name >> admin[anum].password;
		anum++;
	}
	infile.close();
	//信息读取完毕，admin数组中已存入Admin信息
	return anum;//返回一共读取到多少Admin条信息
}

int BankData::SearchAdmin(string n, int anum)//查找Admin
{
	for (int i = 0; i<anum; i++)
	{
		if (n == admin[i].name)
			return i;
	}
	return -1;
}
//检验Admin密码是否正确
bool BankData::CheckAdminPass(int i)
{
	int wrong = 0;
	string pass;
	while (1)
	{
		cout << "                       请输入密码：";
		cin >> pass;
		if (pass == admin[i].password)
			return true;
		else//密码输入错误触发
		{
			cerr << "密码输入有误，请重新输入！" << endl;
			wrong++;
			if (wrong > 2)
			{
				cerr << "Admin密码输入错误超过3次，即将退出系统..." << endl;
			}
			return false;
		}
	}
}

void BankData::MenuShow1()//自助业务办理菜单显示函数
{
	cout << "                欢迎使用银行自助业务办理服务" << endl;
	cout << "                ┏+++++++++++++++++++++++++┓" << endl;
	cout << "                ┃<<1.存款         取款.2>>┃" << endl;
	cout << "                ┃<<                     >>┃" << endl;
	cout << "                ┃<<3.查询         转账.4>>┃" << endl;
	cout << "                ┃<<                     >>┃" << endl;
	cout << "                ┃<<5.挂失         星空.i>>┃" << endl;
	cout << "                ┃<<                     >>┃" << endl;
	cout << "                ┃<<   	 0.退出         >>┃" << endl;
	cout << "                ┃<<                     >>┃" << endl;
	cout << "                ┗+++++++++++++++++++++++++┛" << endl;
}

void BankData::MenuShow2()//柜台业务办理显示函数
{
	cout << "                欢迎使用银行柜台业务办理服务" << endl;
	cout << "                ┏+++++++++++++++++++++++++┓" << endl;
	cout << "                ┃          1.开户         ┃" << endl;
	cout << "                ┃          ******         ┃" << endl;
	cout << "                ┃          2.销户         ┃" << endl;
	cout << "                ┃          ******         ┃" << endl;
	cout << "                ┃          3.解挂         ┃" << endl;
	cout << "                ┃          ******         ┃" << endl;
	cout << "                ┃          4.改密         ┃" << endl;
	cout << "                ┃          ******         ┃" << endl;
	cout << "                ┃          0.退出         ┃" << endl;
	cout << "                ┃          ******         ┃" << endl;
	cout << "                ┗+++++++++++++++++++++++++┛" << endl;
}
//开户
void BankData::AddNumber(int n)
{
	string pass1, pass2, name, id, h;
	double money;
	long acc;
	acc = 10001 + n;   //自动分配账号
	cout << "正在开户" << endl;
	while (1)
	{
		cout << "帐号：" << acc << endl;
		cout << "户主姓名：";
		cin >> name;
		cout << "密码：";
		cin >> pass1;
		cout << "确认密码：";
		cin >> pass2;
		//将开户的信息加入到User文件的末尾
		if (pass1 == pass2)
		{
			cout << "存入金额：";
			cin >> money;
			cout << "身份证号：";
			cin >> id;
			cout << "家庭住址：";
			cin >> h;
			ofstream outfile("BankUser.dat", ios::app);
			if (!outfile)
			{
				cerr << "打开数据库(BankUser.dat)文件失败！";
				exit(1);
			}
			outfile << acc << " " << name << " " << pass1 << " " << money << " " << id << " " << h << " " << 0 << endl;
			outfile.close();
			cout << "开户成功！" << endl;
			user[UserNum].SetUser(acc, name, pass1, money, id, h, 0);
			SaveUserLog(1, n);
			UserNum++;
			system("PAUSE ");
			//文件写入结束
			break;
		}
		else
		{
			cout << "两次密码输入不一致，请重新输入。" << endl;
			continue;
		}
		//信息更新完毕
	}
}
//销户
void BankData::DelNumber()
{
	long acc;
	string pass;
	char check;
	cout << "销户" << endl;
	cout << "待销户帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		while (1)
		{
			if (user[acc].CheckUserPass())
			{
				if (user[acc].get_state() == 0)
				{
					cout << "余额：" << user[acc].get_balance() << endl;
					cout << "确认销户(y/n)?";
					cin >> check;
					if (check == 'y' || check == 'Y')
					{
						cout << "取款" << user[acc].get_balance() << "元，销户成功！" << endl;
						user[acc].set_balance(0);
						user[acc].set_state(2);
						SaveUserLog(2, acc);
						system("PAUSE ");
						break;
					}
					else
					{
						cout << "销户程序已取消。" << endl;
						system("PAUSE");
						break;
					}
				}
				else
				{
					cout << "该账户为挂失或已经销户，无法进行销户操作。" << endl;
					system("PAUSE");
					break;
				}
			}
		}
	}
}
//存款
void BankData::AddMoney()
{
	long acc;
	double addmoney;
	cout << "存款" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		if (user[acc].get_state() == 0)
		{
			cout << "姓名：" << user[acc].get_accName() << endl;
			cout << "存款额：";
			cin >> addmoney;
			user[acc].set_balance(user[acc].get_balance() + addmoney);//将addmoney钱存入User的信息中
			cout << "现余额共计" << user[acc].get_balance() << "元,存款成功！" << endl;
			SaveUserLog(3, acc);
			system("PAUSE ");
		}
		else if (user[acc].get_state() == 2)
		{
			cout << "该账户目前已经销户." << endl;
			system("PAUSE ");
		}
		else
		{
			cout << "该账户目前已经挂失." << endl;
			system("PAUSE ");
		}
	}
}
//取款
void BankData::DelMoney()
{
	long acc;
	double money;
	cout << "取款" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				cout << "余额：" << user[acc].get_balance() << endl;
				while (1)
				{
					cout << "取款额：";
					cin >> money;
					if (money > user[acc].get_balance())
					{
						cout << "余额不足，取款失败！" << endl;
						continue;
					}
					else
					{
						user[acc].set_balance(user[acc].get_balance() - money);
						cout << "取出" << money << "元，现余额" << user[acc].get_balance() << "元。" << endl;
						SaveUserLog(4, acc);
						system("PAUSE ");
						break;
					}
				}
			}
			else
			{
				cout << "该账户挂失或者销户，无法进行取款操作。" << endl;
				system("PAUSE ");
			}
		}
	}

}
//显示user信息与日志
void BankData::ShowInfo()
{
	long acc;
	string logname, logtime, logstate;
	int lognum = 0;
	cout << "查询" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			cout << "余额：" << user[acc].get_balance() << endl;
			cout << "身份证号：" << user[acc].get_id() << endl;
			cout << "家庭住址：" << user[acc].get_homeads() << endl;
			cout << "当前状态：";
			switch (user[acc].get_state())//判断User的状态
			{
			case 0:cout << "正常" << endl; break;
			case 1:cout << "挂失" << endl; break;
			case 2:cout << "销户" << endl; break;
			}
			//开始进行日志读取
			string type;
			//生成将要读取的文件名
			type = int2str(acc + 10001);
			char ch1[25] = "BankUser";
			char ch2[8] = ".log";
			char ch[8];
			strcpy(ch, type.c_str());
			char *typen = new char[50];
			typen = strcat(strcat(ch1, ch), ch2);
			ifstream infile(typen, ios::in);
			if (!infile)
			{
				cerr << "打开用户日志文件失败!" << endl;
				exit(1);
			}
			cout << "---------------------------" << endl;
			cout << "日志记录:" << endl;
			while (infile >> logname >> logtime >> logstate)
			{
				cout << logname << " " << logtime << " " << logstate << endl;
				lognum++;
			}
			infile.close();
			cout << "查询完毕，共" << lognum << "条记录。" << endl;
			cout << "---------------------------" << endl;
			system("PAUSE ");
		}
	}
}
//转账
void BankData::TransferMoney()
{
	long acc, acc2;
	double money;
	cout << "转账" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				cout << "余额：" << user[acc].get_balance() << endl;
				while (1)
				{
					cout << "转账帐号：";
					cin >> acc2;
					cout << "转账金额：";
					cin >> money;
					if (CheckUser(acc2))
					{
						acc2 -= 10001;
						if (user[acc].get_balance() >= money)
						{
							user[acc].set_balance(user[acc].get_balance() - money);
							user[acc2].set_balance(user[acc2].get_balance() + money);
							cout << "转账成功！本账户余额" << user[acc].get_balance() << "元。" << endl;
							SaveUserLog(6, acc);
							system("PAUSE ");
							break;
						}
						else
						{
							cout << "余额不足，转账失败！" << endl;
							system("PAUSE");
							continue;
						}
					}
				}
			}
			else
			{
				cout << "该账户挂失或者销户，无法进行转账操作。" << endl;
				system("PAUSE ");
			}
		}
	}
}
//挂失
void BankData::LossReport()
{
	long acc;
	cout << "挂失" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				user[acc].set_state(1);
				cout << "挂失成功！" << endl;
				SaveUserLog(7, acc);
				system("PAUSE ");
			}
			else
			{
				cout << "该账户已经销户或挂失！" << endl;
				system("PAUSE ");
			}
		}
	}
}
//解挂
void BankData::SolutionLinked()
{
	long acc;
	cout << "解挂" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 1)
			{
				user[acc].set_state(0);
				cout << "解挂成功" << endl;
				SaveUserLog(8, acc);
			}
			else if (user[acc].get_state() == 0)
			{
				cout << "该账户状态正常，无需解挂。" << endl;
			}
			else if (user[acc].get_state() == 2)
			{
				cout << "该账户已经销户，无法解挂。" << endl;
			}
			system("PAUSE ");
		}
	}
}
//改密
void BankData::ChangePass()
{
	long acc;
	string pass1, pass2;
	cout << "改密" << endl;
	cout << "帐号：";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "姓名：" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				while (1)
				{
					cout << "请输入新密码：";
					cin >> pass1;
					cout << "确认密码：";
					cin >> pass2;
					if (pass1 == pass2)
					{
						user[acc].set_password(pass1);
						cout << "更改密码成功！" << endl;
						SaveUserLog(9, acc);
						system("PAUSE ");
						break;
					}
					else
					{
						cout << "两次密码输入不一致，请重新输入。" << endl;
						continue;
					}

				}
			}
			else
			{
				cout << "该账户挂失或者销户，无法进行改密操作。" << endl;
				system("PAUSE");
			}
		}
	}
}