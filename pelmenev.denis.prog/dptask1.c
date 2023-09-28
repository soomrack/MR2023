#include <stdio.h>
#include <math.h>


typedef long long int Money;  // копейки


struct Person
{
    Money capital;
    Money income;              // заработок
    Money life_spendings;      // траты на существование
    Money monthly_payment;     // траты на квартиру (проживание или погашение ипотеки)
    Money overpayment;         // переплата при покупке квартиры
};                             


// создание структур для Элис и Боба
struct Person Alice;
struct Person Bob;


const Money PRICE = 20 * 1000 * 1000 * 100;     // стоимость квартиры в копейках
const Money SALARY = 200 * 1000 * 100;          // зарплата каждого в копейках
const Money START_CAPITAL = 1000 * 1000 * 100;  // стартовый капитал каждого в копейках
const int YEARS = 20;                           
const double INFLATION = 0.07;                  // сотая процента инфляции в год 
double BANK_RATE = 0.09;                        // сотая годовой ставки в банке
const Money LIFE_SPENDINGS = 25 * 1000 * 100;   // траты на жизнь в копейках
const int START_MONTH = 9;                      // начальные временные условия
const int START_YEAR = 2023;
const int LAST_MONTH = 8;


void alice_init()
{
    Alice.income = SALARY;
    Alice.capital = START_CAPITAL;
    Alice.life_spendings = LIFE_SPENDINGS;
    Alice.monthly_payment = 40 * 1000 * 100;
    Alice.overpayment = PRICE * powf((1.0 + INFLATION), YEARS) - PRICE;
}


void alice_salary_income(const int year, const int month)
{
    if (month == 11) {
        return;
    };
    Alice.capital += Alice.income;
}


void alice_deposite_income(const int year, const int month)
{
    if (year == START_YEAR && month == START_MONTH) {
        return;
    };
    if (year == 2033 && month == 1) {
        BANK_RATE = 0.1;
    };
    Alice.capital = Alice.capital * (1.0 + BANK_RATE / 12.0);
}


void alice_life_spending(const int year, const int month)
{
    if (month == 12) {
        Alice.capital -= Alice.life_spendings * 0.5;
    };
    Alice.capital -= Alice.life_spendings;
}


void alice_rent_payment(const int year, const int month)
{
    Alice.capital -= Alice.monthly_payment;
}


void bob_init()
{
    Bob.income = SALARY;
    Bob.capital = 0;
    Bob.life_spendings = LIFE_SPENDINGS;
    Bob.monthly_payment = (PRICE - START_CAPITAL) * (BANK_RATE / 12.0) / (1 - powf((1 + BANK_RATE / 12.0), (1.0 - YEARS * 12.0)));
    Bob.overpayment = Bob.monthly_payment * 12 * YEARS - PRICE;
}


void bob_salary_income(const int year, const int month)
{
    if (month == 12) {
        Bob.capital += (Money)(Bob.income * 1.2);
    };
    Bob.capital += Bob.income;
}


void bob_deposite_income(const int year, const int month)
{
    if (year == 2033 && month == 1) {
        BANK_RATE = 0.1;
    };
    Bob.capital = Bob.capital * (1.0 + BANK_RATE / 12.0); 
}


void bob_life_spending(const int year, const int month)
{
    if (month == 12) {
        Bob.capital -= Bob.life_spendings * 0.5;
    };
    Bob.capital -= Bob.life_spendings;
}


void bob_mortgage_payment(const int year, const int month)
{
    Bob.capital -= Bob.monthly_payment;
}


void goods_inflation(const int year, const int month)
{
    if (month % 3 == 0 && month > 2) {
        Alice.life_spendings += Alice.life_spendings * INFLATION / 4.0;
        Bob.life_spendings += Bob.life_spendings * INFLATION / 4.0;
    };
}


void real_estate_inflation(const int year, const int month)
{
    if (month == 12) {
        Alice.monthly_payment = Alice.monthly_payment * (1.0 + INFLATION / 2.0);
    };
}


void salary_inflation(const int year, const int month)
{
    if (month == 12) {
        Alice.income = Alice.income * (1.0 + INFLATION / 2.0);
        Bob.income = Bob.income * (1.0 + INFLATION / 2.0);
    };
}


void simulation()
{
    int month = START_MONTH;
    int year = START_YEAR;
    int last_year = START_YEAR + YEARS;

    while(!(year == last_year && month == LAST_MONTH)) {

        alice_deposite_income(year, month);
        alice_salary_income(year, month);
        alice_life_spending(year, month);
        alice_rent_payment(year, month);

        bob_deposite_income(year, month);
        bob_salary_income(year, month);
        bob_life_spending(year, month);
        bob_mortgage_payment(year, month);

        goods_inflation(year, month);
        salary_inflation(year, month);
        real_estate_inflation(year, month);

        month++;
        if (month > 12) {
            year++;
            month -= 12;
            printf("Happy New Year \n");  // DEBUG
        };
        
    }
}


void print_persons()
{
    printf("A. Capital: %lld\t", Alice.capital);
    printf("A. Income: %lld\t", Alice.income);
    printf("A. Life spendings: %lld\t", Alice.life_spendings); 
    printf("A. Monthly payment: %lld\t", Alice.monthly_payment); 
    printf("A. Overpayment: %lld\n", Alice.overpayment);
    printf("B. Capital: %lld\t", Bob.capital); 
    printf("B. Income: %lld\t", Bob.income); 
    printf("B. Life spendings: %lld\t", Bob.life_spendings); 
    printf("B. Monthly payment: %lld\t", Bob.monthly_payment); 
    printf("B. Overpayment: %lld\n", Bob.overpayment);
}


int main() 
{
    alice_init();
    bob_init();

    simulation();

    print_persons();

    return 0;
}
