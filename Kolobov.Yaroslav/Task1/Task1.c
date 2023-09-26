#include <stdio.h>
#include <math.h>
    

struct finance {
    int food;
    int utilities;
    int medicine;
    int add;
    int mortgage;
};


int month_add_counter(int food, int utilities, int medicine, int mortgage, int salary, int rent)
{
    int month_add;
    month_add =  salary - (food + utilities + medicine + mortgage + rent);
    return(month_add);
}


int main(void)
{
    const int YEARS = 20;
    const int CAPITAL = 1000 * 1000 * 100; // Price in kopeika

    const float INFLATION = 0.07;
    const float PRICE_INCREASE = 1.05;
    const float SALARY_INCREASE = 1.03;

    float interest_percent = 0.07; 
    float deposite_percent = 0.09;

    long long int flat_price = 2000 * 1000 * 1000; 
    int salary = 2000 * 1000 * 10;
    int rent = 3000 * 1000;
    int monthes;
    long long int alice_total = 0;
    long long int bob_total = 0;
    
    monthes = YEARS * 12;
    interest_percent = interest_percent/12.0;
    deposite_percent = 1 + deposite_percent/12.0;

    float mortgage_pay = (flat_price - CAPITAL) * ((interest_percent * pow(1 + interest_percent, monthes)) / (pow(1 + interest_percent, monthes) - 1));

    struct finance alice = {1500000, 500000, 1000000, 0, 0};
    struct finance bob = {1500000, 500000, 1000000, 0, mortgage_pay};

    alice.add = month_add_counter(alice.food, alice.utilities, alice.medicine, alice.mortgage, salary, rent);
    bob.add = month_add_counter(bob.food, bob.utilities, bob.medicine, bob.mortgage, salary, 0);
    alice_total = CAPITAL;

    flat_price *= pow((1+INFLATION), YEARS);
    flat_price = flat_price/100;

    for (int month = 0; month < monthes; month++ ){

        if (month != 0 && month%12==0){
            alice.food *= PRICE_INCREASE;
            bob.food *= PRICE_INCREASE;
            rent *= PRICE_INCREASE;
            salary *= SALARY_INCREASE;
            alice.add = month_add_counter(alice.food, alice.utilities, alice.medicine, alice.mortgage, salary, rent);
            bob.add = month_add_counter(bob.food, bob.utilities, bob.medicine, bob.mortgage, salary, 0);
        }

        alice_total *= deposite_percent;
        alice_total += alice.add;
        bob_total *= deposite_percent;
        bob_total += bob.add;  
    }    
    
    //alice_total -= flat_price;
    alice_total = alice_total/100;
    bob_total = bob_total/100;
    bob_total += flat_price;

    printf("Alice capital =  %lld, Bob capital =  %lld\n", alice_total, bob_total);
    if (alice_total>bob_total)
        printf("Alice has larger capital\n");
    else
        printf("Bob has larger capital\n");
    printf("Flat price =  %lld\n", flat_price);
}