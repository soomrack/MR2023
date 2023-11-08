#include<stdio.h>
#include<math.h>


typedef long long int Money; 


Money Mortgage_payment = 147307 * 100;
Money Flat_mortgage = 0;
Money First_payment = 1000 * 1000 * 100;
Money Flat_cost;
Money Total_Bob_capital;


struct Person {
	Money bank_account;
	Money salary;
};


struct Person Alice;
struct Person Bob;


void Alice_initialization()
{
	Alice.bank_account = 1000 * 1000 * 100;
	Alice.salary = 200 * 1000 * 100;
}


void Bob_initialization()
{
	Bob.bank_account = 0;
	Bob.salary = 200 * 1000 * 100;
}


void print_Alice()
{
	printf(" Alice capital = %lld\n", Alice.bank_account);
}


void Alice_salary_income(const int year, const int month)
{
	if (year == 2025 && month == 3)
	{
		Alice.salary = 0;
	}
	if (year == 2025 && month == 4)
	{
		Alice.salary = 200 * 1000 * 100;
	}
	Alice.bank_account += Alice.salary;
}


void Alice_deposite_income(const int year, const int month)
{
	int bank_procent = 9;
	Alice.bank_account += (Money)(Alice.bank_account * (bank_procent / 100.0 / 12.0));
}


void Alice_arenda(const int year, const int month)
{
	Alice.bank_account -= 30000 * 100;
}


void Alice_spend_for_life(const int year, const int month)
{
	Alice.bank_account -= 17000 * 100;
}


void Alice_trip_to_Turkey(const int year, const int month)
{
	if (year == 2033 && month == 10)
	{
		Alice.bank_account -= 100000 * 100;
	}
}


void Alice_humster(const int year, const int month)
{
	Alice.bank_account -= 2000 * 100;
}


void print_Bob()
{
	printf(" Bob capital = %lld\n", Total_Bob_capital);
}


void Bob_salary_income(const int year, const int month)
{
	Bob.bank_account += Bob.salary - Mortgage_payment;
}


void Bob_deposite_income(const int year, const int month)
{
	int bank_procent = 9;
	Bob.bank_account += (Money)(Bob.bank_account * bank_procent / 100.0 / 12.0);
}


void Bob_mortgage_payment(const int year, const int month)
{
	Flat_mortgage += Mortgage_payment;
}
	

void Bob_arenda(const int year, const int month)
{
	Bob.bank_account -= 25000 * 100;
}


void Bob_spend_for_life(const int year, const int month)
{
	Bob.bank_account -= 20000 * 100;
}


void simulation()
{
	int month = 9;
	int year = 2023;


	while (!(year == 2053 && month == 5)) {


		Alice_deposite_income(year, month);
		Alice_salary_income(year, month);
		Alice_arenda(year, month);
		Alice_spend_for_life(year, month);
		Alice_trip_to_Turkey(year, month);
		Alice_humster(year, month);


		Bob_salary_income(year, month);
		Bob_mortgage_payment(year, month);
		Bob_arenda(year, month);
		Bob_deposite_income(year, month);
		Bob_spend_for_life(year, month);

		++month;
		if (month == 13) {
			++year;
			month = 1;
		}
	}

	Flat_cost = First_payment + Flat_mortgage;
	Total_Bob_capital = Bob.bank_account + Flat_cost;

}


int main()
{
	Alice_initialization();
	Bob_initialization();


	simulation();
	

	print_Alice();
	print_Bob();


	return 0;
}