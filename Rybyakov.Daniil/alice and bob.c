#include <stdio.h>
#include <math.h>


//переменные
typedef long long int Money;  //копейки

int MONTH = 240;  // месяцы
double CREDITPERCENT = 0.07;  // процент по кредиту
double m_koef = 0.07 / 12;  // коэфф расчета платежа

Money CREDIT = 19 * 1000 * 1000 * 100;  // сумма кредита
Money CREDITPAYMENT;  //платеж по кредиту
Money FLAT = 20 * 1000 * 1000 * 100;  //стоимость квартиры


struct Person
{
	Money balance;  //кол-во денег после расходов на жизнь
	Money bank;  //счте в банке
	Money total;  //конечный результат
	Money salary;  
	Money rent;  //стоимость аренды
	double deposit;  //процент счета в банке
};

struct Person Alice;
struct Person Bob;

void initialization_Alice()
{
	Alice.balance = 0;
	Alice.bank = 1 * 1000 * 1000 * 100;
	Alice.total = 0;
	Alice.salary = 200 * 1000 * 100;
	Alice.rent = 30 * 1000 * 100;
	Alice.deposit = 0.09;
}


void initialization_Bob()
{
	Bob.balance = 0;
	Bob.bank = 0;
	Bob.total = 0;
	Bob.salary = 200 * 1000 * 100;
	Bob.rent = 0;
	Bob.deposit = 0.09;
}


void creditpay()  //расчет платежа по кредиту
{
	CREDITPAYMENT = CREDIT * ((m_koef * pow(1 + m_koef, MONTH)) / (pow(1 + m_koef, MONTH) - 1));  //платеж по кредиту
}


void Alice_free_mooney()
{
	Alice.balance = Alice.salary - Alice.rent;  // ежемесячный остаток денег
}


void Bob_free_mooney()
{
	Bob.balance = Bob.salary - CREDITPAYMENT;  //ежемесячный остаток денег
}

void count_Alice(int now_year, int now_month)  //расчет баланса алисы
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //условие увеличения ставки в банке
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //вычисление года
		{
			year += 1;
		}

		if ((year == now_year) && (i % 12 == now_month))  //Алиса теряет зарплату
		{
			Alice.balance = 0;
		}

		if (Alice.bank / deposit_bonus == 1)  //увеличение ставки
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Alice.deposit += 0.01;
		}

		if ((year % 10 == 0) && (i % 12 == 0))  //траты на зубного
		{
			Alice.bank -= 500 * 1000 * 100;
		}

		Alice.bank += Alice.bank * (Alice.deposit / 12);
		Alice.bank -= Alice.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
	}
}


void count_Bob(int now_year, int now_month)  //расчет баланса боба
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //условие увеличения ставки в банке
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //вычисление года
		{
			year += 1;
		}

		if (Bob.bank / deposit_bonus == 1)  //увеличения ставки в банке
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Bob.deposit += 0.01;
		}

		Bob.bank += Bob.bank * (Bob.deposit / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Bob.bank += Bob.balance;
	}
}


void count_Flat()  //расчет стоимости квартиры
{
	for (int i = 0; i <= MONTH; ++i)
	{
		FLAT += FLAT * (0.01 / 12);
	}
}


void final_Alice()  //финальный баланс алисы в рублях
{
	Alice.total = Alice.bank / 100;
}


void final_Bob()  //финальный баланс боба в рублях
{
	Bob.total = (Bob.bank + FLAT) / 100;
}


void result()  //вывод результата
{
	printf("%lld   %lld", Alice.total, Bob.total);
}


main()
{
	creditpay();
	initialization_Alice();
	initialization_Bob();
	Alice_free_mooney();
	Bob_free_mooney();
	count_Flat();
	count_Alice(15, 8);
	count_Bob(1, 3);
	final_Alice();
	final_Bob();
	result();
}