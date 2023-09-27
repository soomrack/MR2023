#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef long int money;  // ₽ 

typedef struct {
    char * name;
    /*
    variables that describes: person's payback, person's expenses for apartment (rent or mortgage), 
    person's other expenses (groceries, utility bills) and bank debt (for Bob only, for alice = 0)
    */
    money  monthlyIncome, apartmentExpenses, otherExpenses, bankDebt;   
    const __uint8_t inflation, interestRate, mortgageInterest;
    money currentCapital;  //  currentCapital will increase from month to month, thats a main variable in this task
} Capital;  // struct Capital, defines a person (Alice or Bob)



void inflationProcessor(Capital * this, const int monthNum);
void expensesProcessor(Capital * this, const int monthNum);
void bankDepositIncome(Capital * this);
void paybackProcessor(Capital * this, const int yearNum, const int monthNum);
void monthOperation(Capital * this, const int yearNum, const int monthNum);  // monthly routine, calculate capital changes every month 
double calcBobApartmentFee(money debt, const __uint8_t percent);  //  function calculate Bob's mortgage monthly fee
money processFunction(Capital * this, const int totalYearNum); // main process function with lopp
void mainFunction(Capital * alice, Capital * bob, const int totalYearNum);








