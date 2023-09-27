#include <stdio.h>
#include <string.h>


typedef long long int Money;


struct Hero {
    Money start_capital;
    Money income;
    int monthly_expenses;
    double infl_procent;
    Money apartment_fee;
    Money apartment_price;
    int bank_pp;
    Money monthly_installment;
    char name[6];
};

struct Hero Alice;
struct Hero Bob;


void Alice_init()
{
    Alice.start_capital = 1000 * 1000 * 100;
    Alice.income = 200 * 1000 * 100;
    Alice.monthly_expenses = 90 * 1000 * 100;
    Alice.infl_procent = 7.0; 
    Alice.apartment_fee = 30 * 1000 * 100;
    Alice.apartment_price = 0;
    Alice.bank_pp = 11.0;
    Alice.monthly_installment = 0;
    strcpy(Alice.name, "Alice");
}


void Bob_init()
{
    Bob.start_capital = 1000 * 1000 * 100;
    Bob.income = 200 * 1000 * 100;
    Bob.monthly_expenses = 60 * 1000 * 100;
    Bob.infl_procent = 7.0;
    Bob.apartment_fee = 0;
    Bob.apartment_price = 20 * 1000 * 1000 * 100;
    Bob.bank_pp = 7.0;
    Bob.monthly_installment = 126407047; 
    strcpy(Bob.name, "Bob");
}


void print_hero(const struct Hero hero)
{
    printf("$s:\n", hero.name);
    Money capital = hero.start_capital + hero.apartment_price;
    printf("  capital = %lld rub, %lld kop\n", (Money)(capital / 100), capital % 100);
    printf("\n");
}

void Alice_deposite_income(const int year, const int month)
{
    Alice.start_capital += (Money)(Alice.start_capital * Alice.bank_pp / 100.0 / 12.0);
}


void Alice_apartment_fee(const int year, const int month)
{
    Alice.start_capital -= Alice.apartment_fee;
}


void Alice_income(const int year, const int month)
{
    if (month == 12) {
        Alice.income = (Money)(Alice.income * (Alice.infl_procent / 100));
    }

    Alice.start_capital += Alice.income;
}


void Bob_deposite_income(const int year, const int month)
{
    Bob.start_capital += (Money)(Bob.start_capital * Bob.bank_pp / 100.0 / 12.0);
}

void Bob_mortgage_repayment(const int year, const int month)
{
    Bob.start_capital -= Bob.monthly_installment;
}

void Bob_income(const int year, const int month)
{
    if (month == 12) {
       Bob.income = (Money)(Bob.income * (Bob.infl_procent / 100));
    }

    Bob.start_capital += Bob.income;
}


void total()
{
    int month = 1;
    int year = 2023;
    while (year != 2053 && month != 1) {
        Alice_deposite_income(year, month);
        Alice_apartment_fee(year, month);
        Alice_income(year, month);

        Bob_deposite_income(year, month);
        Bob_income(year, month);
        Bob_mortgage_repayment(year, month);

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
    total();
    print_hero(Alice);
    print_hero(Bob);
    return 0;
}