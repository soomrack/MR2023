#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef long long int kopeyki;

kopeyki amortization = 5000 * 100;
kopeyki flat_price = 10 * 1000 * 1000 * 100;
double inflation = 0.07;

struct Person{
kopeyki capital;
kopeyki salary;
kopeyki expenses;
kopeyki rent_price;
kopeyki mortgage_price;
}alice, bob;



void alice_init(){
    alice.capital = 1000 * 1000 * 100;
    alice.salary = 200 * 1000 * 100;
    alice.expenses = 500 * 1000 * 100;
    alice.rent_price = 400 * 1000 * 100;
}

void bob_init(){
    bob.capital = 0 * 100;
    bob.salary = 200 * 1000 * 100;
    bob.expenses = 500 * 1000 * 100;
    bob.mortgage_price = 100 * 1000 * 100;
}

void alice_salary_income(){
    alice.capital += alice.salary;
    alice.salary *= (inflation / 12 + 1);
}

void bob_salary_income(){
    bob.capital += bob.salary;
    bob.salary *= (inflation/12 + 1);
}

void alice_deposite_income(){
   int bank_p;
if(alice.capital < 1000*1000*10*100){
    bank_p = 11;
}else{
    bank_p = 9;
}
alice.capital += (kopeyki)(alice.capital*(bank_p/100.0/12.0));
}

void bob_deposite_income(){
    int bank_p;
if(bob.capital < 1000*1000*10*100){
    bank_p = 11;
}else{
    bank_p = 9;
}
bob.capital += (kopeyki)(bob.capital*(bank_p/100.0/12.0));
}

void alice_expenses(){
    alice.capital -= alice.expenses;
    alice.expenses *= (inflation / 12 + 1);
}

void bob_expenses(){
    bob.capital -= bob.expenses;
    bob.expenses *= (inflation / 12 + 1);
}

void alice_rent(){
    alice.capital -= alice.rent_price;
    alice.rent_price *= (inflation / 12 + 1);
}

void bob_rent(){
    bob.capital -= bob.mortgage_price;
    bob.mortgage_price *= (inflation / 12 + 1);
}

void alice_extra_spend(){
    alice.capital -= amortization;  
}


void bob_extra_spend(){
    //int amortization;
    bob.capital -= amortization; 
}


void simulation(){
    int mounth = 9, year = 2023;
 while(year !=2053 && mounth !=8){
    alice_salary_income();
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
     if(mounth==13){
    mounth = 1;
    ++year;
    }
 }
}


void print_winner(){
    kopeyki bob_capital = (bob.capital + flat_price) / 100;
    kopeyki alice_capital = (alice.capital) / 100;
    printf("|%0.2lf | %0.2lf|\n %s", alice_capital, bob_capital,  (alice_capital > bob_capital) ? "Alice will accumulate more capital":"Bob will accumulate more capital");
}

int main(){

//setlocale(LC_ALL, "Ru");

alice_init();
bob_init();
simulation();
print_winner();
    return 0 ;
}