#include <stdio.h>
#include <math.h>

#define APARTMENT_PRICE 20000000
#define HOLDING_YEARS 20

struct Holder {
    long double account;  // current amount of stored money
    double income;  // salary (paid monthly)
    double outcome;  // apartment rent, mortgage payment, food and communal services (paid monthly)
};

double mortgage_calculus(double mortgage_debt, double mortgage_rate) {
    // Mortgage monthly payment calculus using annuity loan scheme
    double coefficient = mortgage_rate / (1 - pow(1 + mortgage_rate, -HOLDING_YEARS * 12));
    double mortgage_payment = coefficient * mortgage_debt;

    // Mortgage monthly payment output
    printf("Ежемесячная выплата Боба по ипотеке - %.2f рублей\n\n", mortgage_payment);

    return mortgage_payment;
}

int main() {
    // Assuming that Bob bought the same apartment Alice wants to buy price-wise
    double mortgage_debt = APARTMENT_PRICE - 1000000.;

    const double mortgage_rate = 0.07 / 12;  // monthly mortgage rate
    const double holding_rate = 1. + 0.09 / 12;  // monthly holding rate
    const double inflation_rate = 1.07;  // annual inflation rate

    struct Holder alice, bob;

    double mortgage_payment = mortgage_calculus(mortgage_debt, mortgage_rate);  // mortgage monthly payment calculus

    // Initializing structs
    alice.account = 1000000.;
    bob.account = 0.;
    alice.income = bob.income = 200000.;  // salary
    alice.outcome = 30000. + 15000. + 5000.;  // apartment rent + food + communal services
    bob.outcome = mortgage_payment + 15000. + 5000.;  // mortgage payment + food + communal services

    for (int i = 0; i < HOLDING_YEARS * 12; i++) {
        alice.account *= holding_rate;
        alice.account += alice.income - alice.outcome;

        bob.account *= holding_rate;
        bob.account += bob.income - bob.outcome;
    }

    // By the end of HOLDING_YEARS period Alice buys an apartment with a price that inflated over time
    alice.account -= APARTMENT_PRICE * pow(inflation_rate, HOLDING_YEARS);

    // Results output
    printf("Итоговый капитал Алисы - %.2Lf рублей\n", alice.account);
    printf("Итоговый капитал Боба - %.2Lf рублей\n", bob.account);

    return 0;
}