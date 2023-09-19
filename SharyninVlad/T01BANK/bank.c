#include <stdio.h>
#include <math.h>

double year = 20, 
flat = 20000000, 
monthly_expenses = 30000;

int Alice( void )
{
    int i, flag = 0;
    double Alice_flat = flat, 
    salary = 200000 - monthly_expenses, 
    profit = 1000000;
    
    for (i = 1; i <= (year * 12); i++)
    {
        profit = salary + (profit * (1 + 0.09 / 12));
        if (i % 12 == 0)
            Alice_flat *= 1.07;
        if (profit >= Alice_flat && flag == 0)
        {
            profit -= Alice_flat;
            flag++;
        }
    }
    return profit;
}


int Bob( void )
{
    double Bob_flat = flat, 
    salary = 200000 - monthly_expenses, 
    profit = 0, 
    monthly_payment = ((Bob_flat - 1000000) * (0.07 / 12) * (pow((1 + 0.07 / 12), (year * 12)))) / (pow((1 + 0.07 / 12), (year * 12)) - 1);
    int i;

    for (i = 1; i <= (year * 12); i++)
    {
        profit = (salary - monthly_payment) + (profit * (1 + 0.09 / 12)); 
    }
    return profit;
}


void main( void )
{
    printf("Alice earns %i\n", Alice());
    printf("Bob earns %i\n", Bob());
}