#include <stdio.h>  
#include <math.h> 

typedef long long int Rub;


struct Person {
	char name[5];
    	Rub start;
   	Rub zp;
	Rub kvar;
	Rub renta;
	Rub rashod; // eda, odezda i razvlechenia
	Rub platez_ipoteka;
	double pp_vklad;
};

struct Person Bob;  // buy house
struct Person Alice;

void alice_init()
{
	strcpy(Alice.name, "Alice");
	Alice.start = 1000000;
	Alice.kvar = 0;
	Alice.zp = 200000;
	Alice.renta = 30000;
	Alice.razhod = 30000;
	Alice.pp_vklad = 1.11;
	Alice.platez_ipoteka = 0;
}


void bob_init()
{
	strcpy(Bob.name, "Bob");
	Bob.start = 0;
	Bob.kvar = 20000000;
	Bob.zp = 200000;
	Bob.renta = 0;
	Bob.razhod = 30000;
	Bob.platez_ipoteka = (10000 + 126407) * 100; // dengi na remont+platez
	Bob.pp_vklad = 1.11;
}


Rub start_inc(struct Person person) {
	person.start = (Rub)(person.start * (1 + 0.11 / 12.) + (person.zp - person.renta - person.razhod - person.platez_ipoteka));
	return person.start;
}


Rub inf_zp(struct Person person) {
	person.zp = (Rub)(person.zp * 1.07);
	return person.zp;
}


Rub inf_renta(struct Person person) {
	person.renta = (Rub)(person.renta * 1.07);
	return person.renta;
}


Rub inf_razhod(struct Person person) {
	person.razhod = (Rub)(person.razhod * 1.07);
	return person.razhod;
}


Money inf_kvar(struct Person person) {
	person.kvar = (Rub)(person.kvar * 1.07);
	return person.kvar;
}


void print_Bob(Rub kapital) {
	printf("Bob kapital = %lld\n", kapital / 100);
	printf("\n");
}


void print_Alice(Rub kapital) {
	printf("Alice kapital = %lld\n", kapital / 100);
	printf("\n");
}


Rub sim_Bob(struct Person person)
{
	int month = 9;
	int year = 2023;
	while (!(year == 2053 && month == 9)) {
		if (month == 1) {
			Bob.zp = inf_zp(Bob);
			Bob.renta = inf_renta(Bob);
			Bob.razhod = inf_razhod(Bob);
			Bob.kvar = inf_kvar(Bob);
		}

		if (!(month == 6 ^ month == 12)) {
			Bob.start = start_inc(Bob);
		}
		else {
			if (month == 6) {
				Bob.start = start_inc(Bob) - Bob.zp;
			}
			if (month == 12) {
				Bob.start = start_inc(Bob) + Bob.zp;
			}
		}

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
	return (Bob.start + Bob.kvar);
}


Rub sim_Alice(struct Person person)
{
	int month = 9;
	int year = 2023;
	while (!(year == 2053 && month == 9)) {
		if (month == 1) {
			Alice.zp = inf_zp(Alice);
			Alice.renta = inf_renta(Alice);
			Alice.razhod = inf_razhod(Alice);
			Alice.kvar = inf_kvar(Alice);
		}

		if (!(month == 6 ^ month == 12)) {
			Alice.start = start_inc(Alice);
		}
		else {
			if (month == 6) {
				Alice.start = start_inc(Alice) - Alice.zp;
			}
			if (month == 12) {
				Alice.start = start_inc(Alice) + Alice.zp;
			}
		}

		++month;
		if (month == 13) {
			month = 1;
			++year;
		}
	}
	return (Alice.start + Alice.kvar);
}


int main()
{
	alice_init();
	bob_init();

	print_Bob (sim_Bob(Bob));
	print_Alice (sim_Alice(Alice));

	return 0;
}
