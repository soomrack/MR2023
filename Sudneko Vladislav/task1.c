#include <stdio.h>
#include <math.h>
#include <locale.h>

/*
Вычисляет капитал Алисы.

На старте у неё 1 млн рублей, зарплата 200 тыс рублей,
и она снимает квартиру за 30 тыс рублей. Остальные
жизненные расходы обходятся ей в 30 тыс рублей.

Каждый месяц ей начисляются проценты в банке на остаток по счёту.
Также каждый месяц она кладёт новую сумму в банк - остаток после
выплаты аренды - под 9% годовых. 

Через 20 лет Алиса понимает, что из-за инфляции цены на квартиры стали
настолько высокими, что она уже не сможет её себе позволить. 
*/
double computeAliceBank() {
    double bank = 1000000;
    float salary = 200000;
    float arendPrice = 30000;
    float life = 30000;


    for (int i = 0; i < 240; i++) {
        bank *= 1 + 9/1200;
        bank += salary - arendPrice - life;
    }

    return bank;
}


/*
Вычисляет капитал Боба.

На старте у него пустой банк, так как 1 млн идёт первоначальным взносом, 
зарплата 200 тыс рублей. Остальные
жизненные расходы обходятся ему в 30 тыс рублей.

Боб выплачивает ипотеку аннуитетными платежами,
величина которых известна. Всё, что у него остаётся,
Боб кладёт на счёт под 9% годовых.

Через 20 лет Боб полностью выплачивает кредит, после чего 
продаёт квартиру и увольняется с работы, чтобы остаток жизни
путешествовать и ни о чём не думать.
*/
double computeBobBank() {
    double bank = 0;
    int salary = 200000;
    int life = 30000;
    int percent = 7;
    float monthlyPayment = 147306.8;

    for (int i = 0; i < 240; i++) {
        bank *= 1 + 9 / 1200;
        bank += salary - monthlyPayment - life;
    }

    bank *= 1 + 9 / 1200;
    bank += salary - 142021.9;
    bank += 20000000 * pow(1.07, 20);

    return bank;
}

int main() {
    setlocale(LC_NUMERIC, "");

    double aliceBank = computeAliceBank();
    double bobBank = computeBobBank();

    printf("%i - Alice Bank after 20 years\n", (int)aliceBank);
    printf("%i - Bob Bank after 20 years\n", (int)bobBank);
    printf("Bob is richer than Alice by %i rubles", (int)(bobBank - aliceBank));

    return 0;
}