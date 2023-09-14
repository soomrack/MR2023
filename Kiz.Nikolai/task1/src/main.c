#include <math.h>
#include "capital.h"


int main(int argc, char * argv[]) // run this function with args : total amount of months - 1st arg, Bob's and Alice's other expenses - 2nd arg
{
    if (argc != 3)
    {
        printf("Not enough arguments passed into main.\n");
        return 1;  //  pass args when execute!!!
    } 
    int totalMonth = atoi(argv[1]);
    long otherExpenses = (long)atoi(argv[2]);
    Capital bob = {
        .name = "Bob",
        .monthlyIncome = 200 * 1000,  // rubles
        .otherExpenses = otherExpenses,
        .bankDebt = 19 * 1000 * 1000,
        .inflation = 3,
        .interestRate = 9,
        .mortgageInterest = 7,
        .currentCapital = 0,
        };
    bob.apartmentExpenses = calcBobApartmentFee(bob.bankDebt, 
                                        bob.mortgageInterest);  //  defined Bob


    Capital alice = {
        .name = "Alice",
        .monthlyIncome = 200 * 1000,  // rubles
        .apartmentExpenses = 30 * 1000,
        .otherExpenses = otherExpenses,
        .bankDebt = 0,
        .inflation = bob.inflation,
        .interestRate = 9,
        .mortgageInterest = 7,
        .currentCapital = 1000 * 1000
    };  //  defined Alice
    

    long int aliceTotalCapital = processFunction(&alice, totalMonth);  //  calculate Alice total capital after 20 years
    long int bobTotalCapital = processFunction(&bob, totalMonth) 
    + (20 * 1000 * 1000 * pow (1 + bob.inflation/100, 20));  //  calculate Bob capital


    printf("ALICE TOTAL CAPITAL: %lu rubles.\n", aliceTotalCapital);
    printf("BOB TOTAL CAPITAL: %lu rubles.\n", bobTotalCapital);
    printf("Finally, %s earned more by %i rubles.\n", aliceTotalCapital > bobTotalCapital ? "Alice" : "Bob",
                                                             abs(aliceTotalCapital - bobTotalCapital));
    return 0;
}