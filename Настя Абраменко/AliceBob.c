#include <stdio.h>
#include <math.h>


typedef long long int money;  // деньги - копейки


struct Person                  // структуры для Алисы и Боба
{
    money capital;             // накопленный капитал
    money income;              // заработок
    money life_spendings;      // траты на жизнь
    money payment_monthly;     // проживание в квартире или погашение ипотеки в течение месяца
};                             


struct Person Alice;
struct Person Bob;


const int START_MONTH = 9;                      // начальный месяц
const int START_YEAR = 2023;                    // начальный год
const int LAST_MONTH = 8;                       // конечный месяц
const money PRICE = 20 * 1000 * 1000 * 100;     // стоимость квартиры 
const money SALARY = 200 * 1000 * 100;          // зарплата Алисы и Боба
const money START_CAPITAL = 1000 * 1000 * 100;  // стартовый капитал Алисы, первоначальный взнос Боба
const int YEARS = 20;                           
const double INFLATION = 0.07;                  // инфляция в год 
double BANK_RATE = 0.09;                        // годовая ставка в банке
const money LIFE_SPENDINGS = 25 * 1000 * 100;   // обыкновенные траты на жизнь
const money HAMSTER = 500 * 1000;               // цена хомячка
const money DOG = 1000 * 1000;                  // цена собачки


void alice_init()                               // инициализация для Алисы
{
    Alice.income = SALARY;
    Alice.capital = START_CAPITAL;
    Alice.life_spendings = LIFE_SPENDINGS;
    Alice.payment_monthly = 40 * 1000 * 100;
}


void bob_init()                                 // инициализация для Боба
{
    Bob.income = SALARY;
    Bob.capital = 0;
    Bob.life_spendings = LIFE_SPENDINGS;
    Bob.payment_monthly = (PRICE - START_CAPITAL) * (BANK_RATE / 12.0) / (1 - powf((1 + BANK_RATE / 12.0), (1.0 - YEARS * 12.0)));
}


void alice_income(const int year, const int month)               // начисление зарплаты Алисе
{
    if (month == 11) {
        return;
    }
    Alice.capital += Alice.income;
    if (month == 12) {
        Alice.income = Alice.income * (1.0 + INFLATION / 2.0);
    }
}


void bob_income(const int year, const int month)                 // начисление зарплаты Бобу
{
    if (month == 12) {
        Bob.capital += (money)(Bob.income * 1.2);
    }
    Bob.capital += Bob.income;
    if (month == 12) {
        Bob.income = Bob.income * (1.0 + INFLATION / 2.0);
    }
}


void alice_deposite_income(const int year, const int month)             // процент на остаток в банке для Алисы
{
    if (year == START_YEAR && month == START_MONTH) {
        return;
    }
    if (year == 2033 && month == 1) {
        BANK_RATE = 0.1;
    }
    Alice.capital = Alice.capital * (1.0 + BANK_RATE / 12.0);
}


void bob_deposite_income(const int year, const int month)              // процент на остаток в банке для Боба
{
    if (year == 2033 && month == 1) {
        BANK_RATE = 0.1;
    }
    Bob.capital = Bob.capital * (1.0 + BANK_RATE / 12.0); 
}


void alice_life_spending(const int year, const int month)              // траты Алисы на существование
{
    if (month == 12) {
        Alice.capital -= Alice.life_spendings * 0.5;
    }
    Alice.capital -= Alice.life_spendings;
}


void bob_life_spending(const int year, const int month)                // траты Боба на существование
{
    if (month == 12) {
        Bob.capital -= Bob.life_spendings * 0.5;
    }
    Bob.capital -= Bob.life_spendings;
}


void alice_payment(const int year, const int month)              // ежемесячный платеж за съемную квартиру Алисы
{
    Alice.capital -= Alice.payment_monthly;
}


void bob_payment(const int year, const int month)            // ежемесячный платеж по ипотеке Боба
{
    Bob.capital -= Bob.payment_monthly;
}


void life_inflation(const int year, const int month)                 // влияние инфляции на размер обыкновенных трат для Алисы и Боба
{
    if (month % 3 == 0 && month > 2) {
        Alice.life_spendings += Alice.life_spendings * INFLATION / 4.0;
        Bob.life_spendings += Bob.life_spendings * INFLATION / 4.0;
    }
}


void estate_inflation(const int year, const int month)           // влияние инфляции на стоимость съемной квартиры Алисы
{
    if (month == 12) {
        Alice.payment_monthly = Alice.payment_monthly * (1.0 + INFLATION / 2.0);
    }
}


void alice_animal(const int year, const int month)                   // покупка хомячка и собачки Алисой
{
    
    if (year == 2035 && month == 6) {
        Alice.capital -= HAMSTER;
    }
    if (year == 2040 && month == 3) {
        Alice.capital -= DOG;
    }
}


void simulation()
{
    int month = START_MONTH;
    int year = START_YEAR;
    int last_year = START_YEAR + YEARS;

    while(!(year == last_year && month == LAST_MONTH)) {

        alice_deposite_income(year, month);
        alice_income(year, month);
        alice_life_spending(year, month);
        alice_payment(year, month);

        bob_deposite_income(year, month);
        bob_income(year, month);
        bob_life_spending(year, month);
        bob_payment(year, month);

        life_inflation(year, month);
        estate_inflation(year, month);
        alice_animal(year, month);
        
        month++;
        if (month > 12) {
            year++;
            month = 1;
        }
        
    }
}


void print()
{
    double alice_capital = Alice.capital;
    double bob_capital = Bob.capital;
    alice_capital /= 100;
    bob_capital /= 100;
    printf("Alice Capital: %f \n", (alice_capital));
    printf("Bob Capital: %f \n", (bob_capital)); 
}


int main() 
{
    alice_init();
    bob_init();

    simulation();

    print();

    return 0;
}