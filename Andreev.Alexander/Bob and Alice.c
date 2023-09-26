#include <stdio.h>


//переменные
typedef long long int Money;  //копейки

const int MONTH = 240;  // мес€цы
const double CREDITPERCENT = 0.07;  // процент по кредиту
const double m_koef = 0.07 / 12;  // коэфф расчета платежа
const double DEPOSIT = 0.09;  //проццент в банке

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

struct Person Alice = { 0,  1 * 1000 * 1000 * 100,  0,  200 * 1000 * 100,  30 * 1000 * 100 };
struct Person Bob = { 0,  0,  0,  200 * 1000 * 100,  0 };


Money creditpay()  //расчет платежа по кредиту
{
	int result;
	result = CREDIT * ((m_koef * pow(1 + m_koef, MONTH)) / (pow(1 + m_koef, MONTH) - 1));  //платеж по кредиту
	return result;
}


int countAlice()  //расчет баланса алисы
{
	for (int i = 0; i <= MONTH; ++i);
	{
		Alice.bank += Alice.bank * (DEPOSIT / 12);
		Alice.bank -= Alice.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
	}
	return Alice.bank;
}


int countBob()  //расчет баланса боба
{
	for (int i = 0; i <= MONTH; ++i);
	{
		Bob.bank += Bob.bank * (DEPOSIT / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Bob.bank += Bob.balance;
	}
	return Bob.bank;
}


int countFlat()  //расчет стоимости квартиры
{
	for (int i = 0; i <= MONTH; ++i);
	{
		FLAT += FLAT * (0.01 / 12);
	}
	return FLAT;
}


main()
{
	CREDITPAYMENT = creditpay();

	Alice.balance = Alice.salary - Alice.rent;  // ежемес€чный остаток денег
	Bob.balance = Bob.salary - CREDITPAYMENT;  //ежемес€чный остаток денег

	Alice.total = countAlice() / 100;
	Bob.total = (countBob() + countFlat()) / 100;

	printf("%d   %d", Alice.total, Bob.total);
}
