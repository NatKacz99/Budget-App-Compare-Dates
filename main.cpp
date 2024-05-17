#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Markup.h"

using namespace std;

bool isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    else return false;
}
int getLastDayOfCurrentMonth(int &year, int &month)
{
    switch(month)
    {
    case 1:
        return 31;
    case 2:
        return isLeapYear(year) ? 29 : 28;
    case 3:
        return 31;
    case 4:
        return 30;
    case 5:
        return 31;
    case 6:
        return 30;
    case 7:
        return 31;
    case 8:
        return 31;
    case 9:
        return 30;
    case 10:
        return 31;
    case 11:
        return 30;
    case 12:
        return 31;
    default:
        return 0;
    }
}
bool isValidDate(int year, int month, int day)
{
    time_t currentTime = time(nullptr);

    tm* localTime = localtime(&currentTime);

    int currentYear = localTime -> tm_year + 1900;
    int currentMonth = localTime -> tm_mon + 1;

    if (year < 2000 || year > currentYear) return false;
    if (month < 1 || month > 12) return false;
    if (year == 2000 && month == 1 && day < 1) return false;
    if (year == currentYear && month == currentMonth && day < 1) return false;
    if (day < 1 || day > getLastDayOfCurrentMonth(year, month)) return false;
    if (year > currentYear || (year == currentYear && month > currentMonth)) return false;
    if (year >= currentYear && month >= currentMonth && day > getLastDayOfCurrentMonth(year, month)) return false;

    return true;
}
int exchangeDateStringToInt(const string &date)
{
    int year, month, day;
    char firstDash, secondDash;
    stringstream ss(date);
    ss >> year >> firstDash >> month >> secondDash >> day;

    if (!isValidDate(year, month, day)){
        cerr << "Invalid date format or invalid date!" << endl;
        return  -1;
    }

    stringstream formattedDate;
    formattedDate << year
                  << setw(2) << setfill('0') << month
                  << setw(2) << setfill('0') << day;

    return stoi(formattedDate.str());
}
void sortIncomes(vector <string> &incomes)
{
    sort(incomes.begin(), incomes.end());
}
void sortExpenses(vector <string> &expenses)
{
    sort(expenses.begin(), expenses.end());
}
void addIncomeOrExpense()
{
    CMarkup xmlIncomes, xmlExpenses;
    string date;
    vector <string> incomes, expenses;

    while (true) {
        cout << "Enter date of incomes (format YYYY-MM-DD, empty line to finish):" << endl;
        getline(cin, date);
        if (date.empty()) break;
        int modifiedTypeOfDate = exchangeDateStringToInt(date);
        if (modifiedTypeOfDate != -1) incomes.push_back(to_string(modifiedTypeOfDate));
    }
    sortIncomes(incomes);

    xmlIncomes.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    xmlIncomes.AddElem("incomes");
    for (string income : incomes) {
        xmlIncomes.AddChildElem("income", income);
    }
    xmlIncomes.Save("Incomes.xml");

    while (true) {
        cout <<  "Enter date of expenses (format YYYY-MM-DD, empty line to finish):" << endl;
        getline(cin, date);
        if (date.empty()) break;
        int modifiedTypeOfDate = exchangeDateStringToInt(date);
        if (modifiedTypeOfDate != -1) expenses.push_back(to_string(modifiedTypeOfDate));
    }
    sortExpenses(expenses);

    xmlExpenses.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    xmlExpenses.AddElem("incomes");
    for (string expense : expenses) {
        xmlExpenses.AddChildElem("expense", expense);
    }
    xmlExpenses.Save("Expenses.xml");
}
int main()
{
    addIncomeOrExpense();
}
