#include <stdio.h>
#include <math.h>

const int BOBWAGE = 20000000;
const int ALICEWAGE = 20000000;
const double MORTGAGEINTEREST = 0.07;
const double DEPOSITINTEREST = 0.009342;
const int BOBINITIALCAPITAL = 100000000;
const int ALICEINITIALCAPITAL = 100000000;
const int DOWNPAYMENT = 10000000;
const int MORTGAGEPERIOD = 30;
const int ALICERENT = 3000000;
const int BOBRENT = 1000000;
const int BOBEXPENSES = 5000000;
const int ALICEEXPENSES = 5000000;
const long int APARTMENTPRICE = 2000000000;
const double MONTHINFLATION = 0.005945;

int totalPeriod = 30 * 12;
int currentMonth = 1;
double bobCapital = 100000000;
double aliceCapital = 100000000;
double mortgageDebt = APARTMENTPRICE;
double realApartmentPrice = APARTMENTPRICE;

int main() {

	bobCapital = BOBINITIALCAPITAL - DOWNPAYMENT;
	aliceCapital = ALICEINITIALCAPITAL;

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
		printf("%f", bobCapital);
		printf(" rubles");
		printf("\nAlice's estimater capital is ");
		printf("%f", aliceCapital);
		printf("\n rubles");
	}
	printf("\n                   ");
	printf("\n___________________");
	printf("\n                   ");
	printf("\nBob's net worth is ");
	printf("%f", ((bobCapital + realApartmentPrice) / 100));
	printf("\n rubles");
	printf("\nAlice's net worth is ");
	printf("%f", (aliceCapital) / 100);
	printf("\n rubles");

	return 0;

}
