#include <stdio.h>
#include <math.h>

const int BOBWAGE = 200000;
const int ALICEWAGE = 200000;
const int MORTGAGEINTEREST = 0.07;
const float DEPOSITINTEREST = 0.009342;
const int BOBINITIALCAPITAL = 1000000;
const int ALICEINITIALCAPITAL = 1000000;
const int DOWNPAYMENT = 1000000;
const int MORTGAGEPERIOD = 30;
const int ALICERENT = 30000;
const int BOBRENT = 10000;
const int BOBEXPENSES = 50000;
const int ALICEEXPENSES = 50000;
const long int APARTMENTPRICE = 20000000;
const float MONTHINFLATION = 0.005945;

int totalPeriod = 30 * 12;
int currentMonth = 1;
float bobCapital = 1000000;
float aliceCapital = 1000000;
float mortgageDebt = APARTMENTPRICE;
float realApartmentPrice = APARTMENTPRICE;

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
	printf("%f", bobCapital + realApartmentPrice);
	printf("\n rubles");
	printf("\nAlice's net worth is ");
	printf("%f", aliceCapital);
	printf("\n rubles");

	return 0;

}