#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef long long int kopeyki;

kopeyki rent_price = 400 * 1000 * 100;
kopeyki mortgage_price = 100 * 1000* 100;

struct Person{
kopeyki capital;
kopeyki salary;
kopeyki expenses;
}alice, bob;

struct Person alice;
struct Person bob;

void alice_init(){
    alice.capital = 1000 * 1000 * 100;
    alice.salary = 200 * 1000 * 100;
    alice.expenses = 500 * 1000 * 100;
}

void bob_init(){
    bob.capital = 0 * 100;
    bob.salary = 200 * 1000 * 100;
    bob.expenses = 500 * 1000 * 100;
}

void alice_salary_income(){
    alice.capital += alice.salary;
}

void bob_salary_income(){
    bob.capital += bob.salary;
}

void alice_deposite_income(){
   int bank_p = 11;
 alice.capital += (kopeyki)(alice.capital*(bank_p/100.0/12.0));
}

void bob_deposite_income(){
   int bank_p = 11;
 bob.capital += (kopeyki)(bob.capital*(bank_p/100.0/12.0));
}

void alice_expenses(){
    alice.capital -= alice.expenses;
}

void bob_expenses(){
    bob.capital -= bob.expenses;
}

void alice_rent(){
    alice.capital -= rent_price;
}

void bob_rent(){
    bob.capital -= mortgage_price;
}

void simulation(){
    int mounth = 9, year = 2023;
for (mounth; mounth < 8 && year < 2053; mounth = 13 ? mounth =1, ++year : ++mounth){
    alice_salary_income();
    alice_deposite_income();
    alice_rent();
    alice_expenses();

    bob_salary_income();
    bob_deposite_income();
    bob_rent();
    bob_expenses();
}

}




void print_winner(){
    printf("|%0.2lf | %0.2lf|\n %s", alice.capital, bob.capital,  (alice.capital>bob.capital) ? "Alice сформирует больший капитал":"Bob сформирует больший капитал");
}

int main(){

setlocale(LC_ALL, "Ru");

alice_init();
bob_init();
simulation();
    /*
    посчитать доходы алисы
    посчитать доходы боба

    посчитать траты алисы
    посчитать траты боба

    посчитать капитал боба и алисы и сравнить
    
    */
print_winner();
    return 0 ;
}



























































































/*void alice_deposite(){

}



for (i=0;i<=qtyYers-1;++i){
   
    salary_alice *= 1.06;
    deposite_alice = capital_alice*pow(1+investment/(100*12), i*qtyYers) ;
    expenses_alice *=1.07 ;
    capital_alice +=(salary_alice-rent-expenses_alice)*12;

    salary_bob *= 1.06;
    deposite_bob = capital_bob*pow(1+investment/(100*12), i*qtyYers) ;
    expenses_bob *=1.07 ;
    capital_bob +=(salary_bob-mortgage-expenses_bob)*12;

}
capital_alice = deposite_alice;
capital_bob = deposite_bob+apartment_price;

printf("|%0.2lf | %0.2lf|\n %s", capital_alice, capital_bob,  (capital_alice > capital_bob) ? "Alice сформирует больший капитал":"Bob сформирует больший капитал");
    return 0;
}





for (month=0; month<8 && year < 2053; ++month, month = 13? month =1, ++year){

alice_salary_income (month, year); добавить статистику по месяцам и годам
alice_deposite_income(month, year);

}



void alice_init{
    alice.bank_account = 1000*1000*100;
    alice.salary = 200 * 1000* 100;
}

void bob_init{
    bob_bank_account = 1000*1000*100;
    bob.salary = 200 * 1000*100
}

void print_alice{
    printf("Alice\n");
    printf(" bank_account =%lld", alice_bank_account);
}

void print_bob{
    printf("Bob\n");
    printf(" bank_account =%lld", bob_bank_account);
}

void alice_salary_income(const int year, const int month){
 if year == 2024 && month == 10) alice.salary =0;
 alice_bank_account += alice_salary
}
void alice_salary_income(const int year, const int month){
 alice_bank_account += alice_salary
}

void alice_deposite_income(const int year, const int month){
    int bank_pp = 11;
    alice.bank_account += (money)(alice.bank_account*(bank_pp/100.0/12.0));

}

void alice_arenda(const int year, const int month){
    alice.bank_account -= 35000*100;

}
void simulation{
    int month = 9;
    int year = 2023;

    while(year !=2053 && month !=8){
        alice_salary_income(year, month);
        alice_deposite_income(year, month);
        alice_arenda(year, month);
        alice_expenses(year, month);
        добавить еще тратж
        
        bob_salary_income(year, month);
        bob_deposite_income(year, month);
        bob_arenda(year, month);
        bob_expenses(year, month);

        ++month;
        if (month == 13){
            ++year;
            month=1;
        }
    }
}
 int main(){
    alice_init();
    bob_init();
    print_alice();
    print_bob();
    simulation();
    return 0;
 }


если на счете больше 10 млн то ставка по вкладу уменьшается.
раз в 10 лет трата на зубы.









*/