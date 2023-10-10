#include <stdio.h>
#include <string.h>
<<<<<<< HEAD

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
	//char name[6];
};

int YEAR;
int MONTH;

=======
#include <math.h>

typedef long long int Money;  // копейки

struct Person {
    Money schet; 
    double bank_ip_percent;	
    double bank_vk_percent;
    double index_percent;
    Money zp; 
    Money arenda;  
    Money eda;  
    Money veshi;  
	Money ostatok; 
	Money ipoteka;  
	char name[6];
	Money platezh;
	Money traty;
	Money kvartira;
	Money kapital;
};

>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
struct Person alice;
struct Person bob;

void alice_init() 
{
	alice.schet = 1000 * 1000 * 100;
	alice.zp = 200 * 1000 * 100;
<<<<<<< HEAD
	alice.percent = 7;
=======
	alice.bank_vk_percent = 7.0;
	bob.index_percent = 7.0;
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
	alice.arenda = 30000 * 100;
	alice.eda = 20000 * 100;
	alice.veshi = 20000 * 100;
	alice.ipoteka = 0;
<<<<<<< HEAD
	//strcpy(alice.name, "Alice");
}

void bob_init() 
{
	bob.schet = 1000 * 1000 * 100;
	bob.zp = 200 * 1000 * 100;
	bob.percent = 7;
	bob.arenda = 0;
	bob.eda = 20000 * 100;
	bob.veshi = 50000 * 100;
	bob.ipoteka = 20 * 1000 * 1000 * 100;
	//strcpy(bob.name, "Bob");
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
=======
	strcpy_s(alice.name, "Alice");
	alice.traty;
	alice.kapital;
}


void bob_init() {
	bob.schet = 1000 * 1000 * 100;
	bob.zp = 200 * 1000 * 100;
	bob.bank_ip_percent = 7.0;
	bob.bank_vk_percent = 7.0;
	bob.index_percent = 7.0;
	bob.arenda = 0;
	bob.eda = 20000 * 100;
	bob.veshi = 30000 * 100;
	bob.ipoteka = 20 * 1000 * 1000 * 100;
	strcpy_s(bob.name, "Bob");
	bob.platezh = 0;
	bob.traty;
	bob.kvartira = 20 * 1000 * 1000 * 100;
	bob.kapital;
}


void bob_platezh()
{
	int sum_year = 30;
	int srok = sum_year * 12;
	double mnozhit;  // множитель в формуле
	Money razmer_ipoteki = 20000 * 1000 * 100;
	double stavka = (bob.bank_ip_percent / 100.0) / 12.0;  // процент в месяц
	mnozhit = pow((1 + stavka), srok);
	double koef;
	koef = (stavka * mnozhit / (mnozhit - 1));
	bob.platezh = (Money)((double)razmer_ipoteki * koef);
	
}


void bob_umensh_dolga(const int year, const int month)
{
	if (year == 2023 && month == 9) {
		bob.ipoteka -= bob.schet;
		bob.schet = 0;
	}
	bob.ipoteka -= bob.platezh;
}


void bob_rost_dolga() 
{
	bob.ipoteka += (Money)((double)bob.ipoteka * (double)bob.bank_ip_percent / 100.0 / 12.0);
}


void bob_traty() 
{
	bob_platezh();
	bob.traty = bob.arenda + bob.veshi + bob.eda + bob.platezh;
}


void bob_zp(const int year, const int month) 
{
	bob_traty();
	if (year == 2030 && month == 6) {
		bob.zp = 0; // увольнение
	}
	if (year == 2030 && month == 7) {
		bob.zp = 200 * 1000 * 100;
	}
	if (month == 12) {
		bob.schet += bob.zp - bob.traty; // 13-я зп
	}
	bob.schet += bob.zp - bob.traty;
}


void bob_uvelich_schet()
{
	bob.schet += (Money)((double)bob.schet * (bob.bank_vk_percent / 100.0 / 12.0));
}


void bob_uvelich_zp() 
{
	bob.zp += (Money)((double)bob.zp * (double)bob.index_percent / 100.0);
}


void bob_uvelich_trat() 
{
	bob.traty += (Money)((double)bob.traty * (double)bob.index_percent / 100.0 / 12.0);
}


void bob_kvartira()
{
	bob.kvartira += (Money)((double)bob.kvartira * (double)bob.index_percent / 100.0 / 12.0);
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
}



<<<<<<< HEAD
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



void pechat() 
{
	printf("Alice\n");
	printf("%lld\n", alice.schet);
	printf("\nBob\n");
	if (bob.ipoteka < 0)
		bob.ipoteka = 0 - bob.ipoteka;
	//printf("\n%s\n", person.name);
	printf("%lld\n", bob.ipoteka);
=======
void alice_traty()
{
	alice.traty = alice.arenda + alice.eda + alice.veshi;
}


void alice_zp(const int year, const int month)
{
	alice_traty();
	if (year == 2030 && month == 6) alice.zp = 0; // отпуск
	if (year == 2030 && month == 7) alice.zp = 200 * 1000 * 100;
	if (month == 12) alice.schet += alice.zp - alice.traty; // 13-я зп
	alice.schet += alice.zp - alice.traty;
}


void alice_uvelich_vklada() 
{
	alice.schet += (Money)((double)alice.schet * alice.bank_vk_percent / 100.0 / 12.0);
}


void alice_uvelich_zp() 
{
	alice.zp += (Money)((double)alice.zp * (double)alice.index_percent / 100.0);
}


void alice_uvelich_trat() 
{
	alice.traty += (Money)((double)alice.traty * (double)alice.index_percent / 100.0 / 12.0);
}


void print_person(const struct Person person) 
{	
	bob.kapital = bob.schet + bob.kvartira;
	printf("%s\n", person.name);
	printf("%lld\n", person.kapital);
}


void print_vyvod()  // сравнение, чья стратегия лучше
{
	if (alice.kapital > bob.kapital) {
		printf("\n\tAlice's strategy is better\n");
	}
	else printf("\n\tBob's strategy is better\n");
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
}


void simulation() 
{
<<<<<<< HEAD
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
=======
	int month = 9;
	int year = 2023;
	while (!(year==2053 && month==9)) {

		alice_uvelich_vklada();  // проценты по вкладу
		alice_zp(year, month);  // alice получила зп и остаток положила на счёт 
		alice_uvelich_trat();  // еда, вещи, аренда
				
		if (month == 1) {
			alice_uvelich_zp();
		}
		alice.kapital = alice.schet;


		bob_uvelich_schet(); // начисление процента по вкладу боба
		bob_zp(year, month);  // боб кладёт остаток от зп на счёт
		bob_rost_dolga();  // процент по ипотеке
		bob_umensh_dolga(year, month);  // выплата части ипотеки
		bob_uvelich_trat();
		bob_kvartira();  // увеличение стоимости квартиры
		
		if (month == 1) {
			bob_uvelich_zp();  // увеличение зп в начале года
		}
						
		++month;
		if (month == 13) {
			month = 1;
			++year;		
			//printf("\t%d\n", year);
		}
						
	} 
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0

}


int main()
{
	alice_init();
	bob_init();
<<<<<<< HEAD
	bob_razmer_dolga(YEAR, MONTH);
	simulation();
	pechat();

=======
		
	simulation();

	print_person(alice);
	print_person(bob);
	print_vyvod();
	
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
	return 0;
}

