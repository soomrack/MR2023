#include <stdio.h>
#include <math.h>


typedef long long int kopeck;

const kopeck APARTMENT_PRICE = 20 * 1000 * 1000 * 100;
const kopeck CAPITAL_LIMIT = 20 * 1000 * 1000 * 100;

const double MORTGAGE_RATE = 0.06;
const double INFLATION_RATE = 0.07;
const double HOLDING_RATE = 0.09;
const double LIMITED_HOLDING_RATE = 0.03;
const double OVERPRICE = 0.3;

const int STARTING_MONTH = 3 - 1;  // e.g. 3 for March
const int HOLDING_MONTHS = 20 * 12;

const int UNEMPLOYMENT_MONTH = 44 - 1;
const int EMPLOYMENT_MONTH = 48 - 1;
const int OVERPRICE_MONTH = 147;


struct Holder {
    double holding_rate;
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
    printf("Итоговый капитал Боба  - %lld копеек\n", Bob->capital);
}


/**
 * @brief Calculate monthly mortgage payment using annuity loan scheme
 * (https://www.raiffeisen.ru/wiki/kak-rasschitat-annuitetnyj-platezh)
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
    kopeck alice_starting_capital = 1000 * 1000 * 100;
    kopeck bob_starting_capital = 0 * 100;

    kopeck alice_earnings = 200 * 1000 * 100;
    kopeck bob_earnings = 200 * 1000 * 100;

    kopeck food_expenses = 15 * 1000 * 100;
    kopeck communal_expenses = 5 * 1000 * 100;

    kopeck alice_apartment_expenses = 30 * 1000 * 100;
    kopeck bob_mortgage_initial_payment = 1000 * 1000 * 100;
    kopeck bob_apartment_expenses =
            calculate_mortgage_payment(APARTMENT_PRICE - bob_mortgage_initial_payment);

    Alice->holding_rate = HOLDING_RATE;
    Alice->capital = alice_starting_capital;
    Alice->earnings = alice_earnings;
    Alice->food_expenses = food_expenses;
    Alice->communal_expenses = communal_expenses;
    Alice->apartment_expenses = alice_apartment_expenses;

    Bob->holding_rate = HOLDING_RATE;
    Bob->capital = bob_starting_capital;
    Bob->earnings = bob_earnings;
    Bob->food_expenses = food_expenses;
    Bob->communal_expenses = communal_expenses;
    Bob->apartment_expenses = bob_apartment_expenses;
}


void alice_monthly_income(struct Holder *Alice, const int *month) {
    // If holding capital limit (equals to CAPITAL_LIMIT) is exceeded, holding rate decreases.
    // But if it is below the limit, holding rate decreases back to default
    if (Alice->capital > CAPITAL_LIMIT) Alice->holding_rate = LIMITED_HOLDING_RATE;
    else Alice->holding_rate = HOLDING_RATE;
    Alice->capital = (kopeck) ((double) Alice->capital * (1. + Alice->holding_rate / 12));

    // At the start of each January Alice's earnings gets indexed
    if (*month % 12 == 0) Alice->earnings += (kopeck) (INFLATION_RATE * (double) Alice->earnings);
    Alice->capital += Alice->earnings;
}


void bob_monthly_income(struct Holder *Bob, const int *month) {
    // If holding capital limit (equals to CAPITAL_LIMIT) is exceeded, holding rate decreases.
    // But if it is below the limit, holding rate decreases back to default
    if (Bob->capital > CAPITAL_LIMIT) Bob->holding_rate = LIMITED_HOLDING_RATE;
    else Bob->holding_rate = HOLDING_RATE;
    Bob->capital = (kopeck) ((double) Bob->capital * (1. + Bob->holding_rate / 12));

    // At the start of UNEMPLOYMENT_MONTH Bob loses his earnings until EMPLOYMENT_MONTH
    if (*month < UNEMPLOYMENT_MONTH || *month >= EMPLOYMENT_MONTH)
        Bob->capital += Bob->earnings;
}


void monthly_outcome(struct Holder *holder) {
    holder->capital -= holder->apartment_expenses;
    holder->capital -= holder->food_expenses;
    holder->capital -= holder->communal_expenses;
}


void apartment_price_changes(kopeck *apartment_price, const int *month) {
    // At the start of each January apartment price gets inflated by INFLATION RATE
    if (*month % 12 == 0) *apartment_price += (kopeck) ((double) *apartment_price * INFLATION_RATE);

    // At the start of OVERPRICE_MONTH apartment Alice wants to buy gets its cost overpriced by OVERPRICE
    if (*month == OVERPRICE_MONTH) *apartment_price += (kopeck) ((double) *apartment_price * OVERPRICE);
}


/**
 * @brief Calculate Alice's and Bob's capitals after the holding period
 */
void calculate_holdings(struct Holder *Alice, struct Holder *Bob) {
    // Alice intends to buy an apartment after the holding period, with its price
    // before start of the holding period being tantamount to APARTMENT_PRICE
    kopeck apartment_price = APARTMENT_PRICE;

    for (int month = STARTING_MONTH; month < HOLDING_MONTHS + STARTING_MONTH; month++) {
        alice_monthly_income(Alice, &month);
        monthly_outcome(Alice);

        bob_monthly_income(Bob, &month);
        monthly_outcome(Bob);

        apartment_price_changes(&apartment_price, &month);
    }

    // By the end of the holding period Alice buys an apartment with a price that inflated over time
    Alice->capital -= apartment_price;
}


int main() {
    struct Holder Alice, Bob;

    initialize_holders(&Alice, &Bob);

    calculate_holdings(&Alice, &Bob);

    print_holding_results(&Alice, &Bob);

    return 0;
}
