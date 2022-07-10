#include "Header.h"
using namespace std;

const bool userpanel(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	bool flag{ false };
	size_t u{ 0 };
	system("cls");
	cout << "Режим тестування.\n"
		<< "1 - Увійти в систему\n"
		<< "2 - Створити новий логін\n"
		<< "0 - Вихід\n";
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
	cout << "Введіть логін: ";
	cin >> tmp;
	for (const auto& i : cnt_V)
	{
		if (i.get_Login() == tmp)
		{
			cout << "Введіть пароль: ";
			if (i.get_Password() == inputPass()) {
				cout << "\nВи успішно увійшли!\n";
				return counter;
			}
			else { cerr << "\nПароль не вірний"; return 0; }
		}
		++counter;
	}
	cerr << "\nЛогін не вірний";
	return 0;
}
const bool testBegin(const size_t f_Var, vector<User>& cnt_V2)
{
	srand(unsigned(time(NULL)));
	string name;
	cout << "\nЯкий тест проходимо?:\n";
	name = getName();
	vector<ElTest> test;

	if (!readTest(name, test)) { cerr << "Тест ще не заповнений"; return false; }
	system("cls");
	size_t answ{ 0 }, tmp{ 0 }, ball{ 0 };
	for (size_t i = 0; i < 4; ++i)
	{
		tmp = rand() % test.size();
		test.at(tmp).show();
		cout << "\nВведіть ваш варіант відповіді(цифрою або 0 для зупинення тесту): ";
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
	cout << "Ви набрали " << ball << " балів\n";
	system("pause");
	return true;
}

const bool createUser(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	string tmpL, tmpP;
	cin.ignore();
	cout << "Введіть логін: ";
	cin >> tmpL;
	cout << "Введіть пароль: ";
	tmpP = inputPass();
	cnt_V.emplace_back(tmpL, tmpP);

	string tmpPr, tmpI, tmpPb, tmpA, tmpPh;
	cin.ignore();
	cout << "\nПрізвище: ";
	getline(cin, tmpPr);
	cout << "Ім'я: ";
	getline(cin, tmpI);
	cout << "По-батькові: ";
	getline(cin, tmpPb);
	cout << "Адреса: ";
	getline(cin, tmpA);
	cout << "Телефон: ";
	getline(cin, tmpPh);
	cnt_V2.emplace_back(tmpL, tmpPr, tmpI, tmpPb, tmpA, tmpPh);

	return true;
}