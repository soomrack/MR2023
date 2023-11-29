#include <stdio.h>
#include <math.h>

typedef struct {
    long long unsigned int bank_balance;
    int income;
    int expenses;
} Person;

void initAlice(Person* alice, long long unsigned int bank_balance, int income, int expenses) {
    alice->bank_balance = bank_balance;
    alice->income = income;
    alice->expenses = expenses;
}

void initBob(Person* bob, long long unsigned int bank_balance, int income, int expenses) {
    bob->bank_balance = bank_balance;
    bob->income = income;
    bob->expenses = expenses;
}

void calculateAliceIncome(Person* alice, int month, int year) {
    alice->bank_balance *= 1 + 9.0 / 1200.0;

    if ((month == 6 || month == 7) && year == 2035) {
        alice->income = 0;
    }
    if (month == 8 && year == 2035) {
        alice->income = 200000;
    }
}

void calculateAliceExpenses(Person* alice, int month, int year) {
    alice->expenses *= 1 + 7.0 / 1200.0;

    if (month == 12 && year == 2035) {
        alice->expenses += 1000;
    }
}

void calculateBobIncome(Person* bob, int month, int year) {
    bob->bank_balance *= 1 + 9.0 / 1200.0;
}

long long calculate_monthly_mortgage_payment(long long principal, float annual_interest_rate, int num_of_payments) {
    float monthly_interest_rate = annual_interest_rate / 12.0;
    long long monthly_payment = principal * monthly_interest_rate * pow(1 + monthly_interest_rate, num_of_payments) /
                         (pow(1 + monthly_interest_rate, num_of_payments) - 1);
    return monthly_payment;
}

void calculateBobLivingExpenses(Person* bob, int month, int year) {
    bob->expenses += 2000; // Примерная сумма на жилье.
}

void calculateBobTransportationExpenses(Person* bob, int month, int year) {
    bob->expenses += 500; // Примерная сумма на транспорт.
}

void calculateBobEntertainmentExpenses(Person* bob, int month, int year) {
    bob->expenses += 300; // Примерная сумма на развлечения.
}

void calculateBobEducationExpenses(Person* bob, int month, int year) {
    if (year == 2035 && month >= 9) {
        bob->expenses += 1000; // Примерная сумма на образование.
    }
}

void calculateBobMedicalExpenses(Person* bob, int month, int year) {
    if (year == 2035 && month <= 3) {
        bob->expenses += 500; // Примерная сумма на медицину.
    }
}

void calculateBobVacationExpenses(Person* bob, int month, int year) {
    if (year == 2035 && month == 7) {
        bob->expenses += 3000; // Примерная сумма на отпуск.
    }
}

void calculateBobExpenses(Person* bob, int month, int year) {
    calculateBobLivingExpenses(bob, month, year);
    calculateBobTransportationExpenses(bob, month, year);
    calculateBobEntertainmentExpenses(bob, month, year);
    calculateBobEducationExpenses(bob, month, year);
    calculateBobMedicalExpenses(bob, month, year);
    calculateBobVacationExpenses(bob, month, year);
}

void calculateAliceBankBalance(Person* alice) {
    int months = 240;
    for (int k = 0; k < months; k++) {
        int month = k % 12 + 1;
        int year = 2023 + k / 12;

        calculateAliceIncome(alice, month, year);
        calculateAliceExpenses(alice, month, year);

        alice->bank_balance += alice->income - alice->expenses;
    }
}

void calculateBobBankBalance(Person* bob) {
    float annual_interest_rate = 7.0 / 12.0 / 1200.0;
    long long principal = 19000000;
    int num_of_payments = 240;
    long long mortgage = calculate_monthly_mortgage_payment(principal, annual_interest_rate, num_of_payments);
    long long initial_balance = bob->bank_balance;

    for (int k = 0; k < 240; k++) {
        int month = k % 12 + 1;
        int year = 2023 + k / 12;

        calculateBobIncome(bob, month, year);
        calculateBobExpenses(bob, month, year);

        bob->bank_balance += bob->income - mortgage - bob->expenses;
    }

}

void print_result(Person* alice, Person* bob) 
{
    printf("\n\n\t\tResult of simulation\n");
    printf("\t\t===========================\n");
    printf("\t\tAlice Bank: %llu\n", alice->bank_balance);
    printf("\t\tBob Bank: %llu\n", bob->bank_balance);
    printf("\t\t===========================\n\n\n");
}

int main() {
    Person alice;
    initAlice(&alice, 1000000, 200000, 60000);
    Person bob;
    initBob(&bob, 0, 200000, 30000);

    calculateAliceBankBalance(&alice);
    calculateBobBankBalance(&bob);

    print_result(&alice, &bob);

    return 0;
}
