#include<stdio.h>
//#include<string.h>

typedef long long int Money; // kopeiki

struct Person
{
	Money bank_account;
	double bank_account_pp;
	Money salary;
	Money rent;
	Money expenses;
	Money credit;
	double credit_pp;
	double credit_term;
	//char name[6];
};

struct Person Alice;
struct Person Bob;

void Alice_init()
{
	Alice.bank_account = 1000 * 1000 * 100;
	Alice.bank_account_pp = 11;
	Alice.salary = 200 * 1000 * 100;
	Alice.rent = 30 * 1000 * 100;
	Alice.expenses = 40 * 1000 * 100;
	//strcpy_s(Alice.name, "Alice");
}

void Bob_init()
{
	Bob.bank_account = 0;
	Bob.bank_account_pp = 11;
	Bob.salary = 200 * 1000 * 100;
	Bob.credit_pp = 7;
	Bob.credit = 19 * 1000 * 1000 * 100;
	Bob.credit_term = 30 * 12;
	Bob.expenses = 40 * 1000 * 100;
	//strcpy_s(Bob.name, "Bob");
}

void print_person(const struct Person person)
{
	printf("bank_account = %lld\n", person.bank_account);
}

void Alice_deposite_income(const int year, const int month)
{
	Alice.bank_account += (Money)(Alice.bank_account * Alice.bank_account_pp / 100. / 12.);
}

void Bob_deposite_income(const int year, const int month)
{
	Bob.bank_account += (Money)(Bob.bank_account * Bob.bank_account_pp / 100. / 12.);
}

void Alice_salary_income(const int year, const int month)
{
	Alice.bank_account += Alice.salary;
	if (month == 12)
	{
		Alice.bank_account += Alice.salary;
	}
}

void Bob_salary_income(const int year, const int month)
{
	Bob.bank_account += Bob.salary;
	if (month == 12)
	{
		Bob.bank_account += Bob.salary;
	}
}

void Alice_rent(const int year, const int month)
{
	Alice.bank_account -= Alice.rent; 
}

//void Bob_mortgage_outcome(const int year, const int month)
{
	Bob.bank_account -= (Money)(Bob.credit * (Bob.credit_pp * (1 + Bob.credit_pp) ^ (Bob.credit_term)) / ((1 + Bob.credit_pp) ^ (Bob.credit_term) - 1));
}

void Alice_expenses(const int year, const int month)
{
	Alice.bank_account -= Alice.expenses;
}

void Bob_expenses(const int year, const int month)
{
	Bob.bank_account -= Bob.expenses;
}

void simulation()
{
	int month = 9;
	int year = 2023;
	while (year != 2053 && month != 9)
	{
		Alice_deposite_income(year, month);
		Alice_salary_income(year, month);
		Alice_rent(year, month);
		Alice_expenses(year, month);

		Bob_deposite_income(year, month);
		Bob_salary_income(year, month);
		Bob_expenses(year, month);
		//Bob_mortgage(year, month);

		++month;
		if (month == 13)
		{
			month = 1;
			++year;
		}
	}
}

int main()
{
	Alice_init();
	Bob_init();

	simulation();
	print_person(Alice);
	print_person(Bob);
	return 0;

}