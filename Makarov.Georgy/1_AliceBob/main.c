#include <stdio.h>
#include <math.h>

typedef long long int kopeck;

const kopeck APARTMENT_PRICE = 20 * 1000 * 1000 * 100;
const int HOLDING_MONTHS = 20 * 12;

const double MORTGAGE_RATE = 0.06, HOLDING_RATE = 0.09, INFLATION_RATE = 0.07;

struct Holder {
    kopeck capital;
    kopeck earnings;
    kopeck apartment_expenses;
    kopeck food_expenses;
    kopeck communal_expenses;
};


void print_mortgage_payment(const kopeck *mortgage_payment) {
    printf("Ежемесячная выплата Боба по ипотеке - %lld копеек\n\n", *mortgage_payment);
}


void print_holding_results(struct Holder *Alice, struct Holder *Bob) {
    printf("Итоговый капитал Алисы - %lld копеек\n", Alice->capital);
    printf("Итоговый капитал Боба - %lld копеек\n", Bob->capital);
}


/**
 * @brief Calculate monthly mortgage payment using annuity loan scheme (https://www.raiffeisen.ru/wiki/kak-rasschitat-annuitetnyj-platezh)
 */
kopeck calculate_mortgage_payment(const kopeck mortgage_debt) {
    double coefficient = MORTGAGE_RATE / (12 * (1 - pow(1. + MORTGAGE_RATE / 12, -HOLDING_MONTHS)));
    kopeck mortgage_payment = (kopeck) (coefficient * (double) mortgage_debt);

    print_mortgage_payment(&mortgage_payment);

    return mortgage_payment;
}


/**
 * @brief Insert holding data for both Alice and Bob into Holder struct instances
 */
void initialize_holders(struct Holder *Alice, struct Holder *Bob) {
    kopeck alice_starting_capital = 1000 * 1000 * 100, bob_starting_capital = 0 * 100;
    Alice->capital = alice_starting_capital;
    Bob->capital = bob_starting_capital;

    kopeck earnings = 200 * 1000 * 100;
    Alice->earnings = Bob->earnings = earnings;

    // By the start of the holding period Bob pays initially so his monthly mortgage payment decreases
    const kopeck bob_mortgage_initial_payment = 1000 * 1000 * 100;
    kopeck alice_apartment_expenses = 30 * 1000 * 100,
            bob_apartment_expenses = calculate_mortgage_payment(APARTMENT_PRICE - bob_mortgage_initial_payment);
    Alice->apartment_expenses = alice_apartment_expenses;
    Bob->apartment_expenses = bob_apartment_expenses;

    kopeck food_expenses = 15 * 1000 * 100;
    Alice->food_expenses = Bob->food_expenses = food_expenses;

    kopeck communal_expenses = 5 * 1000 * 100;
    Alice->communal_expenses = Bob->communal_expenses = communal_expenses;
}


/**
 * @brief Calculate Alice's and Bob's capitals after the holding period
 */
void calculate_holdings(struct Holder *Alice, struct Holder *Bob) {
    for (int month = 0; month < HOLDING_MONTHS; month++) {
        Alice->capital = (kopeck) ((double) Alice->capital * (1. + HOLDING_RATE / 12));
        Alice->capital += Alice->earnings;
        Alice->capital -= Alice->apartment_expenses;
        Alice->capital -= Alice->food_expenses;
        Alice->capital -= Alice->communal_expenses;

        Bob->capital = (kopeck) ((double) Bob->capital * (1. + HOLDING_RATE / 12));
        Bob->capital += Bob->earnings;
        Bob->capital -= Bob->apartment_expenses;
        Bob->capital -= Bob->food_expenses;
        Bob->capital -= Bob->communal_expenses;
    }

    // By the end of the holding period Alice buys an apartment with a price that inflated over time
    Alice->capital -= (kopeck) ((double) APARTMENT_PRICE * pow(1. + INFLATION_RATE, (int) (HOLDING_MONTHS / 12)));

    print_holding_results(Alice, Bob);
}


int main() {
    struct Holder Alice, Bob;

    initialize_holders(&Alice, &Bob);

    calculate_holdings(&Alice, &Bob);

    return 0;
}