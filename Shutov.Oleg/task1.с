#include <stdio.h>  
#include <math.h> 
#include <string.h> 

typedef long long int Money;  // копейки  

struct Person {
    Money bank_account;  
    int bank_account_precent;  
    Money salary;  
    Money rent;  // рента за съёмную квартиру
    int inflation_pp;  // инфляция
    Money house_price;  // стоимость приобретённой недвижимости
    Money first_payment;  // первый платёж по ипотеке
    int mortgage_pp;  // ипотечная процентная ставка
    int mortgage_term;  // срок ипотеки в годах
    char name[6]; 
    Money expenses;  // расходы на еду, одежду, отдых в месяц
    Money mortgage_annuity_payment;  
    int mortgage_srok;  // срок ипотеки в месяцах
    Money mortage_credit;  // кредит на ипотеку
};


struct Person alice;
struct Person bob;


void alice_init()
{
    alice.bank_account = 1000 * 1000 * 100;
    alice.bank_account_precent = 11;
    alice.salary = 200 * 1000 * 100;
    alice.rent = 30 * 1000 * 100;
    alice.inflation_pp = 7;
    alice.house_price = 0;
    strcpy_s(alice.name, "Alice");
    alice.expenses = 25 * 1000 * 100;
}


void bob_init()
{
    bob.bank_account = 1000 * 1000 * 100; 
    bob.bank_account_precent = 11; 
    bob.salary = 200 * 1000 * 100;
    bob.inflation_pp = 7; 
    bob.house_price = 20 * 1000 * 1000 * 100; 
    bob.first_payment = 1000 * 1000 * 100; 
    bob.mortgage_pp = 7; 
    bob.mortgage_term = 30; 
    strcpy_s(bob.name, "Bob"); 
    bob.expenses = 25 * 1000 * 100; 
    bob.mortgage_annuity_payment = bob.first_payment;
    bob.mortgage_srok = bob.mortgage_term * 12;
    bob.mortage_credit = bob.house_price;
}


void alice_deposite_income(const int year, const int month)
{
    alice.bank_account += (Money)(alice.bank_account * alice.bank_account_precent / 12.0 / 100.0);  
}


void alice_salary_income(const int year, const int month) 
{
    if (year == 2024 && month == 3) alice.salary = 0;   // отпуск за свой счёт в марте 2024
    if (year == 2024 && month == 4) alice.salary = 200 * 1000 * 100;
    alice.bank_account += alice.salary;  
    if (month == 12) alice.bank_account += alice.salary; // 13-ая зарплата 
    if (month == 1) alice.salary += (Money)(alice.salary * alice.inflation_pp / 100.0);  // индексация зарплаты
}


void alice_rent(const int year, const int month) 
{
    alice.bank_account -= alice.rent; 
    if (month == 1) alice.rent += (Money)(alice.rent * alice.inflation_pp / 100.0);  // учёт годовой инфляции
}


void alice_expenses(const int year, const int month)
{
    alice.bank_account -= alice.expenses;
    if (month == 1) alice.expenses += (Money)(alice.expenses * alice.inflation_pp / 100.0);  // учёт годовой инфляции
}


void bob_deposite_income(const int year, const int month)
{
    bob.bank_account += (Money)(bob.bank_account * bob.bank_account_precent / 12.0 / 100.0);  
}


void bob_salary_income(const int year, const int month)
{
    bob.bank_account += bob.salary; 
    if (month == 12) bob.bank_account += bob.salary;  // 13-ая зарплата
    if (month == 1)  bob.salary += (Money)(bob.salary * bob.inflation_pp / 100.0);  // индексация зарплаты
}


void bob_mortgage(const int year, const int month) 
{
    bob.mortage_credit -= bob.mortgage_annuity_payment;
    // формула расчёта месячного платежа взята с сайта Альфа Банка
    bob.mortgage_annuity_payment = bob.mortage_credit * (bob.mortgage_pp / 100) 
        / (1 - (1 + bob.mortgage_pp / 100) ^ (-bob.mortgage_srok));
    bob.bank_account -= bob.mortgage_annuity_payment;
    --bob.mortgage_srok;
}


void bob_house_inflation(const int year, const int month)
{
    if (month == 1)  bob.house_price += (Money)(bob.house_price * bob.inflation_pp / 100.0); 
}


void bob_expenses(const int year, const int month)
{
    bob.bank_account -= bob.expenses;  // формула расчёта месячных расходов Боба
    if (month == 1)  bob.expenses += (Money)(bob.expenses * bob.inflation_pp / 100.0);  // учёт годовой инфляции
}


void print_person(const struct Person person)  // Функция для вывода данных по человеку в рублях
{
    printf("bank_account = %lld, house_price = %lld %s\n", 
        person.bank_account / 100, 
        person.house_price / 100, 
        person.name);
}


void simulation()  // функция хода времени
{
    int month = 9;
    int year = 2023;
    while ( !(year == 2053 && month == 9)) {
        alice_deposite_income(year, month);  
        alice_salary_income(year, month);  
        alice_rent(year, month); 
        alice_expenses(year, month); // расходы Алисы на еду, одежду, отдых

        bob_deposite_income(year, month);  
        bob_salary_income(year, month); 
        bob_mortgage(year, month); 
        bob_expenses(year, month);  // расходы Боба на еду, одежду, отдых
        bob_house_inflation(year, month);  // учёт годовой инфляции на недвижимость

        ++month;
        if (month == 13) {
            month = 1;
            ++year;
        }
    }
}


int main()
{
    alice_init();
    bob_init();

    simulation();
     
    print_person(alice);
    print_person(bob);
    return 0;
}
