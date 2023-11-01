#include<stdio.h>
#include<math.h>

const int FLAT_COST = 20 * 1000 * 1000;
const int FLAT_RENT = 25 * 1000;
const int SALARY = 200 * 1000;
const float INFLATION = 0.07; 

const int TEETH = 500 * 1000;
const int VACATION = 200 * 1000;

const int FIRST_MONTH = 9;
const int LAST_MONTH = 8;   

const int FIRST_YEAR = 2023;
const int LAST_YEAR = 2053; 

float BANK_DEPOSIT = 0.09; 


typedef long long int Money;

struct Person{
	Money capital;
	Money salary;
	Money monthly_spendings;
};

struct Person Alice;
struct Person Bob;


void alice_initialization()
{
	Alice.capital = 1 * 1000 * 1000;
	Alice.monthly_spendings = 30 * 1000 + FLAT_RENT;
	Alice.salary = SALARY;
}


void bob_initialization()
{
	int number_of_years = LAST_YEAR - FIRST_YEAR;
	Bob.capital = 0;
	Bob.monthly_spendings = 30 * 1000 + ((FLAT_COST - 1000000) * (0.07 / 12) * (pow((1 + 0.07 / 12), \
    (number_of_years * 12)))) / (pow((1 + 0.07 / 12), (number_of_years * 12)) - 1);;
	Bob.salary = SALARY;
}


void alice_salary_income(int year, int month)
{
    Alice.capital += Alice.salary;
}


void bob_salary_income(int year, int month)
{
    Bob.capital += Bob.salary;
}


void alice_pay_for_life(int year, int month)
{
    if (month == 12) {
        Alice.capital -= Alice.monthly_spendings * 1.2;
    }
    Alice.capital -= Alice.monthly_spendings;
}


void bob_pay_for_life(int year, int month)
{
    if (month == 12) {
        Bob.capital -= Bob.monthly_spendings * 1.2;
    }
    Bob.capital -= Bob.monthly_spendings;
}


void alice_deposite_income(int year, int month)
{
    if (year == 2033 && month == 1) {
        BANK_DEPOSIT = 0.1;
    }
    Alice.capital = Alice.capital * (1.0 + BANK_DEPOSIT / 12.0);
}


void bob_deposite_income(int year, int month)
{
    if (year == 2033 && month == 1) {
        BANK_DEPOSIT = 0.1;
    }
    Bob.capital = Bob.capital * (1.0 + BANK_DEPOSIT / 12.0);
}

void alice_salary_index(int year, int month)
{
	if(month == 12){
		Alice.salary *= 1.05;
	}
}

void bob_salary_index(int year, int month)
{
	if(month == 12){
		Bob.salary *= 1.05;
	}
}

void life_inflation(int year, int month)
{
    if (month % 3 == 0 && month > 2) {
        Alice.monthly_spendings += Alice.monthly_spendings * INFLATION / 4.0;
        Bob.monthly_spendings += Bob.monthly_spendings * INFLATION / 4.0;
    }
    if (month == 12) {
        Alice.salary = Alice.salary * (1.0 + INFLATION / 2.0);
        Bob.salary = Bob.salary * (1.0 + INFLATION / 2.0);
    }
}


void teeth_repair(int year, int month)
{
	if((year - FIRST_YEAR) % 10 == 0 && year != FIRST_YEAR && month == 6){
		Alice.capital -= TEETH;
	}
}


void vacation_turkey(int year, int month)
{
	if((year - FIRST_YEAR) % 2 == 0 && year != FIRST_YEAR && month == 6){
		Alice.capital -= VACATION;
	}
}


void simulation()
{
    int month = FIRST_MONTH;
    int year = FIRST_YEAR;

    while(!(year == LAST_YEAR && month == LAST_MONTH)) {

        alice_deposite_income(year, month);
        alice_salary_income(year, month);
        alice_pay_for_life(year, month);
		alice_salary_index(year, month);
		vacation_turkey(year, month);
		teeth_repair(year, month);

        bob_deposite_income(year, month);
        bob_salary_income(year, month);
        bob_pay_for_life(year, month);
		bob_salary_index(year, month);

        life_inflation(year, month);
        
        month++;
        if (month > 12) {
            year++;
            month = 1;
        }  
    }
}


void print()
{
	printf("\nAlice capital: %lld\n", Alice.capital);
	printf("\nBob capital: %lld\n", Bob.capital);
}


main()
{
	alice_initialization();
	bob_initialization();
	
	simulation();
	
	print();
	
	return 0;
}