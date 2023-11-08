#include <math.h>
#include "bankModel.h"


#define BOB_APARTMENT_COST 20 * 1000 * 1000  //  20 mil rubles
#define BOB_APARTMENT_FIRST_PAYMENT 1000 * 1000  //  1 mil rubles
#define BOB_MORTGAGE_INTEREST 7  //  means 7%
#define OTHER_EXPENSES 20000
#define INFLATION 3  //  means 3%
#define INTEREST_RATE 3  //  means 9%


/*
Lets say that our model is starting at SEPTEMBER 2023.
That means that last mortgage payment by bob will be made at SEPTEMBER 2043.
Total number of months - 240
Total number of years - 20
*/


Person init_bob() {
    Person temp = {
        .name = "Bob",
        .monthly_income = 200 * 1000,
        .other_expenses = OTHER_EXPENSES,
        .bank_debt = BOB_APARTMENT_COST - BOB_APARTMENT_FIRST_PAYMENT,
        .inflation = INFLATION,
        .interest_rate = INTEREST_RATE,  //  means 9%
        .mortgage_interest = BOB_MORTGAGE_INTEREST,
        .current_capital = 0,
    };
    temp.apartment_expenses = calculate_bob_apartment_fee(temp.bank_debt,
                                temp.mortgage_interest);
    return temp;
}


Person init_alice() {
    Person temp = {
    .name = "Alice",
    .monthly_income = 200 * 1000,
    .apartment_expenses = 35 * 1000,
    .other_expenses = OTHER_EXPENSES,
    .bank_debt = 0,
    .inflation = INFLATION,
    .interest_rate = INTEREST_RATE,  //  means 9%
    .mortgage_interest = 0,
    .current_capital = 1000 * 1000,
    };
    return temp;
}


void bob_payback_processor(DEFAULT_PARAMS) {

    if (year_num == 2024 && month_num == NOVEMBER)
    {
        this->monthly_income += 10 * 1000;
    }
    else if (year_num == 2028 && month_num == JUNE) {  //  got fired and decided to take a break
        this->monthly_income = 0;
    }

    else if (year_num == 2028 && month_num == AUGUST) {  //  new position - new salary
        this->monthly_income = 250 * 1000;
    }
    else if (year_num == 2035 && month_num == MARCH) {
        this->monthly_income -= 40 * 1000;
    } 
    this->current_capital += this->monthly_income;
}


void alice_payback_processor(DEFAULT_PARAMS) {

    if (year_num == 2024 && month_num == NOVEMBER)
    {
        this->monthly_income -= 10 * 1000;
    }
    else if (year_num == 2028 && month_num == JUNE) {
        this->monthly_income = 180 * 1000;
    }

    else if (year_num == 2035 && month_num == MARCH) {
        this->monthly_income += 80 * 1000;
    } 
    this->current_capital += this->monthly_income;
}


money bob_unaccounted_expenses(DEFAULT_PARAMS) {
    if (year_num % 2 == 0 && month_num == AUGUST)  // bob going to vacation every 2 years in august
        return 200 * 1000;
    else if (year_num == 2035 && month_num == FEBRUARY)  // bob's brother got sick and he needed surgery
        return 120 * 1000;
    return 0;
}


void bob_expenses_processor(DEFAULT_PARAMS) {
    this->current_capital -= this->apartment_expenses;  
    this->current_capital -= this->other_expenses;
    this->current_capital -= bob_unaccounted_expenses(this, month_num, year_num);  
}


money alice_unaccounted_expenses(DEFAULT_PARAMS) {
    if (month_num == FEBRUARY)  // alice is asthmatic and need to go to health resort every winter
        return 100 * 1000;
    else if (year_num == 2028 && month_num == OCTOBER)  // alice bought a dog in october 2028
        return 40 * 1000;
    return 0;
}


void alice_expenses_processor(DEFAULT_PARAMS) {
    this->current_capital -= this->apartment_expenses;  
    this->current_capital -= this->other_expenses;
    this->current_capital -= alice_unaccounted_expenses(this, month_num, year_num);  
}


void bank_deposit_income(Person * this) {
    double coef = 1 + ((double)(this->interest_rate)/100)/12;  // bank interest coefficient
    this->current_capital *= coef;  // bank deposit income

}


void bob_inflation_processor(Person * this, const enum Months month_num) {
    if (month_num == DECEMBER) {  //  inflation changes
        this->monthly_income *= (1+ (double)(this->inflation)/200); // salary is being indexed only at half of inflation level
        this->other_expenses *= (1+ (double)(this->inflation)/100);
    }
}


void alice_inflation_processor(Person * this, const enum Months month_num) {
    if (month_num == DECEMBER) {  //  inflation changes
        this->monthly_income *= (1+ (double)(this->inflation)/200); // salary is being indexed only at half of inflation level
        this->other_expenses *= (1+ (double)(this->inflation)/100);
        this->apartment_expenses *= (1+ (double)(this->inflation)/100);
    }
}


void bob_month_operation(DEFAULT_PARAMS) {
    bank_deposit_income(this);
    bob_payback_processor(this, year_num, month_num);
    bob_expenses_processor(this, year_num, month_num);
    bob_inflation_processor(this, month_num);
    if (year_num == 2043 && month_num == SEPTEMBER) {
        this->current_capital += bob_apartment_inflation_increasing();  // the end of the mortgage
    }
};


void alice_month_operation(DEFAULT_PARAMS) {
    bank_deposit_income(this);
    alice_payback_processor(this, year_num, month_num);
    alice_expenses_processor(this, year_num, month_num);
    alice_inflation_processor(this, month_num);
}


double calculate_bob_apartment_fee(money debt, const __uint8_t percent)
{   
    double m = (1 +  (double)(percent)/100)/12;  
    uint8_t n = 240; // number of month
    double coef =  (m * pow(1+m, n)) / (pow(1+m, n) - 1); // annuity coefficient
    return (coef * debt / 12);  //  monthly fee
}


money bob_apartment_inflation_increasing() {
    return BOB_APARTMENT_COST * pow (1 + (double)INFLATION/100, 20);
}


void process_model(Person * alice, Person * bob) {   
    int this_year = 2023;
    int total_month_num = 240;
    int month_counter = SEPTEMBER;
    while (month_counter <= total_month_num + SEPTEMBER)
    {
        enum Months month_number = month_counter % 12;
        month_number = month_number % 12 == 0 ? DECEMBER : month_number;
        bob_month_operation(bob, this_year, month_number);
        alice_month_operation(alice, this_year, month_number);
        if (month_number == 12) {
            this_year++;
        }
        month_counter++;
    }
}


// money * const start_model(Person * alice, Person * bob, const int total_year_num, const enum Months starting_month) {
//     processing_function(alice, bob, total_year_num, starting_month);
//     // money * const capital_array = (money*)malloc(2 * sizeof(money));
//     // capital_array[0] = alice->current_capital;
//     // capital_array[1] = bob->current_capital;
//     // return capital_array;
// }


void handle_result(Person * alice, Person * bob) {
    const money alice_total_capital = alice->current_capital;
    const money bob_total_capital = bob->current_capital;
    printf("ALICE TOTAL CAPITAL: %lu rubles.\n", alice_total_capital);
    printf("BOB TOTAL CAPITAL: %lu rubles.\n", bob_total_capital);
    printf("Finally, %s earned more by %i rubles.\n", alice_total_capital > bob_total_capital ? "Alice" : "Bob",
                                                             abs(alice_total_capital - bob_total_capital));  
}
