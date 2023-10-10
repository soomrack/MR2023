#include<stdio.h>
#include<math.h>


typedef long long int Money; // копейки


struct Person {
	Money bank_account;
	Money salary;
};


struct Person Alice;
struct Person Bob;


void Alice_init()
{
	Alice.bank_account = 1000 * 1000 * 100;
	Alice.salary = 200 * 1000 * 100;
}


void Bob_init()
{
	Bob.bank_account = 1000 * 1000 * 100;
	Bob.salary = 200 * 1000 * 100;
}


void print_Alice()
{
	printf("Alice:\n");
	printf(" bank account = %lld \n", Alice.bank_account);
}


void print_Bob()
{
	printf("Bob:\n");
	printf(" bank account = %lld \n", Bob.bank_account);
}


void Alice_salary_income(const int year, const int month)
{
	if (year == 2024 && month == 10) Alice.salary = 0;
	if (year == 2024 && month == 11) Alice.salary = 200 * 1000 * 100;

	Alice.bank_account += Alice.salary;
}


void Alice_deposite_income(const int year, const int month)
{
	int bank_pp = 9;
	Alice.bank_account += (Money)(Alice.bank_account * (bank_pp / 100.0 / 12.0));
}


void Alice_arenda(const int year, const int month)
{
	Alice.bank_account -= 35000 * 100;
}


void Bob_salary_income(const int year, const int month)
{
	Bob.bank_account += Bob.salary;
}


void Bob_deposite_income(const int year, const int month)
{
	int bank_pp = 9;
	Bob.bank_account += (Money)(Bob.bank_account * (bank_pp / 100.0 / 12.0));


void simulation()
{
	int month = 9;
	int year = 2023;

	while (year != 2053 && month != 2) {

		Alice_deposite_income(year, month);
		Alice_salary_income(year, month);
		Alice_arenda(year, month);
//		Alice_spend_for_life(year, month);
//      Alice_trip_to_Turkey(year, month);
//      Alice_humster(year, month);

		Bob_salary_income(year, month);

		++month;
			if(month == 13) {
				++year;
				month = 1;
		}
	}
}


void print_Alice_results()
{
	printf("Alice:\n");
	printf(" bank account = %lld \n", Alice.bank_account);
}


void print_Bob_results()
{
	printf("Bob:\n");
	printf(" bank account = %lld \n", Bob.bank_account);
}


int main()
{
	Alice_init();
	Bob_init();

	print_Alice();
	print_Bob();

	simulation();

	print_Alice_results()
	print_Bob_results()

	return 0;
}