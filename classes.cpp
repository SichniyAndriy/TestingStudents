#include "Header.h"

using namespace std;
//USER METHODS

void User::show() const
{

	cout << setw(11) << left << "Логін" << ": " << login << '\n'
		<< setw(11) << "Прізвище" << ": " << pr << '\n'
		<< setw(11) << "Ім'я" << ": " << i << '\n'
		<< setw(11) << "По-батькові" << ": " << pb << '\n'
		<< setw(11) << "Адреса" << ": " << address << '\n'
		<< setw(11) << "Телефон" << ": " << phone << '\n';
	showResults();
}
void User::showResults() const
{
	size_t size = results.size();
	for (auto& i: results)
	{
		cout << i.first << ": " << i.second << '\n';
	}
}
void User::toFile(ofstream& m_Fout) const
{
	m_Fout << login << '\n' << pr << '\n' << i << '\n' << pb << '\n'
		   << address << '\n' << phone << '\n';
	resultsToFile(m_Fout);
}
void User::resultsToFile(ofstream& m_Fout) const
{
	size_t size = results.size();
	for (auto& i : results)
	{
		m_Fout << i.first << ' ' << i.second;
		if (--size) m_Fout << ' ';
	}
}

//ELEMENT OF TEST METHODS
void ElTest::show() const
{
	size_t var{ 0 };
	cout << question << ":\n";
	size_t len = answersList.size();
	for (const auto& i : answersList)
	{
		cout << ++var << ") " << i; if (--len) cout << '\n';
	}
}

void ElTest::toFile(ofstream& f_Out) const
{
	f_Out << question << '\n' << answerNum << '\n';
	for (auto &i : answersList)
	{
		f_Out << i << '\n';
	}
	f_Out << "end";
}