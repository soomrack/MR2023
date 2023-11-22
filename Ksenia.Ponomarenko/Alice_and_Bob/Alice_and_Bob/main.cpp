#include <stdio.h>
#include <math.h>

const double INFL = 0.07;

double payment_bob(double mortgage, int year, int flat, int start_capital)
{
	int S = flat - start_capital; // Credit sum
	int n = year * 12; // Mounth count while credit
	float r = mortgage / 12; // Mounth rate
	double count = pow((1 + r), (float)n);
	double platezh = S * ((r * count) / (count - 1)); // Sum of annually payment during mortgage
	return platezh;
};

double flat_bob(double flat, int year )
{
	flat = flat * (powf(1 + INFL, year));
	return flat;
};


double capital(double salary, double expenditure, double payment, double  repair, double bank_pp, double capital)
{

	double percent_mounth = bank_pp / 12;
	double salary_total;
	for (int i = 1; i < 360; i++)
	{ 
		salary_total = salary * powf(1 + INFL, i / 12);
		capital += salary_total;
		if (i >= 60)
		{
			repair = 0;
		}
		capital = (capital - payment - ((expenditure + repair) * powf(1 + (INFL / 12), i))) * (1 + (bank_pp / 12));
	}
	return capital;
};

int main()
{
	double payment = payment_bob(0.07, 30, 20000000, 1000000);
	double bob_capital = capital(200000.0, 50000.0, payment, 10000.0, 0.11, 0.0) + flat_bob(20000000.0,30);
	printf("\nBob's capital: ");
	double alice_capital = capital(200000.0, 50000.0 + 30000.0, 0.0, 0.0, 0.11, 1000000.0);
	printf("%f", bob_capital);
	printf("\nAlice's capital: ");
	printf("%f", alice_capital);
	return 0;
}