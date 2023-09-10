#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct Capital
{
    char * name;
    long monthlyIncome, apartmentExpenses, otherExpenses, bankDebt;
    __uint8_t inflation, interestRate, mortgageInterest;
    double currentCapital;
    // void monthStart(char* name);
    // void monthFinish(char* name);
    // void calculateMortgageFee();
    
};  // struct Capital



void monthOperation(struct Capital * this, int monthNum);
double calcBobApartmentFee(long debt, __uint8_t percent);
double processFunction(struct Capital * this, int totalMonthNum);








