#include <stdio.h>
#include <math.h>

typedef long long int money; // считаем в копейках
struct Person{
    money capital;  
    money income;
    money spendings;
    money flat_payment;
    money overpayment;
} Alice, Bob;

const money FLAT_PRICE = 20*1000*1000*100;
const money FLAT_RENT_PRICE = 40*100*100;
const money SALARY = 200*1000*100;
const money FIRST_FLAT_PAYNMENT = 1000*1000*100;
const money LIFE_SPENDING = 25*1000*100;

const int YEARS = 20;
const int START_MONTH = 9;
const int START_YEAR = 2023;

double INFLATION = 0.07;
double BANK_RATE = 0.09;

void alice_init(){
    Alice.income = SALARY;
    Alice.capital = FIRST_FLAT_PAYNMENT;
    Alice.spendings = LIFE_SPENDING;
    Alice.flat_payment = FLAT_RENT_PRICE;
    Alice.overpayment = FLAT_PRICE * pow((1.0 + INFLATION), YEARS) - FLAT_PRICE;
}

void bob_init(){
    Bob.income = SALARY;
    Bob.capital = 0;
    Bob.spendings = LIFE_SPENDING;
    Bob.flat_payment = ((FLAT_PRICE - FIRST_FLAT_PAYNMENT) * (BANK_RATE / 12.0) * pow((1 + BANK_RATE / 12.0), (YEARS * 12.0)))
                        / (pow((1 + BANK_RATE / 12.0), (YEARS + 12.0)) - 1);
    Bob.overpayment = Bob.flat_payment * 12 * YEARS - FLAT_PRICE;
}

void alice_salary(int year, int month){
    Alice.capital += Alice.income;
}

void alice_deposite(int year, int month){
    Alice.capital *= (1.0 + BANK_RATE / 12.0);
}

void alice_spendings(int year, int month){
    Alice.capital -= (Alice.spendings + Alice.flat_payment);
}

void bob_salary(int year, int month){
    Bob.capital += Bob.income;
}

void bob_deposite(int year, int month){
    Bob.capital *= (1.0 + BANK_RATE / 12.0);
}

void bob_spendings(int year, int month){
    Alice.capital -= (Alice.spendings + Alice.flat_payment);
}

void inflation(int year, int month){
    if(month == 12){
        INFLATION *= 1.05;
        Alice.income *= (1.0 + INFLATION);
        Bob.income   *= (1.0 + INFLATION);
        Alice.flat_payment *= (1.0 + INFLATION);
    }
}

void simulation(){
    int month = START_MONTH;
    int year  = START_YEAR;
    while ((year != (START_YEAR + YEARS)) && month != 8)
    {
        alice_deposite(year, month);
        alice_salary(year, month);
        alice_spendings(year, month);

        bob_deposite(year, month);
        bob_salary(year, month);
        bob_spendings(year, month);

        inflation(year, month);

        month++;

        if(month > 12){
            year++;
            month -=12;
        }
    }
}

void print_bob()
{
    printf("Bob Capital: %lld\n", Bob.capital); 
    printf("Bob Income: %lld\n", Bob.income); 
    printf("Bob Life spendings: ""%lld\n", Bob.spendings); 
    printf("Bob Monthly payment: %lld\n", Bob.flat_payment); 
    printf("Bob Overpayment: ""%lld\n", Bob.overpayment);
}

void print_alice()
{
    printf("Alice Capital: %lld\n", Alice.capital); 
    printf("Alice Income: %lld\n", Alice.income); 
    printf("Alice Life spendings: ""%lld\n", Alice.spendings); 
    printf("Alice Monthly payment: %lld\n", Alice.flat_payment); 
    printf("Alice Overpayment: ""%lld\n", Alice.overpayment);
    printf("\n");
}

int main() 
{
    alice_init();
    bob_init();

    simulation();

    print_alice();
    print_bob();

    return 0;
}