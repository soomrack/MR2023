#include <math.h>
#include "capital.h"


int main(int argc, char * argv[]) // run this function with args : total amount of months - 1st arg, Bob's and Alice's other expenses - 2nd arg
{
    if (argc != 3)
    {
        printf("Not enough arguments passed into main.\n");
        return 1;  //  pass args when execute!!!
    } 
    const  int totalYears = atoi(argv[1]);
    const money otherExpenses = (long)atoi(argv[2]);
    Capital bob = {
        .name = "Bob",
        .monthlyIncome = 200 * 1000,  // rubles
        .otherExpenses = otherExpenses,
        .bankDebt = 19 * 1000 * 1000,
        .inflation = 5,
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
    

    mainFunction(&alice, &bob, totalYears);
    return 0;
}