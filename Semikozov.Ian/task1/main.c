#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
/**
 * @brief с учетом того, что каждый месяц мы добавляем новые деньги к депозиту, 
 *        выберем схему для расчета профита вклада с возможностью пополнения. 
 *        Считаем, что Боб взял ипотеку с первоначальным взносом 10% от нужной 
 *        ипотеки и 7% годовых, динамика инфляции и дефляции на жилье принята 
 *        исходя из статистики цен на жилье в США
 */

typedef unsigned long long cents;
cents apartmentPrice = 1000000000UL; // start apartment price 10.000.000.00 
const uint8_t years = 20;
const uint16_t months = years * 12;
const cents startSalary = 20000000UL; // both have same start salary 200.000.00
const double bankPercent = 0.09;

const double dynamicInflation[] = {
    0.0327, 0.0395, 0.0747, 0.0658, 
    0.0285,-0.0031, 0.0272, 0.0164, 
    0.0239, 0.0207, 0.0212, 0.0273, 
    0.0260, 0.0233, 0.0288, 0.0256, 
    0.0230, 0.0207, 0.0382, 0.0620 
};

cents calculateMortgagePayment(const cents mortgageCost, const double yearProcents, uint16_t mortgageTerm, cents mortgageDebt) {
    double coefficient = yearProcents / (12 * (1 - pow(1. + yearProcents / 12, -mortgageTerm)));
    cents mortgagePayment = (cents)(coefficient * (double)mortgageDebt);
    return mortgagePayment;
}

typedef struct {
    cents salary; 
    cents housingExpenses;
    cents monthlyCosts;
    cents extraExpenses;
    cents currentCapital;
} Person;

void aliceInflation(Person *alice, const int year) {
    alice->housingExpenses += alice->housingExpenses * dynamicInflation[year];
    alice->salary += alice->salary * dynamicInflation[year];
    alice->monthlyCosts *= (1. + dynamicInflation[year]); 
}

void bobInflation(Person *bob, const int year) {
    bob->monthlyCosts *= (1. + dynamicInflation[year]); 
    bob->salary += bob->salary * dynamicInflation[year];
}

static inline void apartmentPriceInflation(const int year) {
    apartmentPrice *= (1. + dynamicInflation[year]);
}

static inline void bobDepositeIncome(Person *bob) {
    bob->currentCapital *= (1. + bankPercent / 12.0);
}

static inline void aliceDepositeInconme(Person *alice) {
    alice->currentCapital *= (1. + bankPercent / 12.0);
}

void bobSalaryIncome(Person *bob) {
    cents newMoney = bob->salary - (bob->housingExpenses + bob->monthlyCosts + bob->extraExpenses);    
    bob->currentCapital += newMoney;
}

void aliceSalaryIncome(Person *alice) {
    cents newMoney = alice->salary - (alice->housingExpenses + alice->monthlyCosts + alice->extraExpenses);    
    alice->currentCapital += newMoney;
}

void main(void) 
{
    const double yearProcents = 0.07;
    const cents mortgageDebt = apartmentPrice - 100000000;
    bool aliceHasApartment = false;
    Person bob = 
    {
       .currentCapital = 0,
       .monthlyCosts = 10000000,
       .extraExpenses = 1500000,
       .housingExpenses = calculateMortgagePayment(apartmentPrice, yearProcents, months, mortgageDebt),
       .salary = startSalary
    }, 
    alice = {
        .currentCapital = 100000000,
        .housingExpenses = 3000000,
        .monthlyCosts = 10000000,
        .extraExpenses = 2000000,
        .salary = startSalary
    };
    printf("Боб вынужден платить за ипотеку: %lld\n", bob.housingExpenses);
    for (uint8_t i = 0, j = 0; i < months; ++i) {
        if (0 == i % 12 && i != 0) {
            aliceInflation(&alice, j);
            bobInflation(&bob, j);
            apartmentPriceInflation(j);
            printf("Прошел %d-й месяц и квартира стоит сейчас: %lld\n", i+1, apartmentPrice);
            j++;
        }
        aliceSalaryIncome(&alice);
        aliceDepositeInconme(&alice);
        printf("Сейчас у Алисы: %lld\n", alice.currentCapital);

        if (alice.currentCapital >= apartmentPrice && !aliceHasApartment) {
            alice.currentCapital = 0;
            aliceHasApartment = true;
            printf("Алиса купила себе квартиру при итоговой стоимости: %lld\n", apartmentPrice);
        }

        bobSalaryIncome(&bob);
        bobDepositeIncome(&bob);
        printf("Сейчас у Боба: %lld\n", bob.currentCapital);
    }
    printf("Итого у Алисы: %lld, а у Боба: %lld", alice.currentCapital + apartmentPrice, bob.currentCapital);
}