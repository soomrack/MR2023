#include <stdio.h>
#include <math.h>


//переменные
typedef long long int Money;  // копейки

int YEARS = 0;
int MONTH = 240;  // месяцы
int FLAT_TAX = 0.05;
double M_KOEF = 0.07 / 12;  // коэфф расчета платежа

Money MORTAGE = 19 * 1000 * 1000 * 100;  // сумма кредита
Money MORTAGE_PAYMENT;  // платеж по кредиту
Money FLAT = 20 * 1000 * 1000 * 100;  // стоимость квартиры
Money DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;  // условие увеличения ставки в банке

struct Person{
    Money balance;  // кол-во денег после расходов на жизнь
    Money bank;  // счте в банке
    Money capital;  // конечный результат
    Money salary;  
    Money rent;  // стоимость аренды
    Money spending;
    double deposit;  // процент счета в банке
};

struct Person Alice;
struct Person Bob;

void initialization_Alice()
{
    Alice.bank = 1 * 1000 * 1000 * 100;
    Alice.capital = 0;
    Alice.salary = 200 * 1000 * 100;
    Alice.rent = 30 * 1000 * 100;
    Alice.deposit = 0.09;
    Alice.spending = 15 * 1000 * 100;
}


void initialization_Bob()
{
    Bob.bank = 0;
    Bob.capital = 0;
    Bob.salary = 200 * 1000 * 100;
    Bob.rent = 0;
    Bob.deposit = 0.09;
    Bob.spending = 15 * 1000 * 100;
}


void MORTAGE_pay()  // расчет платежа по кредиту
{
    MORTAGE_PAYMENT = MORTAGE * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // платеж по кредиту
}


void years_count(int input)  // счетчик лет
{
    if (input % 12 == 0) {
        YEARS += 1;
    }
}


void Alice_loses_salary(int condition_year, int condition_month, int now_month)
{
    if ((YEARS == condition_year) && (now_month % 12 == condition_month)) {  // Алиса теряет зарплату
        Alice.salary = 0;
    }
    else {
        Alice.salary = 200 * 1000 * 100;
    }
}


void deposit_bonus() 
{
    
    if (Alice.bank / DEPOSIT_BONUS == 1) {  // увеличение ставки
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Alice.deposit += 0.01;
    }
    if (Bob.bank / DEPOSIT_BONUS == 1) {  // увеличения ставки в банке
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Bob.deposit += 0.01;
    }
}


void dentist(month)
{
    if ((YEARS % 10 == 0) && (month % 12 == 0)) {  // траты на зубного
        Alice.bank -= 500 * 1000 * 100;
    }
}


void flat_tax(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) { 
        Bob.bank -= FLAT*FLAT_TAX;
    }
}


Alice_spend_money(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) {
        Alice.spending += Alice.spending * 0.03;
    }
}


Bob_spend_money(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) {
        Bob.spending += Bob.spending * 0.03;
    }
}


void count_Alice(int condition_year, int condition_month)  // расчет баланса алисы
{
    int month;
    YEARS = 0;
    DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;

    for (month = 0; month<= MONTH; ++month){

        years_count(month);
        Alice_loses_salary(condition_year, condition_month, month);
        deposit_bonus();
        dentist(month);
        Alice_spend_money(month);

        Alice.bank += Alice.salary;
        Alice.bank -= Alice.spending - Alice.rent;
        Alice.bank += Alice.bank * (Alice.deposit / 12);
        Alice.bank -= Alice.bank * (0.07 / 12);
        Alice.bank += Alice.balance;
    }
}


void count_Bob(int condition_year, int condition_month)  // расчет баланса боба
{
    YEARS = 0;
    DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;
    int month;
   
    for (month = 0;month<= MONTH; ++month){
        years_count(month);
        deposit_bonus();
        flat_tax(month);
        Bob_spend_money(month);

        Bob.bank += Bob.salary;
        Bob.bank -= Bob.spending - MORTAGE_PAYMENT;
        Bob.bank += Bob.bank * (Bob.deposit / 12);
        Bob.bank -= Bob.bank * (0.07 / 12);
        FLAT += FLAT * (0.01 / 12);
    }

}


void final_Alice()  // финальный баланс алисы в рублях
{
    Alice.capital = Alice.bank / 100;
}


void final_Bob()  // финальный баланс боба в рублях
{
    Bob.capital = (Bob.bank + FLAT) / 100;
}


void result()  // вывод результата
{
    printf("%lld   %lld", Alice.capital, Bob.capital);
}


main()
{
    MORTAGE_pay();
    initialization_Alice();
    initialization_Bob();
    count_Alice(1, 8);
    count_Bob(1, 3);
    final_Alice();
    final_Bob();
    result();
}