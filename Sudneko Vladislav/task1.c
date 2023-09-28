// Libs

#include <stdio.h>
#include <math.h>
#include <locale.h>


// Init Person
typedef struct {
    long long unsigned int bank;
    int income;
    int expenses;
} Person;
void initPerson (Person *person, long long int bank, int income, int expenses){
    person->bank = bank;
    person->income = income;
    person->expenses = expenses;
}

// All about Alice

void aliceIncome(Person* alice, int month, int year) {
    alice->bank *= 1 + 9.0 / 1200.0;
    

    if ((month == 6 || month == 7) && year == 2035) {
        alice->income = 0;
    }
    if (month == 8 && year == 2035) {
        alice->income = 200*1000*100;
    }
}

void aliceExpenses(Person* alice, int month, int year) {
    alice->expenses *= 1 + 7.0 / 1200.0;

    if (month == 12 && year == 2035) {
        alice->expenses += 1000;
    }
}

double computeAliceBank(Person* alice) {

    int months = 240;
    int month;
    int year;
    for (int i = 0; i < months; i++) {
        month = i % 12 + 1;
        year = 2023 + i / 12;
        aliceIncome(alice, month, year);
        aliceExpenses(alice, month, year);
        
        alice->bank += alice->income - alice->expenses;
    }

    return alice->bank;
}

// All about Bob

int mortgageCalc(int sum, float r, int n) {
    int monthlyPayment = sum * r * pow(1 + r, n) / (pow(1 + r, n) - 1);
    return monthlyPayment;
}

void bobIncome(Person* bob, int month, int year) {
    bob->bank *= 1 + 9 / 1200;
}

void bobExpenses(Person* bob, int month, int year) {
    
}

long long int computeBobBank(Person* bob) {

    float r = 7.0 / 12.0 / 1200.0;
    int sum = 19*1000*1000*100;
    int n = 240;
    int mortgage = mortgageCalc(sum, r, n);

    int months = 240;
    int month;
    int year;
    for (int i = 0; i < months; i++) {
        month = i % 12 + 1;
        year = 2023 + i / 12;
        bobIncome(bob, month, year);
        bobExpenses(bob, month, year);
        bob->bank += bob->income - mortgage - bob->expenses;
    }


    bob->bank *= 1 + 9 / 1200;
    bob->bank += bob->income - (sum - mortgage * 239);

    return bob->bank;
}

// Print result of the program

void printResult(Person *alice, Person *bob) {
    printf("\n\n\n\n\n\n\t\tResult of simulation\n");
    printf("\t\t===========================\n");
    printf("\t\tAlice Bank: %lli\n", alice->bank/100);
    printf("\t\tBob Bank: %lli\n", bob->bank/100);
    printf("\t\t===========================\n\n\n\n\n\n\n\n\n\n");
}

// Entry Point

int main() {
    Person alice;
    initPerson(&alice, 1000*1000*100, 200*1000*100, 60*1000*100);
    Person bob;
    initPerson(&bob, 0, 200*1000*100, 30*1000*100);

    computeAliceBank(&alice);
    computeBobBank(&bob);

    printResult(&alice, &bob);

    return 0;
}