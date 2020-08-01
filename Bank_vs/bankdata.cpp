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

BankData::BankData()//���캯��
{
	long number;
	string name, pass, id, h;
	double balance;
	int state;
	UserNum = 0;
	//��ʼ��ȡUser����Ϣ
	fstream infile;
	infile.open("BankUser.dat", ios::app | ios::in);
	if (!infile)
	{
		cerr << "�����ݿ�(BankUser.dat)�ļ�ʧ�ܣ�";
		exit(1);
	}
	while (infile >> number >> name >> pass >> balance >> id >> h >> state)
	{
		user[UserNum].SetUser(number, name, pass, balance, id, h, state);
		UserNum++;
	}
	infile.close();
	//User��Ϣ��ȡ��ϣ���������UserNum
}

BankData::~BankData()//��������
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

string BankData::gettime()//��ȡϵͳʱ��
{
	time_t curtime = time(0);
	tm tim = *localtime(&curtime);
	int day, mon, year;
	int hour, min, sec;
	string time;
	hour = tim.tm_hour;//ʱ
	min = tim.tm_min;//��
	sec = tim.tm_sec;//��
	day = tim.tm_mday;//��
	mon = tim.tm_mon;//��
	year = tim.tm_year;//��
	time = int2str(year + 1900) + "-" + int2str(mon + 1) + "-" + int2str(day) + "_" + int2str(hour) + ":" + int2str(min) + ":" + int2str(sec);
	return time;
}

void BankData::about()//�ǿ�
{
	struct STAR
	{
		double x; 
		int y; 
		double step; 
		int color;
	};
	STAR star[200];
	srand((unsigned)time(NULL)); // ������� 
	initgraph(640, 480); // ��ͼ�δ��� 
	for (int i = 0; i < 200; i++)
	{
		star[i].x = 0;
		star[i].y = rand() % 480;
		star[i].step = (rand() % 5000) / 1000.0 + 1;
		star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5); // �ٶ�Խ�죬��ɫԽ�� 
		star[i].color = RGB(100, 200, 230);
		star[i].x = rand() % 640;
	}
	while (!_kbhit())
	{
		for (int i = 0; i < 200; i++)
		{
			putpixel((int)star[i].x, star[i].y, 0);// ������λ�� 
			star[i].x += star[i].step;
			if (star[i].x > 640)
			{
				star[i].x = 0;
				star[i].y = rand() % 480;
				star[i].step = (rand() % 5000) / 1000.0 + 1;
				star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5); // �ٶ�Խ�죬��ɫԽ�� 
				star[i].color = RGB(100, 200, 230);  //�ϳ���ɫ
			}
			putpixel((int)star[i].x, star[i].y, star[i].color);  //����
		}
		Sleep(20);
	}
	closegraph(); // �ر�ͼ�δ���
	cout << "��ӭʹ�����д���ϵͳ1.0��" << endl;
	cout << "ʹ�������κ���������ϵGDF��13218886562" << endl;
	system("PAUSE");
}

void BankData::OpenUserData()
{
	long number;
	string name, pass, id, h;
	double balance;
	int state;
	UserNum = 0;
	//��ʼ��ȡUser����Ϣ
	ifstream infile("BankUser.dat", ios::in);
	if (!infile)
	{
		cerr << "�����ݿ�(BankUser.dat)�ļ�ʧ�ܣ�";
		exit(1);
	}
	while (infile >> number >> name >> pass >> balance >> id >> h >> state)
	{
		user[UserNum].SetUser(number, name, pass, balance, id, h, state);
		UserNum++;
	}
	infile.close();
	//User��Ϣ��ȡ��ϣ���������UserNum
}
//�����û���
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
	cout << "û���ҵ����˻���" << endl;
	system("PAUSE");
	return false;
}

void BankData::SaveUserLog(int i, int acc)//��¼�û���־
{
	string type, time, state;
	switch (i)
	{
	case 1:state = "����"; break;
	case 2:state = "����"; break;
	case 3:state = "���"; break;
	case 4:state = "ȡ��"; break;
	case 6:state = "ת��"; break;
	case 7:state = "��ʧ"; break;
	case 8:state = "���"; break;
	case 9:state = "����"; break;
	}
	time = gettime();
	type = int2str(acc + 10001);
	//strcpy(p,type.data());����ת����string 2 char*
	char ch1[25] = "BankUser";
	char ch2[8] = ".log";
	char ch[8];
	strcpy(ch, type.c_str());
	char *typen = new char[50];
	typen = strcat(strcat(ch1, ch), ch2);
	ofstream outfile(typen, ios::app);
	if (!outfile)
	{
		cerr << "���û������ݿ��ļ�ʧ�ܣ�";
		exit(1);
	}
	outfile << user[acc].get_accName() << " " << time << " " << state << endl;
	outfile.close();
}
//�����û�����
void BankData::SaveUserData()
{
	ofstream outfile("BankUser.dat", ios::out);
	if (!outfile)
	{
		cerr << "�����ݿ�(BankUser.dat)�ļ�ʧ�ܣ�";
		exit(1);
	}
	int i;
	for (i = 0; i<UserNum; i++)
	{
		outfile << user[i].get_accNumber() << " " << user[i].get_accName() << " " << user[i].get_password() << " " << user[i].get_balance() << " " << user[i].get_id() << " " << user[i].get_homeads() << " " << user[i].get_state() << endl;
	}
	outfile.close();

}

int BankData::HomePage()//��ҳ
{
	
	int choice;
	
	cout << "                ��*************************��" << endl;
	cout << "                ��     ��ӭ����GDF����     ��"<< endl;
	cout << "                ��*************************��" << endl;
	cout << "                       1.����ҵ�����" << endl;
	cout << "                       2.��̨ҵ�����" << endl;
	cout << "                          ��ѡ��:";
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
			cout << "��������������ѡ��ǰ������(1��2)��" << endl;
			cout << "���������룺";
			cin >> choice;
		}
	}
	
}

int BankData::OpenAdmin()//��ȡAdmin����Ϣ
{
	int anum;
	//��ʼ��ȡAdmin��Ϣ��admin������
	ifstream infile("BankAdmin.dat", ios::in);
	anum = 0;
	if (!infile)
	{
		cerr << "�򿪹���Ա(BankAdmin.dat)�ļ�ʧ��!" << endl;
		exit(1);
	}
	while (!infile.eof())
	{
		infile >> admin[anum].name >> admin[anum].password;
		anum++;
	}
	infile.close();
	//��Ϣ��ȡ��ϣ�admin�������Ѵ���Admin��Ϣ
	return anum;//����һ����ȡ������Admin����Ϣ
}

int BankData::SearchAdmin(string n, int anum)//����Admin
{
	for (int i = 0; i<anum; i++)
	{
		if (n == admin[i].name)
			return i;
	}
	return -1;
}
//����Admin�����Ƿ���ȷ
bool BankData::CheckAdminPass(int i)
{
	int wrong = 0;
	string pass;
	while (1)
	{
		cout << "                       ���������룺";
		cin >> pass;
		if (pass == admin[i].password)
			return true;
		else//����������󴥷�
		{
			cerr << "���������������������룡" << endl;
			wrong++;
			if (wrong > 2)
			{
				cerr << "Admin����������󳬹�3�Σ������˳�ϵͳ..." << endl;
			}
			return false;
		}
	}
}

void BankData::MenuShow1()//����ҵ�����˵���ʾ����
{
	cout << "                ��ӭʹ����������ҵ��������" << endl;
	cout << "                ��+++++++++++++++++++++++++��" << endl;
	cout << "                ��<<1.���         ȡ��.2>>��" << endl;
	cout << "                ��<<                     >>��" << endl;
	cout << "                ��<<3.��ѯ         ת��.4>>��" << endl;
	cout << "                ��<<                     >>��" << endl;
	cout << "                ��<<5.��ʧ         �ǿ�.i>>��" << endl;
	cout << "                ��<<                     >>��" << endl;
	cout << "                ��<<   	 0.�˳�         >>��" << endl;
	cout << "                ��<<                     >>��" << endl;
	cout << "                ��+++++++++++++++++++++++++��" << endl;
}

void BankData::MenuShow2()//��̨ҵ�������ʾ����
{
	cout << "                ��ӭʹ�����й�̨ҵ��������" << endl;
	cout << "                ��+++++++++++++++++++++++++��" << endl;
	cout << "                ��          1.����         ��" << endl;
	cout << "                ��          ******         ��" << endl;
	cout << "                ��          2.����         ��" << endl;
	cout << "                ��          ******         ��" << endl;
	cout << "                ��          3.���         ��" << endl;
	cout << "                ��          ******         ��" << endl;
	cout << "                ��          4.����         ��" << endl;
	cout << "                ��          ******         ��" << endl;
	cout << "                ��          0.�˳�         ��" << endl;
	cout << "                ��          ******         ��" << endl;
	cout << "                ��+++++++++++++++++++++++++��" << endl;
}
//����
void BankData::AddNumber(int n)
{
	string pass1, pass2, name, id, h;
	double money;
	long acc;
	acc = 10001 + n;   //�Զ������˺�
	cout << "���ڿ���" << endl;
	while (1)
	{
		cout << "�ʺţ�" << acc << endl;
		cout << "����������";
		cin >> name;
		cout << "���룺";
		cin >> pass1;
		cout << "ȷ�����룺";
		cin >> pass2;
		//����������Ϣ���뵽User�ļ���ĩβ
		if (pass1 == pass2)
		{
			cout << "�����";
			cin >> money;
			cout << "���֤�ţ�";
			cin >> id;
			cout << "��ͥסַ��";
			cin >> h;
			ofstream outfile("BankUser.dat", ios::app);
			if (!outfile)
			{
				cerr << "�����ݿ�(BankUser.dat)�ļ�ʧ�ܣ�";
				exit(1);
			}
			outfile << acc << " " << name << " " << pass1 << " " << money << " " << id << " " << h << " " << 0 << endl;
			outfile.close();
			cout << "�����ɹ���" << endl;
			user[UserNum].SetUser(acc, name, pass1, money, id, h, 0);
			SaveUserLog(1, n);
			UserNum++;
			system("PAUSE ");
			//�ļ�д�����
			break;
		}
		else
		{
			cout << "�����������벻һ�£����������롣" << endl;
			continue;
		}
		//��Ϣ�������
	}
}
//����
void BankData::DelNumber()
{
	long acc;
	string pass;
	char check;
	cout << "����" << endl;
	cout << "�������ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		while (1)
		{
			if (user[acc].CheckUserPass())
			{
				if (user[acc].get_state() == 0)
				{
					cout << "��" << user[acc].get_balance() << endl;
					cout << "ȷ������(y/n)?";
					cin >> check;
					if (check == 'y' || check == 'Y')
					{
						cout << "ȡ��" << user[acc].get_balance() << "Ԫ�������ɹ���" << endl;
						user[acc].set_balance(0);
						user[acc].set_state(2);
						SaveUserLog(2, acc);
						system("PAUSE ");
						break;
					}
					else
					{
						cout << "����������ȡ����" << endl;
						system("PAUSE");
						break;
					}
				}
				else
				{
					cout << "���˻�Ϊ��ʧ���Ѿ��������޷���������������" << endl;
					system("PAUSE");
					break;
				}
			}
		}
	}
}
//���
void BankData::AddMoney()
{
	long acc;
	double addmoney;
	cout << "���" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		if (user[acc].get_state() == 0)
		{
			cout << "������" << user[acc].get_accName() << endl;
			cout << "���";
			cin >> addmoney;
			user[acc].set_balance(user[acc].get_balance() + addmoney);//��addmoneyǮ����User����Ϣ��
			cout << "������" << user[acc].get_balance() << "Ԫ,���ɹ���" << endl;
			SaveUserLog(3, acc);
			system("PAUSE ");
		}
		else if (user[acc].get_state() == 2)
		{
			cout << "���˻�Ŀǰ�Ѿ�����." << endl;
			system("PAUSE ");
		}
		else
		{
			cout << "���˻�Ŀǰ�Ѿ���ʧ." << endl;
			system("PAUSE ");
		}
	}
}
//ȡ��
void BankData::DelMoney()
{
	long acc;
	double money;
	cout << "ȡ��" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				cout << "��" << user[acc].get_balance() << endl;
				while (1)
				{
					cout << "ȡ��";
					cin >> money;
					if (money > user[acc].get_balance())
					{
						cout << "���㣬ȡ��ʧ�ܣ�" << endl;
						continue;
					}
					else
					{
						user[acc].set_balance(user[acc].get_balance() - money);
						cout << "ȡ��" << money << "Ԫ�������" << user[acc].get_balance() << "Ԫ��" << endl;
						SaveUserLog(4, acc);
						system("PAUSE ");
						break;
					}
				}
			}
			else
			{
				cout << "���˻���ʧ�����������޷�����ȡ�������" << endl;
				system("PAUSE ");
			}
		}
	}

}
//��ʾuser��Ϣ����־
void BankData::ShowInfo()
{
	long acc;
	string logname, logtime, logstate;
	int lognum = 0;
	cout << "��ѯ" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			cout << "��" << user[acc].get_balance() << endl;
			cout << "���֤�ţ�" << user[acc].get_id() << endl;
			cout << "��ͥסַ��" << user[acc].get_homeads() << endl;
			cout << "��ǰ״̬��";
			switch (user[acc].get_state())//�ж�User��״̬
			{
			case 0:cout << "����" << endl; break;
			case 1:cout << "��ʧ" << endl; break;
			case 2:cout << "����" << endl; break;
			}
			//��ʼ������־��ȡ
			string type;
			//���ɽ�Ҫ��ȡ���ļ���
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
				cerr << "���û���־�ļ�ʧ��!" << endl;
				exit(1);
			}
			cout << "---------------------------" << endl;
			cout << "��־��¼:" << endl;
			while (infile >> logname >> logtime >> logstate)
			{
				cout << logname << " " << logtime << " " << logstate << endl;
				lognum++;
			}
			infile.close();
			cout << "��ѯ��ϣ���" << lognum << "����¼��" << endl;
			cout << "---------------------------" << endl;
			system("PAUSE ");
		}
	}
}
//ת��
void BankData::TransferMoney()
{
	long acc, acc2;
	double money;
	cout << "ת��" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				cout << "��" << user[acc].get_balance() << endl;
				while (1)
				{
					cout << "ת���ʺţ�";
					cin >> acc2;
					cout << "ת�˽�";
					cin >> money;
					if (CheckUser(acc2))
					{
						acc2 -= 10001;
						if (user[acc].get_balance() >= money)
						{
							user[acc].set_balance(user[acc].get_balance() - money);
							user[acc2].set_balance(user[acc2].get_balance() + money);
							cout << "ת�˳ɹ������˻����" << user[acc].get_balance() << "Ԫ��" << endl;
							SaveUserLog(6, acc);
							system("PAUSE ");
							break;
						}
						else
						{
							cout << "���㣬ת��ʧ�ܣ�" << endl;
							system("PAUSE");
							continue;
						}
					}
				}
			}
			else
			{
				cout << "���˻���ʧ�����������޷�����ת�˲�����" << endl;
				system("PAUSE ");
			}
		}
	}
}
//��ʧ
void BankData::LossReport()
{
	long acc;
	cout << "��ʧ" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				user[acc].set_state(1);
				cout << "��ʧ�ɹ���" << endl;
				SaveUserLog(7, acc);
				system("PAUSE ");
			}
			else
			{
				cout << "���˻��Ѿ��������ʧ��" << endl;
				system("PAUSE ");
			}
		}
	}
}
//���
void BankData::SolutionLinked()
{
	long acc;
	cout << "���" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 1)
			{
				user[acc].set_state(0);
				cout << "��ҳɹ�" << endl;
				SaveUserLog(8, acc);
			}
			else if (user[acc].get_state() == 0)
			{
				cout << "���˻�״̬�����������ҡ�" << endl;
			}
			else if (user[acc].get_state() == 2)
			{
				cout << "���˻��Ѿ��������޷���ҡ�" << endl;
			}
			system("PAUSE ");
		}
	}
}
//����
void BankData::ChangePass()
{
	long acc;
	string pass1, pass2;
	cout << "����" << endl;
	cout << "�ʺţ�";
	cin >> acc;
	if (CheckUser(acc))
	{
		acc -= 10001;
		cout << "������" << user[acc].get_accName() << endl;
		if (user[acc].CheckUserPass())
		{
			if (user[acc].get_state() == 0)
			{
				while (1)
				{
					cout << "�����������룺";
					cin >> pass1;
					cout << "ȷ�����룺";
					cin >> pass2;
					if (pass1 == pass2)
					{
						user[acc].set_password(pass1);
						cout << "��������ɹ���" << endl;
						SaveUserLog(9, acc);
						system("PAUSE ");
						break;
					}
					else
					{
						cout << "�����������벻һ�£����������롣" << endl;
						continue;
					}

				}
			}
			else
			{
				cout << "���˻���ʧ�����������޷����и��ܲ�����" << endl;
				system("PAUSE");
			}
		}
	}
}