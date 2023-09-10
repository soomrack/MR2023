#include "capital.h"


int main(int argc, char * argv[])
{
int totalMonth = atoi(argv[1]);
long otherExpenses = (long)atoi(argv[2]);
struct Capital bob;
bob.name = "Bob";
bob.monthlyIncome = 200000;
bob.otherExpenses = otherExpenses;
bob.bankDebt = 19000000;
bob.inflation = 3;
bob.interestRate = 9;
bob.mortgageInterest = 7;
bob.currentCapital = 0;
bob.apartmentExpenses = calcBobApartmentFee(bob.bankDebt, 
                                        bob.mortgageInterest);

struct Capital alice;
alice.name = "Alice";
alice.monthlyIncome = bob.monthlyIncome;
alice.apartmentExpenses = 30000;
alice.otherExpenses = otherExpenses;
alice.bankDebt = 0;
alice.inflation = bob.inflation;
alice.interestRate = 9;
alice.mortgageInterest = 7;
alice.currentCapital = 1000000;

double aliceTotalCapital = processFunction(&alice, totalMonth);
double bobTotalCapital = processFunction(&bob, totalMonth) + 20000000;

printf("ALICE TOTAL CAPITAL %.2f\n", aliceTotalCapital);
printf("BOB TOTAL CAPITAL: %.2f\n", bobTotalCapital);
return 0;

}