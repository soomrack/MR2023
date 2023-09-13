#include <math.h>
#include "capital.h"


int main(int argc, char * argv[]) // run this function with args : total amount of months - 1st arg, their other expenses - 2nd arg
{
    if (argc != 3) return 1;
    int totalMonth = atoi(argv[1]);
    long otherExpenses = (long)atoi(argv[2]);
    struct Capital bob;
    bob.name = "Bob";
    bob.monthlyIncome = 200 * 1000;
    bob.otherExpenses = otherExpenses;
    bob.bankDebt = 19 * 1000 *1000;
    bob.inflation = 3;
    bob.interestRate = 9;
    bob.mortgageInterest = 7;
    bob.currentCapital = 0;
    bob.apartmentExpenses = calcBobApartmentFee(bob.bankDebt, 
                                            bob.mortgageInterest); 

    //  defined Bob

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

    //  defined Alice

    long long int aliceTotalCapital = processFunction(&alice, totalMonth);
    long long int bobTotalCapital = processFunction(&bob, totalMonth) + 20000000 * pow (1 + bob.inflation/100, 20);

    printf("ALICE TOTAL CAPITAL %llu\n", aliceTotalCapital);
    printf("BOB TOTAL CAPITAL: %llu\n", bobTotalCapital);
    return 0;

}