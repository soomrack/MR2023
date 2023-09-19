#include <stdio.h>
#include <math.h>


typedef long long int Money;  // рубли (для копеек не хватает места)


struct Person
{
    Money capital;
    Money income;              // заработок
    Money life_spendings;      // траты на существование
    Money monthly_payment;     // траты на квартиру (проживание или погашение ипотеки)
    Money overpayment;         // переплата при покупке квартиры
} Alice, Bob, Intermediary;    // создание структур для Элис и Боба, а также структуры-посредника


const Money PRICE = 20 * 1000 * 1000;     // стоимость квартиры в рублях
const Money SALARY = 200 * 1000;          // зарплата каждого в рублях
const Money START_CAPITAL = 1000 * 1000;  // стартовый капитал каждого в рублях
const int YEARS = 20;
const double INFLATION = 0.07;            // процент инфляции в год
const double BANK_RATE = 0.09;            // годовая ставка в банке
const Money LIFE_SPENDINGS = 25 * 1000;   // траты на жизнь в рублях


void preparation(char name)  // подготовка исходных данных для вычислений
{
    if (name == 'A') {
        Intermediary.monthly_payment = 40 * 1000;
        Intermediary.capital = START_CAPITAL;
        Intermediary.overpayment = PRICE * powf((1 + INFLATION), YEARS);
    } else if (name == 'B') {
        Intermediary.monthly_payment = (PRICE - START_CAPITAL) * (BANK_RATE / 12) / (1 - powf((1 + BANK_RATE / 12), (1 - YEARS * 12)));
        Intermediary.capital = 0;
        Intermediary.overpayment = Intermediary.monthly_payment * 12 * YEARS;
    } else {
        printf("Who is this? \n");
        return;
    };
    return;
}


void counting (int years)  // вычисления
{
    for (int k = 1; k <= years * 12; k++) {
        Intermediary.capital = (Intermediary.capital + Intermediary.income - Intermediary.monthly_payment 
        - Intermediary.life_spendings) * (1 + BANK_RATE / 12);
        if ((k % 3 == 0) && (k > 2)) {
            Intermediary.life_spendings = Intermediary.life_spendings * (1 + INFLATION / 4);
            if ((k % 12 == 0) && (k > 11)) {
                Intermediary.income = Intermediary.income * (1 + INFLATION / 2);
            };
        };
    };
}


void estimate (char name) // окончательное формирование структуры-посредника и присваивание её значений главным структурам
{
    Intermediary.income = SALARY;
    Intermediary.life_spendings = LIFE_SPENDINGS;
    
    counting(YEARS);

    if (name == 'A') {
        Intermediary.capital = Intermediary.capital - Intermediary.overpayment;
        Intermediary.overpayment = Intermediary.overpayment - PRICE;
    } else {
        Intermediary.overpayment = Intermediary.overpayment - PRICE + START_CAPITAL;
    };
    if (name == 'A') {
        Alice = Intermediary;
    } else if (name == 'B') {
        Bob = Intermediary;
    };
    return;
}


int main(void) 
{
    estimate(65);
    estimate(66);
    estimate(67);
    printf("A. Capital: %d\t", Alice.capital); printf("A. Income: %d\t", Alice.income); printf("A. Life spendings: "
    "%d\t", Alice.life_spendings); printf("A. Monthly payment: %d\t", Alice.monthly_payment); printf("A. Overpayment: " 
    "%d\n", Alice.overpayment);
    printf("B. Capital: %d\t", Bob.capital); printf("B. Income: %d\t", Bob.income); printf("B. Life spendings: "
    "%d\t", Bob.life_spendings); printf("B. Monthly payment: %d\t", Bob.monthly_payment); printf("B. Overpayment: " 
    "%d\n", Bob.overpayment);
    return 0;
}
