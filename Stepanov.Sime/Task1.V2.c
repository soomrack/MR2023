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

struct Person alice;
struct Person bob;

void alice_init() 
{
	strcpy(alice.name, "Alice");
	alice.bank_schet = 1 * 1000 * 1000 * 100;
	alice.kvartira = 0;
	alice.zarplata = 200 * 1000 * 100;
	alice.arenda = 30 * 1000 * 100;
	alice.razhodi = 60*1000*100;
	alice.platez_ipoteka = 0;
	alice.pp_vklad = 1.11;
}


void bob_init()
{
	strcpy(bob.name, "Bob");
	bob.bank_schet = 0;
	bob.kvartira = 20*1000*1000*100;
	bob.zarplata = 200 * 1000 * 100;
	bob.arenda = 0;
	bob.razhodi = 60 * 1000*100;
	bob.platez_ipoteka = (10000+126407)*100; // dengi na remont+platez
	bob.pp_vklad = 1.11;
}


Money bank_schet_inc (struct Person person) {
	person.bank_schet =(Money)(person.bank_schet*(1+0.11/12.) + (person.zarplata - person.arenda - person.razhodi - person.platez_ipoteka));
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


void out(struct Person person) {
	printf("%s\n", person.name);
	printf("Капитал = %lld\n", (person.bank_schet + person.kvartira)/100);
	printf("\n");
}


int main()
{
	alice_init();
	bob_init();
	int i, j;

	for (j = 1; j <= 30; j++)
	{
		for (i = 1; i <= 12; i++)
		{
			bob.bank_schet = bank_schet_inc(bob);
		}

		bob.zarplata = inf_zarplata(bob);
		bob.arenda = inf_arenda(bob);
		bob.razhodi = inf_razhodi(bob);
		bob.kvartira = inf_kvartira(bob);
		printf("Капитал = %lld\n", bob.bank_schet + bob.kvartira);
	}
	out(bob);
	for (j = 1; j <= 30; j++)
	{
		for (i = 1; i <= 12; i++)
		{
			alice.bank_schet = bank_schet_inc(alice);
		}

		alice.zarplata = inf_zarplata(alice);
		alice.arenda = inf_arenda(alice);
		alice.razhodi = inf_razhodi(alice);
		alice.kvartira = inf_kvartira(alice);
	}
	out(alice);
	return 0;
}