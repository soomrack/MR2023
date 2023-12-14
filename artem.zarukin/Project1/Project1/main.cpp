#include <stdio.h>
#include <math.h>
#include <string.h>

struct Person
{
	int wage;
	int initialCapital;
	int rent;
	int expenses;
	double capital;
	char name[6];
};


struct Person alice;
struct Person bob;

const int MORTGAGEINTEREST = 0.07;
const double DEPOSITINTEREST = 0.009342;
const int DOWNPAYMENT = 1000 * 1000 * 100;
const short int MORTGAGEPERIOD = 30;
const long int APARTMENTPRICE = 20 * 1000 * 1000 * 100;
const double MONTHINFLATION = 0.005945;

short int totalPeriod = 30 * 12;
short int currentMonth = 1;
double mortgageDebt = APARTMENTPRICE;
double realApartmentPrice = APARTMENTPRICE;

void InitialCapital()
{

	bob.wage = 200 * 1000 * 100;
	bob.initialCapital = 1000 * 1000 * 100;
	bob.rent = 10 * 1000 * 100;
	bob.expenses = 50 * 1000 * 100;

	alice.wage = 200 * 1000 * 100;
	alice.initialCapital = 1000 * 1000 * 100;
	alice.rent = 30 * 1000 * 100;
	alice.expenses = 50 * 1000 * 100;

	bob.capital = bob.initialCapital - DOWNPAYMENT;
	alice.capital = alice.initialCapital;

};

void calc()
{
	for (currentMonth; currentMonth <= totalPeriod; currentMonth++) {

		bob.capital = bob.capital + bob.wage;
		bob.capital = bob.capital - bob.expenses - bob.expenses * MONTHINFLATION * currentMonth;
		bob.capital = bob.capital - APARTMENTPRICE / totalPeriod - mortgageDebt * MORTGAGEINTEREST / totalPeriod;
		mortgageDebt = mortgageDebt - APARTMENTPRICE / totalPeriod - mortgageDebt * MORTGAGEINTEREST / totalPeriod;
		bob.capital = bob.capital - bob.rent - bob.rent * MONTHINFLATION * currentMonth;
		realApartmentPrice = realApartmentPrice + realApartmentPrice * MONTHINFLATION;

		alice.capital = alice.capital + alice.wage + alice.wage * MONTHINFLATION * currentMonth;
		alice.capital = alice.capital - alice.expenses - alice.expenses * MONTHINFLATION * currentMonth;
		alice.capital = alice.capital - alice.rent - alice.rent * MONTHINFLATION * currentMonth;
		alice.capital = alice.capital + alice.capital * DEPOSITINTEREST;

		printf("\nThe end of month: ");
		printf("%d", currentMonth);
		printf("\nBob's estimater capital is ");
		printf("%f", bob.capital / 100);
		printf(" rubles");
		printf("\nAlice's estimater capital is ");
		printf("%f", alice.capital / 100);
		printf("\n rubles");
	}
	printf("\n                   ");
	printf("\n___________________");
	printf("\n                   ");
	printf("\nBob's net worth is ");
	printf("%f", (bob.capital + realApartmentPrice) / 100);
	printf("\n rubles");
	printf("\nAlice's net worth is ");
	printf("%f", alice.capital / 100);
	printf("\n rubles");
};

int main() 
{
	InitialCapital();

	calc();

	return 0;
}