#include <stdio.h>  
#include <string.h>
#include <math.h>

typedef long long int Money; //  kopeiki


struct Person
{
	Money bank_account; 
	int bank_account_pp;  
	Money salary;  
	Money rent;  
	char name[6];
	double inflation_pp;  // Procent inflation
	double ipoteka_pp;  // Procent ipoteka
	Money house_price;  
	Money rashod;  // food, taxi, hamster, pizza, ...
	Money plata_ipoteka;
};

struct Person alice;
struct Person bob;

void alice_init()
{
	alice.bank_account = 1000 * 1000 * 100;
	alice.bank_account_pp = 11;
	alice.salary = 200 * 1000 * 100;
	alice.rent = 35 * 1000 * 100;
	strcpy_s(alice.name, sizeof(alice.name), "Alice");
	alice.inflation_pp = 7.0;
	alice.ipoteka_pp = 0;
	alice.house_price = 0;
	alice.rashod = 30 * 1000 * 100;
	alice.plata_ipoteka = 0;
}

void bob_init()
{
	bob.bank_account = 1000 * 1000 * 100;
	bob.bank_account_pp = 11;
	bob.salary = 200 * 1000 * 100;
	bob.rent = 0;
	strcpy_s(bob.name, sizeof(bob.name), "Bob");
	bob.inflation_pp = 7.0;
	bob.ipoteka_pp = 7.0;
	bob.house_price = 20 * 1000 * 1000 * 100;
	bob.rashod = 30 * 1000 * 100;
	bob.plata_ipoteka = 0;
}



void alice_deposite_income(const int year, const int month)
{
	alice.bank_account += (Money)(alice.bank_account * alice.bank_account_pp / 100.0 / 12.0);
}


void bob_deposite_income(const int year, const int month)
{
	bob.bank_account += (Money)(bob.bank_account * bob.bank_account_pp / 100.0 / 12.0);
}



void alice_salary_income(const int year, const int month) 
{
	if (year == 2024 && month == 3) alice.salary = 0;
	if(year == 2024 && month == 4) alice.salary = 200*1000*100;

	alice.bank_account += alice.salary;
	if (month == 12) alice.bank_account += alice.salary; // 13-я зарплата
}


void bob_salary_income(const int year, const int month)
{
	bob.bank_account += bob.salary;
}



void alice_rent(const int year, const int month)
{
	alice.bank_account -= alice.rent;
}


void bob_ipoteka(const int year, const int month)
{
	int srok = 30;
	Money vznos = bob.bank_account;
	Money sum = bob.house_price - vznos;
	
	bob.bank_account -= vznos;
	double rate = (bob.inflation_pp / 100.0) / 12.0;  // Mesyachnaya stavka
	int term = srok * 12;   // Srok kredita in month
	double result = pow((1.0 + rate), (double)term);  // plata po ipoteke po formule annuitetnogo plateja
	double plata = (sum) * ((rate * result) / (result - 1.0));
	bob.plata_ipoteka = plata;
}



void alice_rashod(const int year, const int month)
{
	alice.bank_account -= alice.rashod;
}


void bob_rashod(const int year, const int month)
{
	bob.bank_account -= bob.rashod;
}


void bob_plata_ipoteka(const int year, const int month)
{
	bob.bank_account -= bob.plata_ipoteka;
}



void inflation(const int year, const int month)
{
	alice.salary += (Money)(alice.salary * alice.inflation_pp / 100.0);
	bob.salary += (Money)(bob.salary * bob.inflation_pp / 100.0);

	alice.rent += (Money)(alice.rent * alice.inflation_pp / 100.0);
	bob.rent += (Money)(bob.rent * bob.inflation_pp / 100.0);

	alice.house_price += (Money)(alice.house_price * alice.inflation_pp / 100.0);
	bob.house_price += (Money)(bob.house_price * bob.inflation_pp / 100.0);

	alice.rashod += (Money)(alice.rashod * alice.inflation_pp / 100.0);
	bob.rashod += (Money)(bob.rashod * bob.inflation_pp / 100.0);
}



void simulation()
{
	int month = 9;
	int year = 2023;

	bob_ipoteka(year, month);

	while (!(year == 2053 && month == 9)) {
		alice_deposite_income(year, month);
		alice_salary_income(year, month);
		alice_rent(year, month);
		alice_rashod(year, month);
		
		bob_deposite_income(year, month);
		bob_salary_income (year, month);
		bob_plata_ipoteka(year, month);
		bob_rashod(year, month);


		++month;
		if (month == 13) {
			inflation(year, month);
			month = 1;
			++year;
		}
	}
}



void print_person(const struct Person person)
{
	printf("%s\n", person.name);
	printf(" bank account = %lld rub. %lld kop\n", (Money)(person.bank_account / 100), person.bank_account % 100);

	Money capital = person.bank_account + person.house_price;
	printf(" capital = %lld rub. %lld kop\n", (Money)(capital / 100), capital % 100);

	printf(" plata po ipoteke = %lld rub. %lld kop\n", (Money)(person.plata_ipoteka / 100), person.plata_ipoteka % 100);
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
