﻿#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>


typedef long long int Money;  // деньги в копейках

struct Person {
	Money bank_account;
	int bank_account_pp;
	Money salary;
	Money rent;
	char name[6];
	double inflation_pp;
	Money house_price;
	Money mortgage_first_fee;
	Money expenses;  // прочие траты
	double mortgage_pp;
	Money mortgage_monthly_payment;
};

struct Person alice;
struct Person bob;


void alice_init()
{
	alice.bank_account = 1000 * 1000 * 100;
	alice.bank_account_pp = 11;
	alice.salary = 200 * 1000 * 100;
	alice.inflation_pp = 7;
	alice.house_price = 0;
	strcpy(alice.name, "Alice");
	alice.rent = 35 * 1000 * 100;
	alice.expenses = 10 * 1000 * 100;
}


void bob_init()
{
	bob.bank_account = 1000 * 1000 * 100;
	bob.bank_account_pp = 11;
	bob.salary = 200 * 1000 * 100;
	bob.inflation_pp = 7;
	bob.house_price = 20 * 1000 * 1000 * 100;
	strcpy(bob.name, "Bob");
	bob.mortgage_first_fee = 1000 * 1000 * 100;
	bob.expenses = 10 * 1000 * 100;
	bob.mortgage_pp = 7;
	bob.mortgage_monthly_payment = 0;
}


void alice_salary_income(const int year, const int month)
{
	alice.bank_account += alice.salary;
	if (month == 12) {
		alice.salary = (Money)(alice.salary * (alice.inflation_pp / 100.));
	}
}


void alice_deposite_income(const int year, const int month)
{
	alice.bank_account += (Money)(alice.bank_account * alice.bank_account_pp / 100.0 / 12.0);
}


void bob_deposite_income(const int year, const int month)
{
	bob.bank_account += (Money)(bob.bank_account * bob.bank_account_pp / 100.0 / 12.0);
}


void alice_rent(const int year, const int month)
{
	alice.bank_account -= alice.rent;
	if (month == 12) {
		alice.rent = (Money)(alice.rent * (alice.inflation_pp / 100.));
	}
}


void alice_expenses(const int year, const int month)
{
	alice.bank_account -= alice.expenses;
	if (month == 12) {
		alice.expenses = (Money)(alice.expenses * (alice.inflation_pp / 100.));
	}
}


void bob_mortgage_monthly_payment(const Money pay , const double pp , const int months) {
	// формула аннуитетного платежа по ипотеке
	Money mortgage_monthly_installment = ((pay) * (pp * 0.01 / 12) * pow((1.0 + (pp * 0.01 / 12)), (months))) /
		(pow((1.0 + (pp * 0.01 / 12)), (months)) - 1.0);

	bob.mortgage_monthly_payment = mortgage_monthly_installment;
	bob.bank_account -= bob.mortgage_first_fee;
}


void bob_expenses(const int year, const int month)
{
	bob.bank_account -= bob.expenses;
	if (month == 12) {
		bob.expenses = (Money)(bob.expenses * (bob.inflation_pp / 100.));
	}
}


void bob_salary_income(const int year, const int month)
{
	bob.bank_account += bob.salary;
	if (month == 12) {
		bob.salary = (Money)(bob.salary * (bob.inflation_pp / 100.));
	}
}


void bob_house_price(const int year, const int month)
{
	if (month == 12) {
		bob.house_price += (Money)(bob.house_price * (bob.inflation_pp / 100.));
	}
}


void simulation()
{
	int month = 9;
	int year = 2023;

	bob_mortgage_monthly_payment(bob.house_price - bob.mortgage_first_fee,
		bob.mortgage_pp, 30 * 12);


	while (!(year == 2053 && month == 9)) {

		alice_deposite_income(year, month);
		alice_salary_income(year, month);
		alice_rent(year, month);
		alice_expenses(year, month);  // прочие траты

		bob_deposite_income(year, month);
		bob_salary_income(year, month);
		bob_expenses(year, month);  // прочие траты
		bob_house_price(year, month);

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
}


void print_person(const struct Person person)
{
	printf("%s:\n", person.name);
	printf(" bank_account = %lld rub, %lld kop\n", (Money)(person.bank_account / 100.0), person.bank_account % 100);

	Money capital = person.bank_account + person.house_price;
	printf(" capital = %lld rub, %lld kop\n", (Money)(capital / 100.0), capital % 100);
	printf("\n");


}


int main()
{
	alice_init();
	bob_init();

	simulation();

	print_person(alice);
	print_person(bob);
	return 0;
}
