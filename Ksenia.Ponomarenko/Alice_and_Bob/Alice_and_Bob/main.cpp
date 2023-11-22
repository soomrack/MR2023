#include <stdio.h>
#include <math.h>

const double INFL = 0.07;

double platezh_bob(double ipoteka, int year, int kvar, int start)
{
	int S = kvar - start; // —умма кредита
	int n = year * 12; //  ол-во мес€цев во всем сроке кредита
	float r = ipoteka / 12; // ћес€чна€ ставка
	double count = pow((1 + r), (float)n); // ¬озводим (1+r) в степень n, попутно перевод€ n из int в float
	double platezh = S * ((r * count) / (count - 1)); // —умма ежемес€чного платежа по ипотеке по формуле
	return platezh;
};

double kvartira_bob(double kvartira, int year )
{
	kvartira = kvartira * (powf(1 + INFL, year));
	return kvartira;
};


double capital(double zp, double traty, double platezh, double  remont, double bank_pp, double cap)
{

	double proc_mes = bank_pp / 12;
	double zp_itog;
	for (int i = 1; i < 360; i++)
	{ 
		zp_itog = zp * powf(1 + INFL, i / 12);
		cap += zp_itog;
		if (i >= 60)
		{
			remont = 0;
		}
		cap = (cap - platezh - ((traty + remont) * powf(1 + (INFL / 12), i))) * (1 + (bank_pp / 12));
	}
	return cap;
};

int main()
{
	double platezh = platezh_bob(0.07, 30, 20000000, 1000000);
	double bob_capital = capital(200000.0, 50000.0, platezh, 10000.0, 0.11, 0.0) + kvartira_bob(20000000.0,30);
	printf("\nBob's capital: ");
	double alice_capital = capital(200000.0, 50000.0 + 30000.0, 0.0, 0.0, 0.11, 1000000.0);
	printf("%f", bob_capital);
	printf("\nAlice's capital: ");
	printf("%f", alice_capital);
	return 0;
}