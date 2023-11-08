#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define DEFAULT_PARAMS Person * this, const int year_num, const enum Months month_num

typedef long int money;  // ₽ 

typedef struct {
    char * name;
    /*
    variables that describes: person's payback, person's expenses for apartment (rent or mortgage), 
    person's other expenses (groceries, utility bills) and bank debt (for Bob only, for alice = 0)
    */
    money  monthly_income, apartment_expenses, other_expenses, bank_debt;   
    const uint8_t inflation, interest_rate, mortgage_interest;
    money current_capital;  //  currentCapital will increase from month to month, thats a main variable in this task
} Person;  // struct Person, defines a person (Alice or Bob)


enum Months {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};  // enum Months to easily deal with them while writing code


Person init_bob();  //  bob initialization function
Person init_alice();  //  alice initialization function
money bob_apartment_inflation_increasing();  // adds to bob.current_capital price of his asset modified with inflation after mortgage finished
void bob_inflation_processor(Person * this, const enum Months month_num);  //  bob inflation processor
void alice_inflation_processor(Person * this, const enum Months month_num);  //  alice inflation processor
void bob_payback_processor(DEFAULT_PARAMS);  //  bob salary
void alice_payback_processor(DEFAULT_PARAMS);  //  alice salary
void bob_expenses_processor(DEFAULT_PARAMS);  //  bob expenses
void alice_expenses_processor(DEFAULT_PARAMS);  //  alice expenses
money bob_unaccounted_expenses(DEFAULT_PARAMS);
money alice_unaccounted_expenses(DEFAULT_PARAMS);
void bob_month_operation(DEFAULT_PARAMS);  // monthly routine, calculating all the operations with bob's bank account
void alice_month_operation(DEFAULT_PARAMS);  // monthly routine, calculating all the operations with alice's bank account 
void bank_deposit_income(Person * this);
double calculate_bob_apartment_fee(money debt, const uint8_t percent);  //  function calculate Bob's mortgage monthly fee
void process_model(Person * alice, Person * bob);  //  processing function
// money * const start_model(Person * alice, Person * bob, const int total_year_num, const enum Months starting_month);  //  no need
void handle_result(Person * alice, Person * bob);


