#include <stdio.h>
#include <math.h>

typedef struct {
    long long unsigned int bank_balance;
    int income;
    int expenses;
} Person;

void initialize_person(Person* person, long long unsigned int balance, int monthly_income, int monthly_expenses) {
    person->bank_balance = balance;
    person->income = monthly_income;
    person->expenses = monthly_expenses;
}

void calculate_alice_income(Person* alice, int current_month, int current_year) {
    alice->bank_balance *= 1 + 9.0 / 1200.0;
    if ((current_month == 6 || current_month == 7) && current_year == 2035) {
        alice->income = 0;
    }
    if (current_month == 8 && current_year == 2035) {
        alice->income = 200000;
    }
}

void calculate_alice_expenses(Person* alice, int current_month, int current_year) {
    alice->expenses *= 1 + 7.0 / 1200.0;
    if (current_month == 12 && current_year == 2035) {
        alice->expenses += 1000;
    }
}

double compute_alice_bank_balance(Person* alice) {
    int months = 240;
    for (int i = 0; i < months; i++) {
        int current_month = i % 12 + 1;
        int current_year = 2023 + i / 12;
        calculate_alice_income(alice, current_month, current_year);
        calculate_alice_expenses(alice, current_month, current_year);
        alice->bank_balance += alice->income - alice->expenses;
    }
    return alice->bank_balance;
}

int calculate_monthly_mortgage_payment(int principal_amount, float annual_interest_rate, int num_of_payments) {
    float monthly_interest_rate = annual_interest_rate / 12.0;
    int monthly_payment = principal_amount * monthly_interest_rate * pow(1 + monthly_interest_rate, num_of_payments) / (pow(1 + monthly_interest_rate, num_of_payments) - 1);
    return monthly_payment;
}

void calculate_bob_income(Person* bob, int current_month, int current_year) {
    bob->bank_balance *= 1 + 9.0 / 1200.0;
}

void calculate_bob_travel_expenses(Person* bob, int month, int year) {
    if (year == 2035 && month == 7) {
        bob->expenses += 70000;
}

void calculate_bob_living_expenses(Person* bob, int month, int year) {
    bob->expenses += 5000; 
}

void calculate_bob_transportation_expenses(Person* bob, int month, int year) {
    bob->expenses += 500;
} 

void calculateBobExpenses(Person* bob, int month, int year) {
    calculate_bob_living_expenses(bob, month, year);
    calculate_bob_transportation_expenses(bob, month, year);
}

long long unsigned int compute_bob_bank_balance(Person* bob) {
    float annual_interest_rate = 7.0 / 12.0 / 1200.0;
    int principal_amount = 19000000;
    int num_of_payments = 240;
    int mortgage_payment = calculate_monthly_mortgage_payment(principal_amount, annual_interest_rate, num_of_payments);
    int months = 240;
    for (int i = 0; i < months; i++) {
        int current_month = i % 12 + 1;
        int current_year = 2023 + i / 12;
        calculate_bob_income(bob, current_month, current_year);
        calculate_bob_expenses(bob, current_month, current_year);
        bob->bank_balance += bob->income - mortgage_payment - bob->expenses;
    }
    bob->bank_balance *= 1 + 9.0 / 1200.0;
    bob->bank_balance += bob->income - (principal_amount - mortgage_payment * 239);
    return bob->bank_balance;
}

void print_simulation_results(Person* alice, Person* bob) {
    printf("\n\n\t\tSimulation Results\n");
    printf("\t\t==================\n");
    printf("\t\tAlice's Bank Balance: %llu\n", alice->bank_balance);
    printf("\t\tBob's Bank Balance: %llu\n", bob->bank_balance);
    printf("\t\t==================\n\n\n");
}

int main() {

    Person alice;
    initialize_person(&alice, 1000000, 200000, 60000);
    Person bob;
    initialize_person(&bob, 0, 200000, 30000);
    compute_alice_bank_balance(&alice);
    compute_bob_bank_balance(&bob);
    printSimulationResults(&alice, &bob);
    return 0;
}
