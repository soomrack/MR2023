#include <stdio.h>
#include <math.h>

#define true 1
#define false 0

const int FIRST_YEAR = 2023;
const int FIRST_MONTH = 9;

const int LAST_YEAR = 2053;
const int LAST_MONTH = 8;

const rent = 25 * 1000;

const int USUAL_SALARY = 200 * 1000;
const float YEAR_DEPOSITE = 0.09;

const int cost_of_flat = 20 * 1000 * 1000; 

typedef struct
{
    int salary;
    int bought_the_flat;
    int monthly_expenses;
    long long int money_in_bank;    
    int payment_for_flat;
}Person;

void Alice_information( Person *human )
{
    human->bought_the_flat = false;
    human->money_in_bank = 1 * 1000 * 1000;
    human->monthly_expenses = 30 * 1000 + rent;
    human->salary = USUAL_SALARY; 
    human->payment_for_flat = 0;
}

void Bob_information( Person *human )
{
    int number_of_years = LAST_YEAR - FIRST_YEAR;
    human->bought_the_flat = true;
    human->money_in_bank = 0;
    human->monthly_expenses = 30 * 1000;
    human->salary = USUAL_SALARY; 
    human->payment_for_flat = ((cost_of_flat - 1000000) * (0.07 / 12) * (pow((1 + 0.07 / 12), (number_of_years * 12)))) / (pow((1 + 0.07 / 12), (number_of_years * 12)) - 1);
}

void Salary_income( Person *human )
{
    human->money_in_bank += (human->salary - human->monthly_expenses - human->payment_for_flat);
}

void Salary_deposite_income( Person *human )
{
    float bonus_persent;
    if (human->money_in_bank >= 5 * 1000 * 1000)
        bonus_persent = 0.01;
    else
        bonus_persent = 0;
    human->money_in_bank *= 1 + (YEAR_DEPOSITE + bonus_persent) / 12;
}

void Status_of_flat( Person *human )
{
    if (human->money_in_bank > cost_of_flat && human->bought_the_flat == 0)
                human->money_in_bank -= cost_of_flat, human->bought_the_flat = true; 
}

void Print( Person *Alice, Person *Bob )
{
    printf("Alice:\t bought_the_flat = %i\n \t money_in_bank = %lli\n \t monthly_expenses = %i\n \t salary = %i\n\n", Alice->bought_the_flat, Alice->money_in_bank, Alice->monthly_expenses, Alice->salary);
    printf("Bob:\t bought_the_flat = %i\n \t money_in_bank = %lli\n \t monthly_expenses = %i\n \t salary = %i\n\n", Bob->bought_the_flat, Bob->money_in_bank, Bob->monthly_expenses, Bob->salary);
}

void Teeth( Person *human )
{
    human->money_in_bank -= (500 * 1000);
}

void main( void )
{
    int i, j = FIRST_MONTH;
    Person Alice, Bob;

    Alice_information(&Alice);
    Bob_information(&Bob);

    Print(&Alice, &Bob);

    for (i = FIRST_YEAR; i <= LAST_YEAR; i++)
    {
        for (; j <= 12; j++)
        {
            Salary_deposite_income(&Alice);
            Salary_deposite_income(&Bob);

            Salary_income(&Alice);
            Salary_income(&Bob);

            Status_of_flat(&Alice);

            if ((i - FIRST_YEAR) % 10 == 0 && i != FIRST_YEAR)
            {
                Teeth(&Alice);
                Teeth(&Bob);
            } 

            if (j % 4 == 0)
            {
                printf("Alice: money_in_bank = %lli\t\t", Alice.money_in_bank);
                printf("Bob: money_in_bank = %lli\n", Bob.money_in_bank);
            }         
            
            if (i == LAST_YEAR && j == LAST_MONTH)
                break;
        }
        j = 1;
    }
    printf("\n\n");
    Print(&Alice, &Bob);
}