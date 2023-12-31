#include <stdio.h>
#include<string.h>

int const start = 1000 * 1000 * 1000;
int const years = 30;
int const apartment_price = 20 * 1000 * 1000 * 1000;  // kopeiki
int const apartment_fee = 100 * 1000 * 1000;  // kopeiki
int const mortgage_rate = 7;  // %
double const deposit_interest = 0.5; // %

struct hero {
    long capital;
    int income;
    int monthly_expenses;
} hero;

struct hero Alice = {start,  200 * 1000 * 1000,  90 * 1000 * 1000};
struct hero Bob = {start - apartment_fee,  200 * 1000 * 1000,  90 * 1000 * 1000};

int monthly_installment() {
    int monthly_installment = (apartment_price - apartment_fee) * (1 + 0.01 * mortgage_rate) / (years * 12);
    return monthly_installment;
}

long Alices_profit_per_month() {
    Alice.capital = (Alice.capital + Alice.income - Alice.monthly_expenses) * (1 + 0.01 * deposit_interest);
    return Alice.capital;
}

long Bobs_profit_per_month() {
    Bob.capital = (Bob.capital + Bob.income - Bob.monthly_expenses - monthly_installment()) * (1 + 0.01 * deposit_interest);
    return Bob.capital;
}

void output_of_monthly_results() {
    printf("Alice: %d \n", Alice.capital);
    printf("Bob: %d \n", Bob.capital);
}

void total() {
    monthly_installment();
    for (int months = 1; months <= 12 * years; months++)
    {
        Alices_profit_per_month();
        Bobs_profit_per_month();
        output_of_monthly_results();
    }
}

int main() {
    total();
}