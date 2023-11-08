#include <stdio.h>
#include <math.h>

#define true 1
#define false 0

const int FIRST_SIMULATION_YEAR = 2023;
const int FIRST_SIMULATION_MONTH = 9;

const int LAST_SIMULATION_YEAR = 2053;
const int LAST_SIMULATION_MONTH = 8;

const int RENT = 25 * 1000;

const int USUAL_SALARY = 200 * 1000;
const float YEAR_DEPOSITE = 0.09;

const int COST_OF_FLAT = 20 * 1000 * 1000; 

typedef long long int Money;

struct Person{
    int salary;
    int bought_the_flat;
    int monthly_expenses;
    Money money_in_bank;    
};


void humans_initialization(struct Person *Alice, struct Person *Bob)
{
    Alice->bought_the_flat = false;
    Alice->money_in_bank = 1 * 1000 * 1000;
    Alice->monthly_expenses = 30 * 1000 + RENT;
    Alice->salary = USUAL_SALARY; 

    Bob->bought_the_flat = true;
    Bob->money_in_bank = 0;
    Bob->monthly_expenses = 30 * 1000;
    Bob->salary = USUAL_SALARY;
}


void monthly_expenses(struct Person *human)
{
    human->money_in_bank -= human->monthly_expenses;
}


void payment_for_flat(struct Person *human)
{
    int number_of_years = LAST_SIMULATION_YEAR - FIRST_SIMULATION_YEAR;

    human->money_in_bank -= ((COST_OF_FLAT - 1000000) * (0.07 / 12) * (pow((1 + 0.07 / 12), \
    (number_of_years * 12)))) / (pow((1 + 0.07 / 12), (number_of_years * 12)) - 1);
}


void salary_income(struct Person *human)
{
    human->money_in_bank += human->salary;
}


void salary_indexing(struct Person *human)
{
    human->salary *= 1.02;
}


void deposite_income(struct Person *human)
{
    float bonus_persent;
    if (human->money_in_bank >= 5 * 1000 * 1000)
        bonus_persent = 0.01;
    else
        bonus_persent = 0;
    human->money_in_bank *= 1 + (YEAR_DEPOSITE + bonus_persent) / 12;
}


void status_of_flat(struct Person *human)
{
    if (human->money_in_bank > COST_OF_FLAT && human->bought_the_flat == 0)
        human->money_in_bank -= COST_OF_FLAT, human->bought_the_flat = true; 
}


void print_results(struct Person *Alice, struct Person *Bob)
{
    printf("Alice:\n \
            \r bought_the_flat = %i\n \
            \r money_in_bank = %lli\n \
            \r monthly_expenses = %i\n \
            \r salary = %i\n\n", 
            Alice->bought_the_flat, Alice->money_in_bank,
            Alice->monthly_expenses, Alice->salary);

    printf("Bob:\n \
            \r bought_the_flat = %i\n \
            \r money_in_bank = %lli\n \
            \r monthly_expenses = %i\n \
            \r salary = %i\n", 
            Bob->bought_the_flat, Bob->money_in_bank,
            Bob->monthly_expenses, Bob->salary);
}


void go_to_the_detist(struct Person *human)
{
    human->money_in_bank -= (500 * 1000);
}


void business_simulation(void)
{
    int year = FIRST_SIMULATION_YEAR, month = FIRST_SIMULATION_MONTH;
    struct Person Alice, Bob;

    humans_initialization(&Alice, &Bob);

    printf("Initial setup >>>\n");
    print_results(&Alice, &Bob);
    
    
    for (; month <= LAST_SIMULATION_MONTH || year < LAST_SIMULATION_YEAR; (month >= 12) ? month = 1, year++ : month++)
    {
        if (month  == 1)
        {
            salary_indexing(&Alice);
            salary_indexing(&Bob);
        }

        deposite_income(&Alice);
        deposite_income(&Bob);

        salary_income(&Alice);
        salary_income(&Bob);

        monthly_expenses(&Alice);
        monthly_expenses(&Bob);

        payment_for_flat(&Bob);

        status_of_flat(&Alice);

        if ((year - FIRST_SIMULATION_YEAR) % 10 == 0 && year != FIRST_SIMULATION_YEAR) 
        {
            go_to_the_detist(&Alice);
            go_to_the_detist(&Bob);
        } 
    
    }

    printf("\n\nSimulation result >>>\n");
    print_results(&Alice, &Bob); 
}

void main( void )
{
   business_simulation();
}