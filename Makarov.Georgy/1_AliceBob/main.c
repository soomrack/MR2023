#include <stdio.h>
#include <math.h>

#define APARTMENT_PRICE (20000000 * 100)
#define HOLDING_YEARS 20

struct Holder {
    long int account;  // current amount of stored money
    long int income;  // salary (paid monthly)
    long int outcome;  // apartment rent, mortgage payment, food and communal services (paid monthly)
};

long int mortgage_calculus(const long int *mortgage_debt, const double *mortgage_rate) {
    // Mortgage monthly payment calculus using annuity loan scheme
    double coefficient = *mortgage_rate / (1 - pow(1. + *mortgage_rate, -HOLDING_YEARS * 12));
    long int mortgage_payment = (long int) (coefficient * (double) *mortgage_debt);

    // Mortgage monthly payment output
    printf("Ежемесячная выплата Боба по ипотеке - %ld копеек\n\n", mortgage_payment);

    return mortgage_payment;
}

int main() {
    // Assuming that Bob bought the same apartment Alice wants to buy price-wise
    const long int mortgage_debt = APARTMENT_PRICE - 1000000. * 100;

    const double mortgage_rate = 0.07 / 12;  // monthly mortgage rate
    const double holding_rate = 1. + 0.09 / 12;  // monthly holding rate
    const double inflation_rate = 1.07;  // annual inflation rate

    struct Holder alice, bob;

    long int mortgage_payment = mortgage_calculus(&mortgage_debt, &mortgage_rate);  // mortgage monthly payment calculus

    // Initializing structs
    alice.account = 1000000 * 100;
    bob.account = 0 * 100;
    alice.income = bob.income = 200000 * 100;  // salary
    alice.outcome = (30000 + 15000 + 5000) * 100;  // apartment rent + food + communal services
    bob.outcome = mortgage_payment + (15000 + 5000) * 100;  // mortgage payment + food + communal services

    for (int i = 0; i < HOLDING_YEARS * 12; i++) {
        alice.account = (long int) ((double) alice.account * holding_rate);
        alice.account += alice.income - alice.outcome;

        bob.account = (long int) ((double) bob.account * holding_rate);
        bob.account += bob.income - bob.outcome;
    }

    // By the end of HOLDING_YEARS period Alice buys an apartment with a price that inflated over time
    alice.account -= (long int) ((double) APARTMENT_PRICE * pow(inflation_rate, HOLDING_YEARS));

    // Results output
    printf("Итоговый капитал Алисы - %ld копеек\n", alice.account);
    printf("Итоговый капитал Боба - %ld копеек\n", bob.account);

    return 0;
}