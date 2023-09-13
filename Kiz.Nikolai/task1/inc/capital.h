#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct Capital
{
    char * name;
    /*
    variables that describes: person's payback, person's expenses for apartment (rent or mortgage), 
    person's other expenses (groceries, utility bills) and bank debt (for Bob only, for alice = 0)
    */
    long int monthlyIncome, apartmentExpenses, otherExpenses, bankDebt;   
    __uint8_t inflation, interestRate, mortgageInterest;
    long int currentCapital;  //  currentCapital will increase from month to month, thats a main variable in this task
 
};  // struct Capital, defines a person (Alice or Bob)



void monthOperation(struct Capital * this, int monthNum);  // monthly routine, calculate capital changes every month 
double calcBobApartmentFee(long debt, __uint8_t percent);  //  function calculate Bob's mortgage monthly fee
long int processFunction(struct Capital * this, int totalMonthNum); // main process function with lopp








