#include <stdio.h>
#include <math.h>

// Объявление переменных
typedef long long int Money;  // Для копеек

const int MONTH = 240;  // Количество месяцев
const double CREDITPERCENT = 0.07;  // Процент по кредиту
const double M_KOEF = 0.07 / 12;  // Коэффициент расчета платежа
const double DEPOSIT = 0.09;  // Процент по вкладу
const double LOAN = 0.07;  // Процент по кредиту

Money CREDIT = 19 * 1000 * 1000 * 100;  // Сумма кредита
Money CREDITPAYMENT;  // Платеж по кредиту
Money FLAT = 20 * 1000 * 1000 * 100;  // Стоимость квартиры

struct Person // Условия
{
    Money balance;
    Money bank;
    Money total;
    Money salary;
    Money rent;
};

struct Person Alice = { 0, 1 * 1000 * 100 * 100, 0, 200 * 1000 * 100, 30 * 1000 * 100 };
struct Person Bob = { 0, 0, 0, 200 * 1000 * 100, 0 };

Money creditpay()  // Расчет платежа по кредиту
{
    int result;
    result = CREDIT * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // Платеж по кредиту
    return result;
}

int countBob()
{
    Bob.bank = 0; // Инициализируем банковский счет Bob
    for (int i = 0; i <= MONTH; ++i)
    {
        Bob.bank += Bob.bank * (DEPOSIT / 12);
        Bob.bank -= Bob.bank * (LOAN / 12);
        Bob.bank += Bob.balance;
    }
    return Bob.bank;
}

int countAlice()  // Расчет баланса Алисы
{
    for (int i = 0; i <= MONTH; ++i)
    {
        Alice.bank += Alice.bank * (DEPOSIT / 12);
        Alice.bank -= Alice.bank * (LOAN / 12);
        Alice.bank += Alice.balance;
    }
    return Alice.bank;
}

int countFlat()  // Расчет стоимости квартиры
{
    for (int i = 0; i <= MONTH; ++i)
    {
        FLAT += FLAT * (0.01 / 12);
    }
    return FLAT;
}

int main()
{
    CREDITPAYMENT = creditpay();

    Alice.balance = Alice.salary - Alice.rent;  // Ежемесячный остаток денег
    Bob.balance = Bob.salary - CREDITPAYMENT;  // Ежемесячный остаток денег

    Alice.total = countAlice() / 100;
    Bob.total = (countBob() + countFlat()) / 100;

    printf("%lld   %lld", Alice.total, Bob.total);
    return 0;
}
