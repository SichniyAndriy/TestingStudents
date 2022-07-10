#include "Header.h"

using namespace std;

int main()
{
    /*setlocale(LC_CTYPE, "Ukranian");*/
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool flagExit, flagChange{ false };
    vector<L_and_P> LP_List;
    begin(LP_List);
    cout << "Вас вітає програма тестування.\n";
    vector<User> users_List;
    readFromUsers(users_List);

    for (;;)
    {
        flagExit = false;
        switch (greeting())
        {
        case 1:
            if (checkLP()) {
                flagChange = adminpanel(LP_List, users_List);
            }
            break;
        case 2:
            flagChange = userpanel(LP_List, users_List);
            break;
        case 3:
            demoTest();
            break;
        case 0:
            flagExit = true;
        }
        if (flagChange) writeToFiles(LP_List, users_List);
        if (flagExit) break;
    }
    writeToFiles(LP_List, users_List);
    return 0;
}

void begin(vector<L_and_P>& cnt_V)
{
    fstream file;
    string tmpL, tmpP;
    file.open("logAndPass.txt", ios::in);
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, tmpL);
            getline(file, tmpP);
            cnt_V.emplace_back(tmpL, tmpP);
        }
    }
    else
    {
        file.open("logAndPass.txt", ios::out); assert(file);
        cout << "Створіть логін адміністратора: ";
        cin >> tmpL;
        file << tmpL << '\n';
        cout << "Створіть пароль адміністратора: ";
        char ch = 0;
        file << inputPass();
        cnt_V.emplace_back(tmpL, tmpP);
    }
    file.close();
}
const bool checkLP()
{
    string tmp, tmp1, tmp2;
    ifstream file;
    file.open("logAndPass.txt"); assert(file);
    getline(file, tmp1);
    getline(file, tmp2);
    file.close();
    cout << "Введіть логін адміністратора: ";
    cin >> tmp;
    if (tmp1 == tmp)
    {
        cout << "Введіть пароль адміністратора: ";
        if (tmp2 == inputPass()) return true;
    }
    cerr << "Логін або пароль невірні";

    return false;
}
const string inputPass()
{
    char ch = 0;
    string tmp;
    while ((ch = _getch()) != 13)
    {
        tmp += to_string(ch);
        cout << '*';
    }
    return tmp;
}
const size_t greeting()
{
    system("cls");
    cout << "Виберіть режим програми\n"
         << "1 - Режим адміністрування\n"
         << "2 - Режим тестування\n"
         << "3 - Випробувальний режим\n"
         << "0 - Вихід\n";

    return makechoice(3u);
}
const size_t makechoice(const size_t f_Max)
{
    int choice{ 0 };
    do {
        cout << "Зробіть ваш вибір: ";
        if ((cin >> choice).fail()) { cin.clear(); while (cin.get() != '\n'); }
    } while (choice < 0 || choice > f_Max);

    return choice;
}
const string getName()
{
    vector<string> cnt_V;
    readTmp(cnt_V);
    size_t counter = showListPartition(cnt_V);
    counter = makechoice(counter);
    return "tests\\" + cnt_V.at(--counter) + ".txt";
}
void readTmp(vector<string>& cnt_V)
{
    ifstream file;
    getListTests;
    file.open("tmp.txt"); assert(file);

    string tmp;
    getline(file, tmp);
    while (!tmp.empty())
    {
        tmp.erase(tmp.find(".txt"));
        cnt_V.push_back(tmp);
        getline(file, tmp);
    }
    file.close();
}
const size_t readTest(const string f_Str, vector<ElTest>& cl_V)
{
    string asq, tmp;
    size_t varAnsw;
    vector<string> answ;

    ifstream fin;
    fin.open(f_Str); assert(fin);
    getline(fin, asq);
    while (!fin.eof() and !asq.empty())
    {
        fin >> varAnsw;
        fin.ignore();
        getline(fin, tmp);
        while (tmp != "end")
        {
            answ.push_back(tmp);
            getline(fin, tmp);
        }
        cl_V.emplace_back(asq, varAnsw, answ);
        answ.clear();
        getline(fin, asq);
    }
    fin.close();
    return cl_V.size();
}
void showTest(const string f_Str, vector<ElTest>& cl_V)
{
    system("cls");
    size_t len = cl_V.size();
    size_t counter{ 0 };
    for (const auto& i : cl_V)
    {
        cout << ++counter << ")\n";
        i.show();
        if (--len) cout << '\n';
    }
}
const size_t showListPartition(const vector<string>& cnt_V)
{
    size_t counter{ 0 };
    for (auto& i : cnt_V)
    {
        cout << ++counter << ") " << i << '\n';
    }
    return counter;
}
void demoTest()
{
    string name;
    cout << "\nЯкий тест проходимо?:\n";
    name = getName();
    vector<ElTest> test;
    readTest(name, test);
    if (test.empty()) { cerr << "Тест порожній"; return; }

    system("cls");
    size_t answ{ 0 }, tmp{ 0 }, ball{ 0 };
    for (size_t i = 0; i < 4; ++i)
    {
        tmp = rand() % test.size();
        test.at(tmp).show();
        cout << "\nВведіть ваш варіант відповіді(цифрою або 0 для зупинення тесту): ";
        cin >> answ;
        if (!answ) return;
        if (answ == test.at(tmp).get_AnswerNum()) ball += 3;
        cout << "\n";
    }
    cout << "Ви набрали " << ball << " балів\n";
    system("pause");
}
void readFromUsers(vector<User>& cnt_V)
{
    ifstream fin;

    fin.open("users.txt");
    assert(fin);
    string tmpL, tmpPr, tmpI, tmpPB, tmpAddress, tmpPhone, tmpResStr;
    map<string, size_t> tmpRes;
    string tmp;
    int x;
    size_t i{ 0 };
    getline(fin, tmpL);
    while (!fin.eof() and !tmpL.empty())
    {
        getline(fin, tmpPr);
        getline(fin, tmpI);
        getline(fin, tmpPB);
        getline(fin, tmpAddress);
        getline(fin, tmpPhone);
        getline(fin, tmpResStr);
        while (i != -1 && !tmpResStr.empty())
        {
            i = tmpResStr.find_first_of(' ');
            tmp = tmpResStr.substr(0, i);
            tmpResStr.erase(0, i + 1);
            i = tmpResStr.find_first_of(' '); 
            x = stoi(tmpResStr.substr(0, i));
            tmpResStr.erase(0, i + 1);
            tmpRes.emplace(tmp, x);
        }
        cnt_V.emplace_back(tmpL, tmpPr, tmpI, tmpPB, tmpAddress, tmpPhone, tmpRes);
        tmpRes.clear();
        i = 0;
        getline(fin, tmpL);
    }
    fin.close();
}
void writeToFiles(const vector<L_and_P>& cnt_V, const vector<User>& cnt_V2)
{
    ofstream file;
    file.open("logAndPass.txt"); assert(file);
    size_t n = cnt_V.size();
    for (const auto& i: cnt_V)
    {
        file << i.get_Login() << '\n' << i.get_Password();
        if (--n) file << '\n';
    }
    file.close();
    file.open("users.txt"); assert(file);
    n = cnt_V2.size();
    for (const auto& i : cnt_V2)
    {
        i.toFile(file);
        if (--n) file << '\n';
    }
    file.close();
}