
#include <stdio.h>
#include <string.h>

typedef long long int Money;

struct Person {
	Money schet;	// копейки
	int percent;	
	Money zp;		// копейки
	Money arenda;   // копейки
	Money eda;		// копейки
	Money veshi;    // копейки
	Money ostatok;  // копейки
	Money ipoteka;  // копейки
	char name[6];
	
};

int YEAR;
int MONTH;

struct Person alice;
struct Person bob;

void alice_init() 
{
	alice.schet = 1000 * 1000 * 100;
	alice.zp = 200 * 1000 * 100;
	alice.percent = 7;
	alice.arenda = 30000 * 100;
	alice.eda = 20000 * 100;
	alice.veshi = 20000 * 100;
	alice.ipoteka = 0;
	strcpy_s(alice.name, "Alice");
}

void bob_init() {
	bob.schet = 1000 * 1000 * 100;
	bob.zp = 200 * 1000 * 100;
	bob.percent = 7;
	bob.arenda = 0;
	bob.eda = 20000 * 100;
	bob.veshi = 50000 * 100;
	bob.ipoteka = 20 * 1000 * 1000 * 100;
	strcpy_s(bob.name, "Bob");
}


void bob_razmer_dolga(const int YEAR, const int MONTH) 
{
	bob.ipoteka -= bob.schet;
}

void bob_rost_dolga(const int YEAR, const int MONTH) 
{
	bob.ipoteka += (Money)((double)bob.ipoteka * (double)bob.percent / 100.0 / 12.0);
}

void bob_ostatok(const int YEAR, const int MONTH) 
{
	bob.ostatok = bob.zp - bob.arenda - bob.veshi - bob.eda;
}

void bob_vlozhenia(const int YEAR, const int MONTH) 
{
	bob.ipoteka = bob.ipoteka - bob.ostatok;
}

void bob_uvelich_zp(const int YEAR, const int MONTH) 
{
	bob.zp += (Money)((double)bob.zp * (double)bob.percent / 100.0 / 12.0);
}

void bob_uvelich_trat(const int YEAR, const int MONTH) 
{
	bob.eda = bob.eda * bob.percent / 100;
	bob.veshi = bob.veshi * bob.percent / 100;
}



void alice_uvelich_vklada(const int YEAR, const int MONTH) 
{
	alice.schet += (Money)(alice.ostatok + alice.schet * alice.percent / 100.0 / 12.0);
}

void alice_ostatok(const int YEAR, const int MONTH) 
{
	alice.ostatok = alice.zp - alice.arenda - alice.eda - alice.veshi;
}

void alice_uvelich_zp(const int YEAR, const int MONTH) 
{
	alice.zp += (Money)((double)alice.zp * (double)alice.percent / 100.0 / 12.0);
}

void alice_uvelich_trat(const int YEAR, const int MONTH) 
{
	alice.eda = alice.eda * alice.percent / 100;
	alice.arenda = alice.arenda * alice.percent / 100;
	alice.veshi = alice.veshi * alice.percent / 100;
}

void print_person(const struct Person person) {
	if (bob.ipoteka < 0) {
		bob.ipoteka = 0 - bob.ipoteka;
		bob.schet = bob.ipoteka;
	}
	
	printf("%s\n", person.name);
	printf("%lld\n", person.schet);
}

void simulation() 
{
	MONTH = 9;
	YEAR = 2023;
	do {
		alice_ostatok(YEAR, MONTH);
		alice_uvelich_vklada(YEAR, MONTH);
		
		bob_ostatok(YEAR, MONTH);
		bob_vlozhenia(YEAR, MONTH);
				
		++MONTH;
		if (MONTH == 13) {
			MONTH = 1;
			alice_uvelich_zp(YEAR, MONTH);
			bob_uvelich_zp(YEAR, MONTH);
			++YEAR;
			alice_uvelich_trat(YEAR, MONTH);
			bob_uvelich_trat(YEAR, MONTH);
		}

		if (MONTH == 9 && YEAR == 2053) {
			break;
		}
		
	} while (YEAR != 2054);

}


int main()
{
	alice_init();
	bob_init();
	bob_razmer_dolga(YEAR, MONTH);
	simulation();
	print_person(alice);
	print_person(bob);
	
	return 0;
}
