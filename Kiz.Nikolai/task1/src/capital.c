#include <math.h>
#include "capital.h"


void monthOperation(struct Capital *this, int monthNum)
{
    this->currentCapital *= 1 + ((double)(this->interestRate)/100)/12;  // bank deposit income
    this->currentCapital += this->monthlyIncome;  // payback
    this->currentCapital -= this->apartmentExpenses;  //  rent 
    this->currentCapital -= this->otherExpenses; // other
    if (monthNum + 1 % 12 == 0)  //  inflation changes
    {
        this->monthlyIncome *= (1+ (double)(this->inflation)/100);
        this->otherExpenses *= (1+ (double)(this->inflation)/100);
        if (this->name == "Alice")
        {
            this->apartmentExpenses *= (1+ (double)(this->inflation)/100);
        }
    }
}; // mothOperation function


double calcBobApartmentFee(long debt, __uint8_t percent)
{   
    double m = (1 +  (double)(percent)/100)/12;  
    __uint8_t n = 240; // number of month
    double coef =  (m * pow(1+m, n)) / (pow(1+m, n) - 1); // annuity coefficient
    return (coef * debt / 12);  //  monthly fee
}


long int processFunction(struct Capital * this, int totalMonthNum)
{
    for (int i = 0; i < totalMonthNum; i++)
    {
        monthOperation(this, i);
    }
    return this->currentCapital;
}



