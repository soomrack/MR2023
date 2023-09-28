#include <stdio.h>
#include <math.h>
typedef long long int Money;  // kopeiki


struct Person
{
	Money capital;
	int bank_pp;
	Money salary;
	Money traty;  // eda, domashnie zhivontie, komunalka
	Money arenda;
	double inf_pp;
	Money house_price;
	char name[6];
	Money monthly_mortgage;
	double mortgage_pp;
	Money mortgage;
};


struct Person alice;
struct Person bob;


void alice_init()
{
	alice.capital = 1000 * 1000 * 100;
	alice.bank_pp = 11;
	alice.salary = 200 * 1000 * 100;
	alice.traty = 50 * 1000 * 100;
	alice.arenda = 35 * 1000 * 100;
	alice.inf_pp = 7.0;
	alice.house_price = 0;
	strcpy(alice.name, "Alice");
	alice.monthly_mortgage = 0;
	alice.mortgage_pp = 0;
	bob.mortgage = 0;
}


void bob_init()
{
	bob.capital = 0;
	bob.bank_pp = 11;
	bob.salary = 200 * 1000 * 100;
	bob.traty = 50 * 1000 * 100;
	bob.arenda = 0;
	bob.inf_pp = 7.0;
	bob.house_price = 20 * 1000 * 1000 * 100;
	strcpy(bob.name, "Bob's");
	bob.mortgage_pp = 7.0;
	bob.mortgage = 19 * 1000 * 1000 * 100;
}


void alice_capital_income(const int year, const int month)
{
	alice.capital += (Money)(alice.capital * alice.bank_pp / 100 / 12 );
}


void bob_capital_income(const int year, const int month)
{
	bob.capital += (Money)(bob.capital * bob.bank_pp / 100 / 12);
}


void alice_salary_income(const int year, const int month)
{
	if (month == 12) alice.salary += (Money)(alice.salary * alice.inf_pp / 100.0 );
	alice.capital += (alice.salary);
}


void bob_salary_income(const int year, const int month)
{
	if (month == 12) bob.salary += (Money)(bob.salary * bob.inf_pp / 100.0);
	if (year != 2030 && (month != 5 || month != 6)) bob.capital += (bob.salary);
}

// eda, domashnie zhivontie, komunalka
void alice_traty_loss(const int year, const int month) 
	alice.traty += (Money)(alice.traty * alice.inf_pp / 100.0 / 12.0);
	alice.capital -= (alice.traty);
}


// eda, domashnie zhivontie, komunalka
void bob_traty_loss(const int year, const int month) {
	bob.traty += (Money)(bob.traty * bob.inf_pp / 100.0 / 12.0);
	bob.capital -= (bob.traty);
}


void alice_arenda_loss(const int year, const int month)
{
	alice.arenda += (Money)(alice.arenda * alice.inf_pp / 100.0 / 12.0);
	alice.capital -= alice.arenda;
}


void bob_monthly_mortgage(const int year, const int month)
{
	double pp = bob.mortgage_pp / 100.0 / 12.0;
	bob.monthly_mortgage = (Money)(bob.mortgage * (pp 
		* (powf(1 + pp, 360.0)) /
		(powf(1 + pp, 360.0) - 1.0)));
	bob.capital -= bob.monthly_mortgage;
}


void bob_house_price(const int year, const int month)
{
	bob.house_price += (Money)(bob.house_price * bob.inf_pp / 100.0 / 12.0);
}


void simulation()
{
	int month = 9;
	int year = 2023;
	while (year != 2053 || month != 9) {
		alice_capital_income(year, month);
		alice_salary_income(year, month);
		alice_traty_loss(year, month);  // eda, domashnie zhivontie, komunalka
		alice_arenda_loss(year, month);
		
		bob_capital_income(year, month);
		bob_salary_income(year, month);
		bob_traty_loss(year, month);  // eda, domashnie zhivontie, komunalka
		bob_monthly_mortgage(year, month);
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
	printf(person.name);
	printf(" capital = %lld rub, %lld kop\n", (Money)((person.capital+person.house_price)/100), 
		(person.capital + person.house_price) % 100);
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