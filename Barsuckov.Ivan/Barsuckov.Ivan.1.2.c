/*Примеры усложнений:
1. ставка в банке меняется
2. зп в какой-то момент меняется (исчезает)
3. Если на счёте больше 5 млн, то ставка по вкладу на 1% выше
4. Раз в 10 лет они тратят 500000 на зубы 
5. ...*/


#include <stdio.h>
#include <math.h>

typedef long long int Money;// копейки


struct Person {
    Money bank_account;
    Money salary;
};


struct Person alice;
struct Person bob;

void alice_init()
{
    alice.bank_account = 1000 * 1000 * 100;
    alice.salary = 200 * 1000 * 100;
}


void bob_init()
{
    bob.bank_account = 1000 * 1000 * 100;
    bob.salary = 200 * 1000 * 100;
}

void print_alice()
{
    printf("Alice:\n");
    printf(" bank account = %lld\n", alice.bank_account);
}


void print_bob()
{
    printf("Bob:\n");
    printf(" bank account = %lld\n", bob.bank_account);
}



int Count_year = 20;
void simulation()
{
    int month = 9;
    int year = 2023;

    while (year != (year + Count_year) && month != 8) {

        alice_salary_income(year, month);
        alice_deposite_income(year, month);
        alice_rent(year, month);
        alice_food(year, month);
        //alice_hamster(year, month);


        bob_salary_income(year, month);
        bob_deposite_income(year, month);
        //bob_rent(year, month);


        ++month;
            if (month == 13) {
                ++year;
                month = 1;
            }


    }
}



void alice_salary_income(const int year, const int month) //чтобы прибавить зп Алисы и учесть непостоянность зп
{
    if (year == 2024 && month == 10) 
    { 
        alice.salary = 0; 
    }
    if (year == 2024 && month == 11) 
    { 
        alice.salary = 200 * 1000 * 100; 
    }

    alice.bank_account += alice.salary;
}



void alice_deposite_income(const int year, const int month) //прибавляет к счёту проценты с вложения Алисы
{
    int percent_rate = 7; //процентная ставка
    alice.bank_account += (Money)(alice.bank_account*(percent_rate / 100.0 / 12.0));
}


void alice_rent(const int year, const int mount)  //вычитает из счёта Алисы стоимость за квартиру
{
    alice.bank_account -= 35000 * 100;
}


void alice_food(const int year, const int mount)
{
    alice.bank_account -= 15000 * 100;
}



void bob_salary_income(const int year, const int mount) //чтобы прибавить зп Боба и учесть непостоянность зп
{
    bob.bank_account += bob.salary;
}


void bob_deposite_income(const int year, const int mount) //прибавляет к счёту проценты с вложения Боба
{
    
    int total_month = Count_year * 12; //сколько всего месяцев платят кредит
    double bet_mortgage = 0.07; //пр-я ставка за ипотеку
    
    bob.bank_account -= (Money)(bob.bank_account* ((bet_mortgage / 12.0 * pow(1 + bet_mortgage / 12.0, total_month)) / (pow(1 + bet_mortgage / 12.0, total_month) - 1)));
}



int main()
{
    alice_init();
    bob_init();

    simulation();

    print_alice();
    print_bob();

    return 0;

}