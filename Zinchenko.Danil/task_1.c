#include <stdio.h>
#include <math.h>
#include <string.h>

typedef long long int Money;


const double inflation_pp = 7;


struct Person
{
	Money bank_account;
	Money salary;
	Money house;
	Money ipoteka_pay;
	Money perv_vznos;
	Money traty;
	Money house_bills;
	short int srok;
	double bank_account_pp;
	char name[6];
};


struct Person alice;
struct Person bob;


void bob_init()
{
	bob.bank_account = 0;
	bob.salary = 200 * 1000 * 100;
	bob.house = 20 * 1000 * 1000 * 100;
	bob.perv_vznos = 1000 * 1000 * 100;
	bob.srok = 30 * 12;
	bob.bank_account_pp = 11.0;
	bob.traty = 50 * 1000 * 100;
	strcpy(bob.name, "Bob");
	bob.house_bills = 0; //monthly_ipoteka_pay_bob(7.0);
};


void alice_init()
{
	alice.bank_account = 1000 * 1000 * 100;
	alice.salary = 200 * 1000 * 100;
	alice.house = 0;
	alice.perv_vznos = 0;
	alice.bank_account_pp = 11.0;
	alice.traty = 50 * 1000 * 100;
	alice.house_bills = 30 * 1000 * 100;
	strcpy(alice.name, "Alice");
};


void alice_deposite_income()
{
	alice.bank_account += (Money)(alice.bank_account * alice.bank_account_pp / 100.0 / 12.0);
};


Money alice_salary(const int year, const int month)
{
	if (month == 12) alice.salary += (Money)(alice.salary * inflation_pp / 100);
	if (month != 3) alice.bank_account += alice.salary;
};


void alice_house_bills()
{
	alice.bank_account -= alice.house_bills;
	alice.house_bills += (Money)(alice.house_bills * inflation_pp / 100 / 12);
};


void alice_traty() // potrebitelskie traty Alice
{
	alice.bank_account -= alice.traty;
	alice.traty += (Money)(alice.traty * inflation_pp / 100 / 12);
};


void bob_traty() // potrebitelskie traty Boba
{
	bob.bank_account -= bob.traty;
	bob.traty += (Money)(bob.traty * inflation_pp / 100 / 12);

};


void bob_house_nalog (double procent_naloga, int month)
{
	if (month == 8) bob.bank_account -= (Money)(bob.house * procent_naloga / 100 );
};

void monthly_ipoteka_pay_bob (double procent_ipoteki)
{
	double monthly_pp = procent_ipoteki / 12.0;
	Money house_price = bob.house - bob.perv_vznos;

	bob.house_bills = (double)house_price *
		((monthly_pp / 100.0) * (powf(1.0 + (monthly_pp / 100.0), (double)bob.srok))
			/ (powf(1.0 + (monthly_pp / 100.0), (double)bob.srok) - 1.0));
};


Money bob_salary(const int year, const int month)
{
	if (!(month >= 4 && month <= 6 && year == 2030)) bob.bank_account += bob.salary;
	if (month == 12) bob.salary += (Money)(bob.salary * inflation_pp / 100);
};


void bob_deposite_income()
{
	bob.bank_account += (Money)(bob.bank_account * bob.bank_account_pp / 100.0 / 12.0);
};


void bob_house_cost(int month)
{
	if (month == 12) bob.house += (Money)(bob.house * (inflation_pp / 100));
};


void bob_house_bills()
{
	bob.bank_account -= bob.house_bills;

};


void simulation(int month, int year)
{

	bob.bank_account = 0;
	monthly_ipoteka_pay_bob(7.0);

	while (!(year == 2053 && month == 9)) {
		alice_salary(year, month);
		alice_house_bills();
		alice_traty();
		alice_deposite_income();

		
		bob_salary(year, month);
		bob_house_bills();
		bob_traty();
		bob_house_nalog(0.1, month);
		bob_deposite_income();
		bob_house_cost(month);
		++month;

		if (month == 13) {
			month = 1;
			++year;
		}
	}
	bob.bank_account += bob.house;
};


void print_person(const struct Person person)
{
	printf("%s:\n", person.name);
	printf("  bank_account = %lld rub\n", (Money)(person.bank_account / 100));
};


int main()
{
	alice_init();
	bob_init();

	simulation(9, 2023);

	print_person(bob);
	print_person(alice);

	return 0;
}
