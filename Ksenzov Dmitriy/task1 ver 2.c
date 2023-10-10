#include <stdio.h>
#include <string.h>
#include <math.h>


typedef long long int Money;  // kopecks


struct Person
{
    Money bank_account;
    int bank_contribution_procent;
    char name[6];
    Money salary;
    Money rent;
    Money consumption;  // food, utility fee and other personal needs
    int inflation;
    Money mortgage;
    Money appartment;
    Money appartment_mortgage_first_payment;
    Money appartment_cost;
    int appartment_mortgage_procent;
    int appartment_mortgage_period;
};


struct Person alice;
struct Person bob;


void alice_int()
{
    alice.bank_account = 1000 * 1000 * 100;
    strcpy(alice.name, "Alice");
    alice.bank_contribution_procent = 11;
    alice.salary = 200 * 1000 * 100;
    alice.rent = 30 * 1000 * 100;
    alice.consumption = 30 * 1000 * 100;
    alice.inflation = 7;
    alice.mortgage = 0;
    alice.appartment = 0;
    alice.appartment_mortgage_first_payment = 3 * 1000 * 1000 * 100;
    alice.appartment_cost = 3 * 1000 * 1000 * 100;
    alice.appartment_mortgage_procent = 7;
    alice.appartment_mortgage_period = 10;
}


void bob_int()
{
    bob.bank_account = 1000 * 1000 * 100;
    strcpy(bob.name, "Bob");
    bob.bank_contribution_procent = 11;
    bob.salary = 200 * 1000 * 100;
    bob.rent = 0;
    bob.consumption = 30 * 1000 * 100;
    bob.inflation = 7;
    bob.mortgage = 0;
    bob.appartment = 0;
    bob.appartment_mortgage_first_payment = 1000 * 1000 * 100;
    bob.appartment_cost = 20 * 1000 * 1000 * 100;
    bob.appartment_mortgage_procent = 7;
    bob.appartment_mortgage_period = 30;
}


void print_person(const struct Person person)
{
    printf("%s ", person.name);
    printf("bank account = %lld kopecks\n", person.bank_account);
}


void alice_contribution(const int year, const int month)
{
    alice.bank_account += (Money)(alice.bank_account * alice.bank_contribution_procent / 100.0 / 12.0);
}


void bob_contribution(const int year, const int month)
{
    bob.bank_account += (Money)(bob.bank_account * bob.bank_contribution_procent / 100.0 / 12.0);
}


void alice_salary (const int year, const int month)
{
    if (month == 12) alice.bank_account += alice.salary;  // 13-th salary

    alice.bank_account += alice.salary;

    if (month == 1) alice.salary += (Money)(alice.salary * alice.inflation / 100.0);  // salary growth
    
}


void bob_salary (const int year, const int month)
{
    if (month == 12) bob.bank_account += bob.salary;  // 13-th salary
    
    bob.bank_account += bob.salary;

    if (month == 1) bob.salary += (Money)(bob.salary * bob.inflation / 100.0);  // salary growth
}


void alice_rent (const int year, const int month)
{
    alice.bank_account -= alice.rent;
    alice.rent += (Money)(alice.rent * alice.inflation / 100.0 / 12.0);
}


void bob_rent (const int year, const int month)
{
    bob.bank_account -= bob.rent;
    bob.rent += (Money)(bob.rent * bob.inflation / 100.0 / 12.0);
}


void alice_consumption (const int year, const int month)
{
    alice.bank_account -= alice.consumption;
    alice.consumption += (Money)(alice.consumption * alice.inflation / 100.0 / 12.0);
}


void bob_consumption (const int year, const int month)
{
    bob.bank_account -= bob.consumption;
    bob.consumption += (Money)(bob.consumption * bob.inflation / 100.0 / 12.0);
}


void alice_appartment (const int year, const int month)
{
    if (year == 2053 && month == 9) {
    alice.bank_account += alice.appartment;
    };

    alice.appartment += (Money)(alice.appartment * alice.inflation / 100.0 / 12.0);    
}


void bob_appartment (const int year, const int month)
{  

    if (year == 2053 && month == 9) {
    bob.bank_account += bob.appartment;
    };

    bob.appartment += (Money)(bob.appartment * bob.inflation / 100.0 / 12.0);    
}


void alice_mortgage (const int year, const int month)
{
    if (year == 2023 && month == 9) {
        alice.bank_account -= alice.appartment_mortgage_first_payment;
        Money appartment_mortgage = alice.appartment_cost - alice.appartment_mortgage_first_payment;
        double mortgage_month_procent = alice.appartment_mortgage_procent / 100.0 / 12.0;
        double mortgage_power = pow(1 + mortgage_month_procent, alice.appartment_mortgage_period * 12.0);
        alice.mortgage += (Money)(((appartment_mortgage) * (mortgage_month_procent) * mortgage_power) / (mortgage_power - 1.0));
        alice.appartment += alice.appartment_cost;
    };
    
    alice.bank_account -= alice.mortgage;
}


void bob_mortgage (const int year, const int month)
{
    if (year == 2023 && month == 9) {
        bob.bank_account -= bob.appartment_mortgage_first_payment;
        Money appartment_mortgage = bob.appartment_cost - bob.appartment_mortgage_first_payment;
        double mortgage_month_procent = bob.appartment_mortgage_procent / 100.0 / 12.0;
        double mortgage_power = pow(1 + mortgage_month_procent, bob.appartment_mortgage_period * 12.0);
        bob.mortgage += (Money)(((appartment_mortgage) * (mortgage_month_procent) * mortgage_power) / (mortgage_power - 1.0));
        bob.appartment += bob.appartment_cost;
    };

    bob.bank_account -= bob.mortgage;
}


void print_profit_person (const struct Person person1, const struct Person person2)
{
    if (person1.bank_account > person2.bank_account) {
    printf("%s's strategy is more profit", person1.name);
    }
    else {
    printf("%s's strategy is more profit", person2.name);    
    };   
}

void simulation()
{
    int year = 2023;
    int month = 9;

    while (!(year == 2053 && month == 9)) {
        
        alice_appartment(year, month);
        alice_contribution(year, month);
        alice_salary(year, month);
        alice_rent(year, month);
        alice_consumption(year, month);  // food, utility fee and other personal needs
        alice_mortgage(year, month);

        bob_appartment(year, month);
        bob_contribution(year, month);
        bob_salary(year, month);
        bob_rent(year, month);
        bob_consumption(year, month);  // food, utility fee and other personal needs
        bob_mortgage(year, month);

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        };
               
    }
    
}


int main() {
    alice_int();
    bob_int();
    simulation();
    print_person(alice);
    print_person(bob);
    print_profit_person(alice, bob);
    return 0;
}