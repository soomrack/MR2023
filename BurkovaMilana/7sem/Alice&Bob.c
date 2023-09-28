#include <stdio.h>
#include <string.h>


typedef long long int Money; // kopeiki


struct Hero {
    Money bank_account;
    Money salary;
    int monthly_expenses; // food, utilities
    double infl_procent;
    Money apartment_fee;
    Money apartment_price;
    int bank_pp;
    Money mortgage_payment;
    char name[6];
};

struct Hero Alice;
struct Hero Bob;


void Alice_init()
{
    Alice.bank_account = 1000 * 1000 * 100;
    Alice.salary = 200 * 1000 * 100;
    Alice.monthly_expenses = 60 * 1000 * 100; 
    Alice.infl_procent = 7.0; 
    Alice.apartment_fee = 30 * 1000 * 100;
    Alice.apartment_price = 0;
    Alice.bank_pp = 11.0;
    Alice.mortgage_payment = 0; 
    strcpy(Alice.name, "Alice");
}


void Bob_init()
{
    Bob.bank_account = 1000 * 1000 * 100;
    Bob.salary = 200 * 1000 * 100;
    Bob.monthly_expenses = 60 * 1000 * 100;
    Bob.infl_procent = 7.0;
    Bob.apartment_fee = 0;
    Bob.apartment_price = 20 * 1000 * 1000 * 100;
    Bob.bank_pp = 7.0;
    Bob.mortgage_payment = 126407047; 
    strcpy(Bob.name, "Bob");
}


void print_hero(const struct Hero hero)
{
    printf("$s:\n", hero.name);
    Money capital = hero.bank_account + hero.apartment_price;
    printf("  capital = %lld rub, %lld kop\n", (Money)(capital / 100), capital % 100);
    printf("\n");
}


void Alice_deposite_income(const int year, const int month)
{
    Alice.bank_account += (Money)(Alice.bank_account * Alice.bank_pp / 100.0 / 12.0);
}


void Alice_apartment_fee(const int year, const int month)
{
    Alice.bank_account -= Alice.apartment_fee;
}


void Alice_salary(const int year, const int month)
{
    if (month == 12) {
        Alice.salary = (Money)(Alice.salary * (Alice.infl_procent / 100));
    }

    Alice.bank_account += Alice.salary;
}


void Bob_deposite_income(const int year, const int month)
{
    Bob.bank_account += (Money)(Bob.bank_account * Bob.bank_pp / 100.0 / 12.0);
}


void Bob_mortgage_payment(const int year, const int month)
{
    Bob.bank_account -= Bob.mortgage_payment;
}


void Bob_salary(const int year, const int month)
{
    if (month == 12) {
       Bob.salary = (Money)(Bob.salary * (Bob.infl_procent / 100));
    }

    Bob.bank_account += Bob.salary;
}


void Bob_apartment_price(const int year, const int month)
{
    if (month == 12) {
        Bob.apartment_price = (Money)(Bob.apartment_price * (Bob.infl_procent / 100));
    }

}


void simulation()
{
    int month = 1;
    int year = 2023;
    while (!(year == 2053 && month == 1)) {
        Alice_deposite_income(year, month);
        Alice_apartment_fee(year, month);
        Alice_salary(year, month);

        Bob_deposite_income(year, month);
        Bob_salary(year, month);
        Bob_mortgage_payment(year, month);
        Bob_apartment_price(year, month);

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


int main() {
    Alice_init();
    Bob_init();

    simulation();

    print_hero(Alice);
    print_hero(Bob);
    return 0;
}
