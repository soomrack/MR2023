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
    int has_bought_flat;
    int monthly_expenses;
    Money money_in_bank;    
};


void alice_initialization(struct Person *human)
{
    human->has_bought_flat = false;
    human->money_in_bank = 1 * 1000 * 1000;
    human->monthly_expenses = 30 * 1000 + RENT;
    human->salary = USUAL_SALARY; 
}


void bob_initialization(struct Person *human)
{
    human->has_bought_flat = true;
    human->money_in_bank = 0;
    human->monthly_expenses = 30 * 1000;
    human->salary = USUAL_SALARY; 
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


void salary_indexing(struct Person *human, int month)
{
    if (month  == 1)
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


void try_to_buy_flat(struct Person *human)
{
    if (human->money_in_bank > COST_OF_FLAT && human->has_bought_flat == 0)
        human->money_in_bank -= COST_OF_FLAT, human->has_bought_flat = true; 
}


void print_info(struct Person *Alice, struct Person *Bob)
{
    printf("Alice:\t has_bought_flat = %i\n \t \
money_in_bank = %lli\n \t \
monthly_expenses = %i\n \t \
salary = %i\n\n", Alice->has_bought_flat, Alice->money_in_bank, Alice->monthly_expenses, Alice->salary);

    printf("Bob:\t has_bought_flat = %i\n \t \
money_in_bank = %lli\n \t \
monthly_expenses = %i\n \t \
salary = %i\n\n", Bob->has_bought_flat, Bob->money_in_bank, Bob->monthly_expenses, Bob->salary);
}


void go_to_the_detist(struct Person *human, int year, int month)
{
    if ((year - FIRST_SIMULATION_YEAR) % 10 == 0 && year != FIRST_SIMULATION_YEAR && month == 6)
        human->money_in_bank -= (500 * 1000);
}

void take_a_rest(struct Person *human, int year, int month)
{
    if ((year - FIRST_SIMULATION_YEAR) % 3 == 0 && year != FIRST_SIMULATION_YEAR && month == 6) 
        human->money_in_bank -= human->salary;
}

void simulation(struct Person *Alice, struct Person *Bob)
{
    for (int year = FIRST_SIMULATION_YEAR, month = FIRST_SIMULATION_MONTH;\
    month <= LAST_SIMULATION_MONTH || year < LAST_SIMULATION_YEAR; \
    (month >= 12) ? month = 1, year++ : month++)
    {
    //Alice
        salary_indexing(Alice, month);
        deposite_income(Alice);
        salary_income(Alice);
        take_a_rest(Alice, year, month);
        monthly_expenses(Alice);
        try_to_buy_flat(Alice);
        go_to_the_detist(Alice, year, month);

    //Bob  
        salary_indexing(Bob, month);        
        deposite_income(Bob);        
        salary_income(Bob);         
        monthly_expenses(Bob);
        payment_for_flat(Bob);
        go_to_the_detist(Bob, year, month);

/*
        if (month % 4 == 0) //DEBAG
        {
            printf("Alice: money_in_bank = %lli\t\t", Alice.money_in_bank);
            printf("Bob: money_in_bank = %lli\n", Bob.money_in_bank);
        }         
*/      
    }
    printf("\n\n");
}

int main( void )
{
    struct Person Alice, Bob;

    alice_initialization(&Alice);
    bob_initialization(&Bob);

    print_info(&Alice, &Bob); 
    simulation(&Alice, &Bob);
    print_info(&Alice, &Bob); 

    return 0;    
}