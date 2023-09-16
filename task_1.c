#include <stdio.h>
#include <math.h>

const double INFL = 0.07;

double platezh_bob(double procent)
{
	procent = procent / 12.0;
	double platezh;
	platezh = 19 * 1000 * 1000 * (procent * (powf(1 + procent, 360)) / (powf(1 + procent, 360) - 1));
};

double kvartira_bob(double kvartira)
{
	kvartira = kvartira * (powf(1 + INFL, 30));
};


double capital( double zp, double traty,double platezh, double  remont, double bank_pp, double cap)
{

	double proc_mes = bank_pp/ 12;
	double zp_itog;
	for (int i = 1; i < 360; i++)
	{
		zp_itog = zp * powf(1 + INFL, i / 12);
		cap += zp_itog;
		if (i >= 60)
		{
			remont = 0;
		}
		cap = (cap - platezh - ((traty+remont) * powf(1 + (INFL / 12), i))) * (1 + (bank_pp / 12));

	}
};

int main()
{
	double platezh = platezh_bob(0.07);
	double bob_capital = capital(200000.0, 50000.0, platezh , 10000.0, 0.11 , 0.0) + kvartira_bob(20000000.0);
	printf("\nBob's capital: ");
	double alice_capital = capital(200000.0, 50000.0+30000.0, 0.0, 0.0, 0.11, 1000000.0);
	printf("%f", bob_capital);
	printf("\nAlice's capital: ");
	printf("%f", alice_capital);
	return 0;
}