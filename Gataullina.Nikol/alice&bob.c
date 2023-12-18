#include <stdio.h>
#include <math.h>


typedef long long int Money;  //kopeiki


const int YEARS = 20;  //промежуток времени
const int YEAR = 2023;
const int MONTH = 9;
const double INFLATION = 0.07;
const double BANK_PERCENT = 0.09;
const Money START = 1000 * 1000 * 100;
const Money SALARY = 200 * 1000 * 100;
const Money ALICE_RENT = 30 * 1000 * 100; 
const Money FLAT = 20 * 1000 * 1000 * 100;


struct Person {
Money bank_account;
Money salary;
Money rent;
};


struct Person alice;
struct Person bob;


Money flat_cost = 20 * 1000 * 1000 * 100;


void alice_init()
{
alice.bank_account = START;
alice.salary = SALARY; 
alice.rent = ALICE_RENT; 
}


void bob_init()
{
bob.bank_account = 0; 
bob.salary = SALARY; 
}


Money bob_month_pay() {
double month_per = BANK_PERCENT / 12;
Money bob_month_payment = (FLAT - START) * (month_per + (month_per / (pow(1 + month_per, YEARS * 12)-1)));
return bob_month_payment;
}


void bob_payment(Money payment){
bob.bank_account -= payment; 
}


void alice_salary_income(const int year, const int month) 
{
if (year == 2024 && month == 11) {  // alice fired for one month
alice.salary = 0; 
} 
else {
alice.salary = SALARY; 
}

if(month % 12 == 0) {
alice.salary *= ( 1 + 0.07 );
}
}


void bob_salary_income(const int year, const int month)
{
if ( month == 1 ) {  // additional salary
bob.salary += 200 * 1000 * 100; 
}

bob.bank_account += bob.salary;

if(month % 12 == 0) {
bob.salary *= ( 1 + 0.07 );
}
} 


void alice_rent() {
int alice_rent = ALICE_RENT;
alice_rent *= ((INFLATION / 12) + 1);
alice.bank_account -= alice_rent;
}


void alice_spend_for_life (const int year, const int month) {
static Money life = 30 * 1000 * 100;
alice.bank_account -= life;
life *= ((INFLATION / 12) + 1);
}


void bob_spend_for_life (const int year, const int month) {
static Money life = 30 * 1000 * 100;
bob.bank_account -= life;
life *= (INFLATION / 12 + 1);
}


void alice_add_spending(const int year, const int month){
int dental = 0; // 500 * 1000 * 100
Money dental_cost = 500 * 1000 * 100;
if (dental != 0){
alice.bank_account -= dental_cost;
}
}


void bob_add_spending(const int year, const int month){
int dental = 0; // 500 * 1000 * 100
Money dental_cost = 500 * 1000 * 100;
if (dental != 0){
bob.bank_account -= dental_cost;
}
}


void alice_bank_percent (const int year, const int month) {
if (alice.bank_account > 5 * 1000 * 1000 * 100) {
alice.bank_account *= (1 + (BANK_PERCENT + 0.01) / 12);
} else {
alice.bank_account *= (1 + BANK_PERCENT / 12);
}
}


void bob_bank_percent (const int year, const int month) {
bob.bank_account *= (1 + BANK_PERCENT / 12);
}


void alice_inflation (const int year, const int month) {
alice.rent *= (1 + INFLATION / 12);
}


void bob_inflation (const int year, const int month) {
flat_cost *= (1 + INFLATION / 12);
}


void result () {
double bob_sum = (bob.bank_account - flat_cost);
double alice_sum = alice.bank_account;
printf("alice bank account = %f\n", alice_sum);
printf("bob bank account = %f\n", bob_sum);
}


void simulation (const Money bob_month_payment)
{
int month = 9;
int year = 2023;

while(month != MONTH + 12 * YEARS) {
alice_salary_income(year, month);
alice_rent(year, month);
alice_spend_for_life(year, month);
alice_add_spending(year, month);
alice_bank_percent(year, month);
alice_inflation(year, month); 

bob_salary_income(year, month);
bob_add_spending(year, month);
bob_bank_percent(year, month);
bob_inflation(year, month);
bob_spend_for_life(year, month);
bob_payment(bob_month_payment);


++month;
if(month % 12 == 0) {
++year; 
}
}
}


int main ()
{
alice_init();
bob_init();
Money bob_month_payment = bob_month_pay();
simulation(bob_month_payment);
result();

return 0;
}
