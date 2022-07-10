#include "Header.h"
using namespace std;

const bool adminpanel(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	system("cls");
	cout << "Режим Адміністратора.\n"
		<< "1 - Керування користувачами\n"
		<< "2 - Керування тестуванням\n"
		<< "3 - Перегляд статистики\n"
		<< "0 - Вихід\n";
	bool flag{ false };
	switch (makechoice(3))
	{
	system("cls");
	case 1:

		flag = managementUsers(cnt_V, cnt_V2);
		break;
	case 2:
		managementTesting();
		break;
	case 3:
		showStatistic(cnt_V2);
		break;
	case 0:
		flag = false;
	}
	system("pause");
	return flag;
}
////////////////////////////////////////////////////////////////////////////
const bool managementUsers(vector<L_and_P>& cnt_V, vector<User>& cnt_V2)
{
	cout << "Ви можете видалити користувача або натисніть ноль для виходу:\n\n";
	size_t choice{ 0 };
	size_t length = cnt_V2.size();
	for (size_t i = 1; i < length; ++i)
	{
		cout << "№ " << setw(3) << i << "\n";
		cnt_V2.at(i).show();
		cout << '\n';
	}
	choice = makechoice(length);
	if (choice)
	{
		cnt_V.erase(cnt_V.begin() + choice);
		cnt_V2.erase(cnt_V2.begin() + choice);
		cout << "Видалення завершене\n\n";
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////
void managementTesting()
{
	system("cls");
	cout << "1 - Додати розділ\n"
		 << "2 - Додати питання\n"
		 << "3 - Видалити розділ\n"
		 << "4 - Видалити питання\n"
		 << "0 - Вихід\n";
	bool flagChange{ false };
	switch (makechoice(4))
	{
	case 1:
		addPart();
		break;
	case 2:
		addAsk();
		break;
	case 3:
		delPart();
		break;
	case 4:
		delAsk();
	}
}
void addPart()
{
	cout << "Який розділ добавити?: ";
	getListTests;
	string tmp, tmp2;
	fstream file;

	cin >> tmp;
	if (tmp.find('.') == -1) tmp.append(".txt");
	file.open("tmp.txt", ios::in); assert(file);
	getline(file, tmp2);
	while (!file.eof())
	{
		if (!tmp.compare(tmp2)) { cout << "Такий розділ вже існує\n"; return; }
		getline(file, tmp2);
	}
	tmp = "tests/" + tmp;
	file.close();
	file.open(tmp, ios::out);
	file.close();
	cout << "Розділ додано\n";
}
void addAsk()
{
	cout << "В який розділ добавити запитання?\n(Введіть існуючий, або введіть назву нового): ";
	getListTests;
	string tmp;
	cin.ignore();
	getline(cin, tmp);
	tmp = "tests\\" + tmp + ".txt";
	ofstream file;
	file.open(tmp, ios::app);
	assert(file);
	cout << "Введіть запитання:\n";
	getline(cin , tmp);
	file << tmp << '\n';
	cout << "Введіть правильний варіант вдповіді(цифрою): ";
	size_t var{ 0 };
	cin >> var;
	file << var;
	cout << "Введіть варіанти відповідей(Enter для завершення):\n";
	cin.ignore();
	getline(cin, tmp);
	while (tmp != "")
	{
		file << '\n';
		file << tmp;
		getline(cin, tmp);
	}
	file << "end";
	file.close();
}
void delPart()
{
	cout << "Який розділ видалити?:\n";
	getListTests;
	string tmp = getName();
	if (!remove(tmp.c_str())) cout << "Розділ видалено\n";
}
void delAsk()
{
	cout << "В якому розділі видалити запитання?:\n";
	getListTests;
	const string name = getName();
	vector<ElTest> test;

	readTest(name, test);
	showTest(name, test);

	cout << "\n\nЯке питання видалити?\n";
	size_t counter = makechoice(test.size());
	if (counter > 0 || counter <= test.size()) { --counter; }
	else { cerr << "Неправильний номер\n"; return; }

	test.erase(test.begin() + counter);

	ofstream fout;
	fout.open(name); assert(fout);
	counter = test.size();
	for (const auto &i: test)
	{
		i.toFile(fout);
		if (--counter) fout << '\n';
	}
	fout.close();
}

////////////////////////////////////////////////////////////////////////////
void showStatistic(const vector<User>& cnt_V2)
{
	size_t n{ 0 };
	for (const auto& i : cnt_V2)
	{
		if (!n++) continue;
		cout << '\n' << i.get_Login() << '\n';
		i.showResults();
		cout << '\n';
	}
}