#include <math.h>
#include "capital.h"



void monthOperation(struct Capital *this, int monthNum)
{
    this->currentCapital *= 1 + ((double)(this->interestRate)/100)/12;
    this->currentCapital += this->monthlyIncome;
    this->currentCapital -= this->apartmentExpenses;
    this->currentCapital -= this->otherExpenses;
    if (monthNum + 1 % 12 == 0)
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
    double coef =  (m * pow(1+m, n)) / (pow(1+m, n) - 1);
    return (coef * debt / 12);
}


long int processFunction(struct Capital * this, int totalMonthNum)
{
    for (int i = 0; i < totalMonthNum; i++)
    {
        monthOperation(this, i);
    }
    return this->currentCapital;
}



// int main()
// {
//     printf("Monthly fee: %.3f\n", calcBobApartmentFee(19000000, 7));
//     return 0;    

// }