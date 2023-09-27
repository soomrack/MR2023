#include <math.h>
#include "capital.h"
#include <stdint.h>


void bankDepositIncome(Capital * this)
{
    double coef = 1 + ((double)(this->interestRate)/100)/12;
    this->currentCapital *= coef;  // bank deposit income

}

void paybackProcessor(Capital * this, const int yearNum, const int monthNum)
{
    if (strcmp(this->name, "Alice") == 0)
    {
        if (yearNum == 2028 && monthNum == 4)
        {
            this->monthlyIncome -= 10000;

        }
        else if (yearNum == 2029 && monthNum == 9)
        {
            this->monthlyIncome += 23000;
        }
    }

    this->currentCapital += this->monthlyIncome;

}   

void expensesProcessor(Capital * this, const int monthNum)
{
    if (strcmp(this->name, "Bob") == 0 && monthNum == 8)
    {
        this->currentCapital -= 100000; // Bob's is going on vacation in August every year
    }
    else if (strcmp(this->name, "Alice") == 0 && monthNum == 1)
    {
        this->currentCapital -= 120000; // Alice going to the ski resort every winter
    }
    this->currentCapital -= this->apartmentExpenses;
    this->currentCapital -= this->otherExpenses;
}


void inflationProcessor(Capital * this, const int monthNum)
{
    if (monthNum == 12)  //  inflation changes
    {
        this->monthlyIncome *= (1+ (double)(this->inflation)/200); // we live in Russia, so payback is being indexed only on half of inflation level
        this->otherExpenses *= (1+ (double)(this->inflation)/100);
        if (strcmp(this->name, "Alice") == 0)
        {
            this->apartmentExpenses *= (1+ (double)(this->inflation)/100);  // rent is rising due to inflation
        }
    }
}

void monthOperation(Capital * this, const int yearNum, const int monthNum)
{
    bankDepositIncome(this);
    paybackProcessor(this, yearNum, monthNum);
    expensesProcessor(this, monthNum);
    inflationProcessor(this, monthNum);

}; // mothOperation function



double calcBobApartmentFee(money debt, const __uint8_t percent)
{   
    double m = (1 +  (double)(percent)/100)/12;  
    __uint8_t n = 240; // number of month
    double coef =  (m * pow(1+m, n)) / (pow(1+m, n) - 1); // annuity coefficient
    return (coef * debt / 12);  //  monthly fee
}


long int processFunction(Capital * this, const int totalYearNum)
{   
    int16_t thisYear = 2023;
    int16_t totalMonthNum = totalYearNum * 12;
    for (int i = 1, j = 1; i <= 12, j <= totalYearNum; i++)
    {
        monthOperation(this, thisYear, i);
        if (i == 12)
        {
            i = 0;
            thisYear++;
            j++;
        }
    }
    return this->currentCapital;
}



void mainFunction(Capital * alice, Capital * bob, const int totalYearNum)
{

    money aliceTotalCapital = processFunction(alice, totalYearNum);  //  calculate Alice total capital after 20 years
    money bobTotalCapital = processFunction(bob, totalYearNum)
    + (20 * 1000 * 1000 * pow (1 + (double)bob->inflation/100, 20));  //  calculate Bob capital

    printf("ALICE TOTAL CAPITAL: %lu rubles.\n", aliceTotalCapital);
    printf("BOB TOTAL CAPITAL: %lu rubles.\n", bobTotalCapital);
    printf("Finally, %s earned more by %i rubles.\n", aliceTotalCapital > bobTotalCapital ? "Alice" : "Bob",
                                                             abs(aliceTotalCapital - bobTotalCapital));
}