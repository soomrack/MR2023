#include <stdio.h>
#include <math.h>

double main()
{
	//переменные
	int salary = 200000, time = 240, i;
	int rent = 30000, credit = 19000000;
	double abank = 1000000.0, bbank = 0.0, deposit = 0.09, abalance, bbalance;
	double creditpercent = 0.07, creditpayment, m = 0.07/12;

	abalance = salary - rent;
	creditpayment = credit*((m * pow(1 + m, time)) / (pow(1 + m, time) - 1));
	bbalance = salary - creditpayment;
	bbank = bbalance;

	//расчет
	for (i = 1; i <= time; ++i){
		abank += (abank * (deposit / 12));
		bbank += (bbank * (deposit / 12));
		abank -= abank * (0.07 / 12);
		bbank -= bbank * (0.07 / 12);
		abank += abalance;
		bbank += bbalance;
	}

	printf("%f   %f", abank, bbank);

}