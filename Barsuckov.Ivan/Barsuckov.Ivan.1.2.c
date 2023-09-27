/*Ïðèìåðû óñëîæíåíèé:
1. ñòàâêà â áàíêå ìåíÿåòñÿ
2. çï â êàêîé-òî ìîìåíò ìåíÿåòñÿ (èñ÷åçàåò)
3. Åñëè íà ñ÷¸òå áîëüøå 5 ìëí, òî ñòàâêà ïî âêëàäó íà 1% âûøå
4. Ðàç â 10 ëåò îíè òðàòÿò 500000 íà çóáû 
5. ...*/


#include <stdio.h>
#include <math.h>

typedef long long int Money;// êîïåéêè


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
        bob_rent_income(year, month);
        //bob_deposite(year, month);


        ++month;
            if (month == 13) {
                ++year;
                month = 1;
            }


    }
}



void alice_salary_income(const int year, const int month) //÷òîáû ïðèáàâèòü çï Àëèñû è ó÷åñòü íåïîñòîÿííîñòü çï
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



void alice_deposite_income(const int year, const int month) //ïðèáàâëÿåò ê ñ÷¸òó ïðîöåíòû ñ âëîæåíèÿ Àëèñû
{
    int percent_rate = 7; //ïðîöåíòíàÿ ñòàâêà
    alice.bank_account += (Money)(alice.bank_account*(percent_rate / 100.0 / 12.0));
}


void alice_rent(const int year, const int mount)  //âû÷èòàåò èç ñ÷¸òà Àëèñû ñòîèìîñòü çà êâàðòèðó
{
    alice.bank_account -= 35000 * 100;
}


void alice_food(const int year, const int mount)
{
    alice.bank_account -= 15000 * 100;
}



void bob_salary_income(const int year, const int mount) //÷òîáû ïðèáàâèòü çï Áîáà è ó÷åñòü íåïîñòîÿííîñòü çï
{
    bob.bank_account += bob.salary;
}


void bob_rent_income(const int year, const int mount) //ïðèáàâëÿåò ê ñ÷¸òó ïðîöåíòû ñ âëîæåíèÿ Áîáà
{
    
    int total_month = Count_year * 12; //ñêîëüêî âñåãî ìåñÿöåâ ïëàòÿò êðåäèò
    double bet_mortgage = 0.07; //ïð-ÿ ñòàâêà çà èïîòåêó
    
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
