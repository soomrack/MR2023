#include <stdio.h>
#include <string.h>
#include <math.h>



typedef long long int Money;


struct Person {
    Money bank_account;
    char name[6];
    double bank_account_pp;
    Money salary;
    Money rent;
    Money wastes;
    double inflation_pp;
    Money house_repair;
    Money payment_mortgage;
    Money house_price;
    double house_tax;
};


struct Person Alice;
struct Person Bob;


void Alice_start()
{
    Alice.bank_account = 1000 * 1000 * 100;
    strcpy_s(Alice.name, sizeof(Alice.name), "Alice");
    Alice.bank_account_pp = 0.11;
    Alice.salary = 200 * 1000 * 100;
    Alice.rent = 30000 * 100;
    Alice.wastes = 15000 * 100;
    Alice.inflation_pp = 6.0;
    Alice.house_repair = 0;
    Alice.payment_mortgage = 0;
    Alice.house_price = 0;
    Alice.house_tax = 0.0;
}


void Bob_start()
{
    Bob.bank_account = 1000 * 1000 * 100;
    strcpy_s(Bob.name, sizeof(Bob.name), "Bob");
    Bob.bank_account_pp = 0.11;
    Bob.salary = 200 * 1000 * 100;
    Bob.rent = 0;
    Bob.wastes = 15000 * 100;
    Bob.inflation_pp = 6.0;
    Bob.house_repair = 20 * 1000 * 100;
    Bob.payment_mortgage = 160000 * 100;
    Bob.house_price = 20 * 1000 * 1000 * 100;
    Bob.house_tax = 0.01;
}


void Alice_deposite_income(const int year, const int month)
{
    Alice.bank_account += (Money)(Alice.bank_account * Alice.bank_account_pp / 12.0);
}


void Alice_salary_income(const int year, const int month)
{
    Alice.bank_account += Alice.salary;
    if (month == 1) Alice.salary += (Money)(Alice.salary * Alice.inflation_pp / 100.0);
}


void Bob_deposite_income(const int year, const int month)
{
    Bob.bank_account += (Money)(Bob.bank_account * Bob.bank_account_pp / 12.0);
}


void Bob_salary_income(const int year, const int month)
{
    Bob.bank_account += Bob.salary;
    if (month == 1) Bob.salary += (Money)(Bob.salary * Bob.inflation_pp / 100.0);
}


void Alice_rent(const int year, const int month)
{
    Alice.bank_account -= Alice.rent;
    if (month == 1) Alice.rent += (Money)(Alice.rent * Alice.inflation_pp / 100.0);
}


void Bob_mortgage(const int year, const int month)
{
    Bob.bank_account -= Bob.payment_mortgage;
}


void Alice_wastes(const int year, const int month)
{
    Alice.bank_account -= Alice.wastes;
    if (month == 1) Alice.wastes += (Money)(Alice.wastes * Alice.inflation_pp / 100.0);
}


void Bob_wastes(const int year, const int month)
{
    Bob.bank_account -= Bob.wastes;
    if (month == 1) Bob.wastes += (Money)(Bob.wastes * Bob.inflation_pp / 100.0);
}


void Bob_house_repair(const int year, const int month)
{
    if (year == 2023) Bob.bank_account -= Bob.house_repair;
    if (month == 1) Bob.house_repair += (Money)(Bob.house_repair * Bob.inflation_pp / 100.0);
}


void Bob_inflation_house(const int year, const int month)
{
    if (month == 1) Bob.house_price += (Money)(Bob.house_price * Bob.inflation_pp / 100.0);
}


void bob_house_tax(const int year, const int month)
{
    if (month == 1) Bob.bank_account -= (Money)(Bob.house_price * Bob.house_tax);
}


void simulation()
{
    int month = 9;
    int year = 2023;
    while (!(year == 2053 && month == 9)) {
        Alice_deposite_income(year, month);
        Alice_salary_income(year, month);
        Alice_rent(year, month);
        Alice_wastes(year, month);
        Bob_deposite_income(year, month);
        Bob_salary_income(year, month);
        Bob_house_repair(year, month);
        Bob_mortgage(year, month);
        Bob_wastes(year, month);
        Bob_inflation_house(year, month);
        bob_house_tax(year, month);
        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


void print_person(const struct Person person)
{
    printf("%s\n", person.name);
    printf(" bank account = %lld rub.\n", (Money)(person.bank_account / 100));
    Money capital = person.bank_account + person.house_price;
    printf(" capital = %lld rub.\n", (Money)(capital / 100));
}


int main()
{
    Alice_start();
    Bob_start();
    simulation();
    print_person(Alice);
    print_person(Bob);
    return 0;
}
