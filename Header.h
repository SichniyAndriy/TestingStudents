#pragma once

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <conio.h>
#include <iomanip>

#define getListTests system("dir /b tests\\ > tmp.txt")

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::ostream;
using std::ofstream;

class L_and_P;
class User;
class ElTest;

//MAIN
void begin(vector<L_and_P>&);
const size_t greeting();
const size_t makechoice(const size_t);
const bool checkLP();
const string inputPass();
const string getName();
const size_t showListPartition(const vector<string>&);
void readTmp(vector<string>&);
const size_t readTest(const string, vector<ElTest>&);
void showTest(const string, vector<ElTest>&);
void demoTest();
void readFromUsers(vector<User>&);
void writeToFiles(const vector<L_and_P>&, const vector<User>&);

//ADMIN PANEL
const bool adminpanel(vector<L_and_P>&, vector<User>&);
const bool managementUsers(vector<L_and_P>&, vector<User>&);
void managementTesting();
void addPart();
void addAsk();
void delPart();
void delAsk();
void showStatistic(const vector<User>&);
//USER PANEL
const bool userpanel(vector<L_and_P>&, vector<User>&);
const size_t login(const vector<L_and_P>&);
const bool testBegin(const size_t, vector<User>&);
const bool createUser(vector<L_and_P>&, vector<User>&);

class User
{
public:
	User(const string c_L, const string c_Pr, const string c_I, const string c_PB,
		 const string c_Address, const string c_Phone)
		:login(c_L), pr(c_Pr), i(c_I), pb(c_PB), address(c_Address), phone(c_Phone) {}
	User(const string c_L,const string c_Pr, const string c_I, const string c_PB,
		 const string c_Address, const string c_Phone, const map<string, size_t> c_Results) 
		: login(c_L), pr(c_Pr), i(c_I), pb(c_PB), 
		  address(c_Address), phone(c_Phone), results(c_Results) {}

	//GETTERS
	inline const string get_Login()   const { return login; };
	inline const string get_Pr()	  const { return pr; }
	inline const string get_I()		  const { return i; }
	inline const string get_PB()      const { return pb; }
	inline const string get_Address() const { return address; }
	inline const string get_Phone()   const { return phone; }
	inline const map<string, size_t> get_Results() const { return results; }
	//SETTERS
	inline void set_Login  (const string m_L)   { login = m_L; };
	inline void set_Pr	   (const string m_Pr)	{ pr = m_Pr; }
	inline void set_I	   (const string m_I)	{ i = m_I; }
	inline void set_PB	   (const string m_pb)  { pb = m_pb; }
	inline void set_Address(const string m_A)   { address = m_A; }
	inline void set_Phone  (const string m_P)   { phone = m_P; }
	void set_Results(const string m_Str, const size_t m_Val) { results.emplace(m_Str, m_Val); }
	void set_Ball	(const string m_Str, const size_t m_Val) { results.at(m_Str) = m_Val; }

	void show() const;
	void showResults() const;
	void toFile(ofstream&) const;
	void resultsToFile(ofstream&) const;

private:
	string login;
	string pr;
	string i;
	string pb;
	string address;
	string phone;
	map<string, size_t> results;
};

class L_and_P
{
public:
	L_and_P(const string c_L, const string c_P) : login(c_L), password(c_P) {}

	inline const string get_Login()	   const { return login; }
	inline const string get_Password() const { return password; }

private:
	string login;
	string password;
};

class ElTest
{
public:
	ElTest(const string c_Q, const size_t c_A, const vector<string> c_AL)
		: question(c_Q), answerNum(c_A), answersList(c_AL) {}

	inline const string			get_Question()	  const { return question; }
	inline const size_t			get_AnswerNum()	  const { return answerNum; }
	inline const vector<string> get_AnswersList() const { return answersList; }

	inline void show_AnswerNum() const { cout << answerNum; }
	void show() const;
	void toFile(ofstream&) const;

private:
	string question;
	size_t answerNum;
	vector<string> answersList;
};