#include <stdio.h>
#include <math.h>


//переменные
typedef long long int Money;  //копейки

int MONTH = 240;  // мес€цы
double CREDITPERCENT = 0.07;  // процент по кредиту
double m_koef = 0.07 / 12;  // коэфф расчета платежа
double DEPOSIT = 0.09;  //проццент в банке

Money CREDIT = 19 * 1000 * 1000 * 100;  // сумма кредита
Money CREDITPAYMENT;  //платеж по кредиту
Money FLAT = 20 * 1000 * 1000 * 100;  //стоимость квартиры


struct Person 
{
	Money balance;
	Money bank;
	Money total;
	Money salary;
	Money rent;
};

struct Person Alice = { 0.0,  1 * 1000 * 1000 * 100,  0.0,  200 * 1000 * 100,  30 * 1000 * 100};
struct Person Bob = {0.0,  0.0,  0.0,  200 * 1000 * 100,  0.0};


Money creditpay(int credit, double m, int time) 
{
	int result;
	result = credit * ((m * pow(1 + m, time)) / (pow(1 + m, time) - 1));  //платеж по кредиту
	return result;
}


main()
{
	CREDITPAYMENT = creditpay(CREDIT, m_koef, MONTH);

	Alice.balance = Alice.salary - Alice.rent;  // ежемес€чный остаток денег
	Bob.balance = Bob.salary - CREDITPAYMENT;  //ежемес€чный остаток денег
	Bob.bank = Bob.balance;

		for (int i = 1; i <= MONTH; ++i)
		{
			Alice.bank += (Alice.bank * (DEPOSIT / 12));
			Bob.bank += (Bob.bank * (DEPOSIT / 12));
			Alice.bank -= Alice.bank * (0.07 / 12);
			Bob.bank -= Bob.bank * (0.07 / 12);
			Alice.bank += Alice.balance;
			Bob.bank += Bob.balance;
			FLAT += FLAT * (0.01 / 12);
		}

	Alice.total = Alice.bank / 100;
	Bob.total = (Bob.bank + FLAT) / 100;

	printf("%d   %d", Alice.total, Bob.total);
}