#include <stdio.h>
#include <string.h>

typedef unsigned long long int Money; // kopeiki


struct Person {
	char name[5];
	Money bank_schet;
	Money kvartira;
	Money zarplata;
	Money arenda;
	Money razhodi; // eda, odezda i razvlechenia
	Money platez_ipoteka;
	double pp_vklad;
};


struct Person Alice;
struct Person Bob;


void alice_init()
{
	strcpy(Alice.name, "Alice");
	Alice.bank_schet = 1 * 1000 * 1000 * 100;
	Alice.kvartira = 0;
	Alice.zarplata = 200 * 1000 * 100;
	Alice.arenda = 30 * 1000 * 100;
	Alice.razhodi = 60 * 1000 * 100;
	Alice.platez_ipoteka = 0;
	Alice.pp_vklad = 1.11;
}


void bob_init()
{
	strcpy(Bob.name, "Bob");
	Bob.bank_schet = 0;
	Bob.kvartira = 20 * 1000 * 1000 * 100;
	Bob.zarplata = 200 * 1000 * 100;
	Bob.arenda = 0;
	Bob.razhodi = 60 * 1000 * 100;
	Bob.platez_ipoteka = (10000 + 126407) * 100; // dengi na remont+platez
	Bob.pp_vklad = 1.11;
}


Money bank_schet_inc(struct Person person) {
	person.bank_schet = (Money)(person.bank_schet * (1 + 0.11 / 12.) + (person.zarplata - person.arenda - person.razhodi - person.platez_ipoteka));
	return person.bank_schet;
}


Money inf_zarplata(struct Person person) {
	person.zarplata = (Money)(person.zarplata * 1.07);
	return person.zarplata;
}


Money inf_arenda(struct Person person) {
	person.arenda = (Money)(person.arenda * 1.07);
	return person.arenda;
}


Money inf_razhodi(struct Person person) {
	person.razhodi = (Money)(person.razhodi * 1.07);
	return person.razhodi;
}


Money inf_kvartira(struct Person person) {
	person.kvartira = (Money)(person.kvartira * 1.07);
	return person.kvartira;
}


void print_Bob(Money kapital) {
	printf("Bob Капитал = %lld\n", kapital / 100);
	printf("\n");
}


void print_Alice(Money kapital) {
	printf("Alice Капитал = %lld\n", kapital / 100);
	printf("\n");
}


Money sim_Bob(struct Person person)
{
	int month = 9;
	int year = 2023;
	while (!(year == 2053 && month == 9)) {
		if (month == 1) {
			Bob.zarplata = inf_zarplata(Bob);
			Bob.arenda = inf_arenda(Bob);
			Bob.razhodi = inf_razhodi(Bob);
			Bob.kvartira = inf_kvartira(Bob);
		}

		if (!(month == 6 ^ month == 12)) {
			Bob.bank_schet = bank_schet_inc(Bob);
		}
		else {
			if (month == 6) {
				Bob.bank_schet = bank_schet_inc(Bob) - Bob.zarplata;
			}
			if (month == 12) {
				Bob.bank_schet = bank_schet_inc(Bob) + Bob.zarplata;
			}
		}

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
	return (Bob.bank_schet + Bob.kvartira);
}


Money sim_Alice(struct Person person)
{
	int month = 9;
	int year = 2023;
	while (!(year == 2053 && month == 9)) {
		if (month == 1) {
			Alice.zarplata = inf_zarplata(Alice);
			Alice.arenda = inf_arenda(Alice);
			Alice.razhodi = inf_razhodi(Alice);
			Alice.kvartira = inf_kvartira(Alice);
		}

		if (!(month == 6 ^ month == 12)) {
			Alice.bank_schet = bank_schet_inc(Alice);
		}
		else {
			if (month == 6) {
				Alice.bank_schet = bank_schet_inc(Alice) - Alice.zarplata;
			}
			if (month == 12) {
				Alice.bank_schet = bank_schet_inc(Alice) + Alice.zarplata;
			}
		}

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
	return (Alice.bank_schet + Alice.kvartira);
}


int main()
{
	alice_init();
	bob_init();

	print_Bob (sim_Bob(Bob));
	print_Alice (sim_Alice(Alice));

	return 0;
}