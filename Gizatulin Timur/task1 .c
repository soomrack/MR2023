#include<stdio.h>
#include<time.h>

int main() {
	// for Alice

	double bank = 1000000;
	float salary = 150000;
	float arendPrice = 30000;
	double flatPrice = 20000000;

	for (int i = 0; i < 240; i++) {
		bank *= 1.0075;
		bank += salary - arendPrice;
	}

	for (int i = 0; i < 20; i++) {
		flatPrice *= 1.07;
	}

	bank -= flatPrice;
	printf("%f - Alice Bank after 20 years\n", bank);

	// Bob
    bank = 1000000;
	salary = 150000;
	flatPrice = 20000000;
	float procent = flatPrice * 1.07 / 240;

	for (int i = 0; i < 240; i++) {
		bank += salary - procent;
	}
	printf("%f - Bob Bank after 20 years", bank);
	
	

	return 0;
}
