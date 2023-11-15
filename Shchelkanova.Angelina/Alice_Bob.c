#include <stdio.h>
#include <math.h>

typedef long long int money; //копейки

//объявление переменных, можно менять для изменения условий задачи
const money sum_start = 1 * 1000*1000 * 100; // начальный капитал в копейках
const money rent = 35 * 1000 * 100; // ежемесячная рента в копейках
const money price = 20 * 1000 * 1000 * 100; // стоимость квартиры в копейках
const money spending_life = 25 * 1000 * 100; //ежемесячные траты на жизнь в копейках
const double inflation = 0.07; // инфляция в год
const double bank_procent = 0.11; // годовая ставка по вкладу в банке
const int years = 20;

struct person {
	money bank_account; // счёт в банке
	money salary; // зарплата
	money spendings; //траты, включая непредвиденные обстоятельства
	money payment; //ежемесячная выплата по ипотеке, аренда квартиры
	money overpayment; //переплата за покупку квартиры(ипотеку)
};

struct person Alice;
struct person Bob;

void Alice_initializations()
{
	Alice.bank_account = sum_start;
	Alice.salary = 200 * 1000 * 100;
	Alice.spendings = spending_life;
	Alice.payment = rent;
	Alice.overpayment = price * powf((1.0 + inflation), years) - price;
}


void print_Alice()
{
		printf("Alice:\n");
		printf(" bank account = %lld\n", Alice.bank_account);
		printf(" overpayment = %lld\n", Alice.overpayment);
}


void Alice_salary_income(const int year, const int month)
{
	if (year == 2025 && month == 3) Alice.salary = 0;

	Alice.bank_account += Alice.salary;
	if (month == 12)
	{
		Alice.salary =(money) Alice.salary * (1.0 + inflation / 2.0);
}
}


void Alice_deposite_income(const int year, const int month)
{
	Alice.bank_account += (money)(Alice.bank_account * (bank_procent/ 12.0));
}


void Alice_spendings(const int year, const int month)
{
	if (month == 12) {
		Alice.bank_account -= Alice.spendings * 1.5;
		Alice.payment = Alice.payment * (1.0 + inflation / 2.0);
	}
	Alice.bank_account -= Alice.payment;
	Alice.bank_account -= Alice.spendings;
	if (month % 6 == 0 && month > 1)
	{
		Alice.spendings += Alice.spendings * inflation / 4.0;
	}
}


void Bob_initializations()
{
		Bob.bank_account = 0;
		Bob.salary = 200 * 1000 * 100;
		Bob.spendings = spending_life;
		Bob.payment = (price - sum_start) * (bank_procent / 12.0) / (1 - powf((1 + bank_procent / 12.0), (1.0 - years * 12.0)));
		Bob.overpayment = Bob.payment * 12 * years - price;
}


void print_Bob()
{
		printf("Bob:\n");
		printf(" bank account = %lld\n", Bob.bank_account);
		printf(" overpayment = %lld\n", Bob.overpayment);
}


void Bob_salary_income(int year,int month)
{
		Bob.bank_account += Bob.salary;
		if (month == 12)
		{
			Bob.salary = (money) Bob.salary * (1.0 + inflation / 2.0);
		}
}


void Bob_deposite_income(const int year, const int month)
{
	Bob.bank_account += (money)(Bob.bank_account * (bank_procent / 12.0));
}


void Bob_spendings(const int year, const int month)
{
	if (month==12)
	{
		Bob.bank_account -= Bob.spendings * 1.5;
	}
	if (month == 9 && year == 2023)
	{
		Bob.spendings=0;
	}
	Bob.bank_account -= Bob.payment;
	Bob.bank_account -= Bob.spendings;
	if (month % 6 == 0 && month > 1)
	{
		Bob.spendings += Bob.spendings * inflation / 4.0;
	}
}


void simulation()
{
		int month = 9;
		int year = 2023;

		while (year != 2053 && month != 8) {
			Alice_deposite_income(year, month);
			Alice_salary_income(year, month);
			Alice_spendings(year, month);
			//alice spend

			Bob_deposite_income(year, month);
			Bob_salary_income(year, month);
			Bob_spendings(year, month);

			++month;
			if (month == 13) {
				++year;
				month = 1;
			}
		}
}


int main()
{
	Alice_initializations();
	Bob_initializations();

	simulation();

	print_Alice();
	print_Bob();

	return 0;

}
