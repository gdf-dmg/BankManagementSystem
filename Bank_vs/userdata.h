#pragma once
#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;
class UserData//用户类
{
private:
	long accNumber;
	string accName;
	string password;
	double balance;
	string identity;
	string homeads;
	int state;//状态 0:正常 -1:挂失 2:销户
public:
	void SetUser(long a, string n, string p, double b, string i, string h, int s);
	long get_accNumber() { return accNumber; }
	string get_accName() { return accName; }
	string get_password() { return password; }
	double get_balance() { return balance; }
	string get_id() { return identity; }
	string get_homeads() { return homeads; }
	int get_state() { return state; }
	void set_accNumber(long num) { accNumber = num; }
	void set_accName(string n) { accName = n; }
	void set_password(string p) { password = p; }
	void set_balance(double b) { balance = b; }
	void set_id(string id) { identity = id; }
	void set_homeads(string h) { homeads = h; }
	void set_state(int s) { state = s; }
	bool CheckUserPass();
};
struct Admin
{
	string name;
	string password;
};
#endif 
