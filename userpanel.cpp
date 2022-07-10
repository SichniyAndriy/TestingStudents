#include "Header.h"
using namespace std;

const bool userpanel(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	bool flag{ false };
	size_t u{ 0 };
	system("cls");
	cout << "����� ����������.\n"
		<< "1 - ����� � �������\n"
		<< "2 - �������� ����� ����\n"
		<< "0 - �����\n";
	switch (makechoice(3))
	{
	case 1:
		u = login(cnt_V);
		if (u) { flag = testBegin(u, cnt_V2); }
		break;
	case 2:
		flag = createUser(cnt_V, cnt_V2);
		break;
	case 0:
		return flag = false;
	}

	return flag;
}
const size_t login(const vector<L_and_P>& cnt_V)
{
	string tmp, tmp2;
	size_t counter{ 0 };
	cout << "������ ����: ";
	cin >> tmp;
	for (const auto& i : cnt_V)
	{
		if (i.get_Login() == tmp)
		{
			cout << "������ ������: ";
			if (i.get_Password() == inputPass()) {
				cout << "\n�� ������ ������!\n";
				return counter;
			}
			else { cerr << "\n������ �� �����"; return 0; }
		}
		++counter;
	}
	cerr << "\n���� �� �����";
	return 0;
}
const bool testBegin(const size_t f_Var, vector<User>& cnt_V2)
{
	srand(unsigned(time(NULL)));
	string name;
	cout << "\n���� ���� ���������?:\n";
	name = getName();
	vector<ElTest> test;

	if (!readTest(name, test)) { cerr << "���� �� �� ����������"; return false; }
	system("cls");
	size_t answ{ 0 }, tmp{ 0 }, ball{ 0 };
	for (size_t i = 0; i < 4; ++i)
	{
		tmp = rand() % test.size();
		test.at(tmp).show();
		cout << "\n������ ��� ������ ������(������ ��� 0 ��� ��������� �����): ";
		cin >> answ;
		if (!answ) return false;
		if (answ == test.at(tmp).get_AnswerNum()) ball += 3;
		cout << "\n";
	}

	name.erase(0, name.find_last_of('\\') + 1);
	name.erase(name.find(".txt"));
	if (cnt_V2.at(f_Var).get_Results().count(name))
	{
		if (cnt_V2.at(f_Var).get_Results().at(name) < ball) {
			cnt_V2.at(f_Var).set_Ball(name, ball);
		}
	}
	else { cnt_V2.at(f_Var).set_Results(name, ball); }
	cout << "�� ������� " << ball << " ����\n";
	system("pause");
	return true;
}

const bool createUser(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	string tmpL, tmpP;
	cin.ignore();
	cout << "������ ����: ";
	cin >> tmpL;
	cout << "������ ������: ";
	tmpP = inputPass();
	cnt_V.emplace_back(tmpL, tmpP);

	string tmpPr, tmpI, tmpPb, tmpA, tmpPh;
	cin.ignore();
	cout << "\n�������: ";
	getline(cin, tmpPr);
	cout << "��'�: ";
	getline(cin, tmpI);
	cout << "��-�������: ";
	getline(cin, tmpPb);
	cout << "������: ";
	getline(cin, tmpA);
	cout << "�������: ";
	getline(cin, tmpPh);
	cnt_V2.emplace_back(tmpL, tmpPr, tmpI, tmpPb, tmpA, tmpPh);

	return true;
}