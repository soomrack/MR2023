#include <stdio.h>
#include <math.h>


//переменные
typedef long long int Money; //копейки

int time = 240; // мес€цы
double creditpercent = 0.07; // процент по кредиту
double m = 0.07 / 12; // коэфф расчета платежа
double deposit = 0.09; //проццент в банке

Money salary = 200 * 1000 * 100; 
Money rent = 30 * 1000 * 100; //ареннда квартиры
Money credit = 19 * 1000 * 1000 * 100; // сумма кредита
Money creditpayment; //платеж по кредиту
Money flat = 20 * 1000 * 1000 * 100; //стоимость квартиры

struct Person {
	Money balance;
	Money bank;
	Money total;
};

struct Person Alice = {.bank = 1 * 1000 * 1000 * 100, .balance = 0.0};
struct Person Bob = {.bank = 0.0, .balance = 0.0 };

main() {
	Alice.balance = salary - rent; // ежемес€чный остаток денег
	creditpayment = credit * ((m * pow(1 + m, time)) / (pow(1 + m, time) - 1)); //платеж по кредиту
	Bob.balance = salary - creditpayment; //ежемес€чный остаток денег
	Bob.bank = Bob.balance;

	for (int i = 1; i <= time; ++i) {
		Alice.bank += (Alice.bank * (deposit / 12));
		Bob.bank += (Bob.bank * (deposit / 12));
		Alice.bank -= Alice.bank * (0.07 / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
		Bob.bank += Bob.balance;
		flat += flat * (0.01 / 12);
	}

	Alice.total = (Alice.bank) / 100;
	Bob.total = (Bob.total + flat) / 100;

	printf("%d   %d", Alice.total, Bob.total);

}