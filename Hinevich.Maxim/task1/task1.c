#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef long long int kopeyki;

kopeyki amortization = 5000 * 100;
kopeyki flat_price = 10 * 1000 * 1000 * 100;
double inflation = 0.07;
int count;
struct Person {
    kopeyki capital;
    kopeyki salary;
    kopeyki expenses;
    kopeyki rent_price;
    kopeyki mortgage_price;
};

struct Person Alice, Bob;


void alice_init()
 {

    Alice.capital = 1000 * 1000 * 100;
    Alice.salary = 200 * 1000 * 100;
    Alice.expenses = 50 * 1000 * 100;
    Alice.rent_price = 40 * 1000 * 100;
    
}


void bob_init()
 {

    Bob.capital = 0 * 100;
    Bob.salary = 200 * 1000 * 100;
    Bob.expenses = 50 * 1000 * 100;
    Bob.mortgage_price = 100 * 1000 * 100;

}


void alice_salary_income(const int mounth) 
{

    if (mounth == 12) {
        Alice.capital += Alice.salary;
}
    Alice.capital += Alice.salary;
    Alice.salary *= (inflation / 12 + 1);

}


void bob_salary_income()
 {

    Bob.capital += Bob.salary;
    Bob.salary *= (inflation/12 + 1);

}


void alice_deposite_income()
 {

   int bank_p;
    if (Alice.capital < 1000 * 1000 * 10 * 100) {
        bank_p = 11;
    } else {
        bank_p = 9;
    }
    Alice.capital += (kopeyki)(Alice.capital * (bank_p / 100.0 / 12.0));

}


void bob_deposite_income() 
{

    int bank_p;
    if (Bob.capital < 1000 * 1000 * 10 * 100) {
        bank_p = 11;
    } else {
        bank_p = 9;
    }
    Bob.capital += (kopeyki)(Bob.capital*(bank_p/100.0/12.0));

}


void alice_expenses() 
{

    Alice.capital -= Alice.expenses;
    Alice.expenses *= (inflation / 12 + 1);

}


void bob_expenses()
{

    Bob.capital -= Bob.expenses;
    Bob.expenses *= (inflation / 12 + 1);

}


void alice_rent() 
{

    Alice.capital -= Alice.rent_price;
    Alice.rent_price *= (inflation / 12 + 1);

}


void bob_rent() 
{

    Bob.capital -= Bob.mortgage_price;
    Bob.mortgage_price *= (inflation / 12 + 1);

}


void alice_extra_spend() 
{

    Alice.capital -= amortization;  

}


void bob_extra_spend() 
{
    
    Bob.capital -= amortization; 

}


void simulation() 
{

    int mounth = 9, year = 2023;
 while(year !=2053 && mounth !=8) {
    alice_salary_income(mounth);
    alice_deposite_income();
    alice_rent();
    alice_expenses();
    alice_extra_spend();

    bob_salary_income();
    bob_deposite_income();
    bob_rent();
    bob_expenses();
    bob_extra_spend();

    ++mounth;
    if (mounth == 13) {
        mounth = 1;
        ++year;
    }
 }
}


void print_winner() 
{

    kopeyki Bob_capital = (Bob.capital + flat_price) / 100;
    kopeyki Alice_capital = (Alice.capital) / 100;
    printf("|%0.2lld | %0.2lld|\n %s", Alice_capital, Bob_capital,  (Alice_capital > Bob_capital) ? "Alice will accumulate more capital":"Bob will accumulate more capital");
}

int main() 
{
    
alice_init();
bob_init();
simulation();
print_winner();
    return 0 ;
}