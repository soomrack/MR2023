#include <stdio.h>
#include <math.h>

const int BOBWAGE = 200 * 1000 * 100;
const int ALICEWAGE = 200 * 1000 * 100;
const int MORTGAGEINTEREST = 0.07;
const double DEPOSITINTEREST = 0.009342;
const int BOBINITIALCAPITAL = 1000 * 1000 * 100;
const int ALICEINITIALCAPITAL = 1000 * 1000 * 100;
const int DOWNPAYMENT = 1000 * 1000 * 100;
const short int MORTGAGEPERIOD = 30;
const int ALICERENT = 30 * 1000 * 100;
const int BOBRENT = 10 * 1000 * 100;
const int BOBEXPENSES = 50 * 1000 * 100;
const int ALICEEXPENSES = 50 * 1000 * 100;
const long int APARTMENTPRICE = 20 * 1000 * 1000 * 100;
const double MONTHINFLATION = 0.005945;

short int totalPeriod = 30 * 12;
short int currentMonth = 1;
double bobCapital = 100 * 1000 * 100;
double aliceCapital = 1000 * 1000 * 100;
double mortgageDebt = APARTMENTPRICE;
double realApartmentPrice = APARTMENTPRICE;

void InitialCapital()
{
	bobCapital = BOBINITIALCAPITAL - DOWNPAYMENT;
	aliceCapital = ALICEINITIALCAPITAL;
};

void calc()
{
	for (currentMonth; currentMonth <= totalPeriod; currentMonth++) {

		bobCapital = bobCapital + BOBWAGE;
		bobCapital = bobCapital - BOBEXPENSES - BOBEXPENSES * MONTHINFLATION * currentMonth;
		bobCapital = bobCapital - APARTMENTPRICE / totalPeriod - mortgageDebt * MORTGAGEINTEREST / totalPeriod;
		mortgageDebt = mortgageDebt - APARTMENTPRICE / totalPeriod - mortgageDebt * MORTGAGEINTEREST / totalPeriod;
		bobCapital = bobCapital - BOBRENT - BOBRENT * MONTHINFLATION * currentMonth;
		realApartmentPrice = realApartmentPrice + realApartmentPrice * MONTHINFLATION;

		aliceCapital = aliceCapital + ALICEWAGE + ALICEWAGE * MONTHINFLATION * currentMonth;
		aliceCapital = aliceCapital - ALICEEXPENSES - ALICEEXPENSES * MONTHINFLATION * currentMonth;
		aliceCapital = aliceCapital - ALICERENT - ALICERENT * MONTHINFLATION * currentMonth;
		aliceCapital = aliceCapital + aliceCapital * DEPOSITINTEREST;

		printf("\nThe end of month: ");
		printf("%d", currentMonth);
		printf("\nBob's estimater capital is ");
		printf("%f", bobCapital / 100);
		printf(" rubles");
		printf("\nAlice's estimater capital is ");
		printf("%f", aliceCapital / 100);
		printf("\n rubles");
	}
	printf("\n                   ");
	printf("\n___________________");
	printf("\n                   ");
	printf("\nBob's net worth is ");
	printf("%f", (bobCapital + realApartmentPrice) / 100);
	printf("\n rubles");
	printf("\nAlice's net worth is ");
	printf("%f", aliceCapital / 100);
	printf("\n rubles");
};

int main() 
{
	InitialCapital();

	calc();

	return 0;
}