#include <stdio.h>


typedef long long int Money;


struct Person
{
    Money sallary;
    Money consumption;
    Money contribution;
    Money capital;
    Money hypothec;
    Money appartment;
};


struct Procent
{
    double inflation;
    double contribution;
};


Money summ (Money contribution, Money sallary, Money consumption, Money hypotec, double procent)
{
    Money summ;
    summ = (Money)((double)(contribution + sallary - consumption - hypotec) * procent);
    return summ;
}


void out (Money alice, Money bob)
{
    Money alicek = alice % 100;
    Money alicer = alice / 100;
    Money bobk = bob % 100;
    Money bobr = bob / 100;
    printf("Капитал Алисы: %lld рубля %lld копеек Капитал Боба: %lld рубля %lld копеек\n", alicer, alicek, bobr, bobk);
    if (alice > bob)
    {
        printf("Стратегия Alice выгодней\n");
    }
    else
    {
        printf("Стратегия Bob выгодней\n");
    }
}

int main() {
    struct Person alice = {200 * 1000 * 100, 60 * 1000 * 100, 1000 * 1000 * 100, 0, 0, 0}; // Копейки
    struct Person bob = {200 * 1000 * 100, 30 * 1000 * 100, 0, 0, 12640747, 20 * 1000 * 1000 * 100}; // Копейки
    struct Procent mounth = {1.0 + 0.07 / 12.0, 1.0 + 0.11 / 12.0};
    struct Procent year = {1.07, 0};
        
    for (int i = 0; i < 30; i++)
    {
        for (int i = 0; i < 12; i++)
        {
            alice.contribution = summ(alice.contribution, alice.sallary, alice.consumption, alice.hypothec, mounth.contribution);
            bob.contribution = summ(bob.contribution, bob.sallary, bob.consumption, bob.hypothec, mounth.contribution);
            alice.consumption = summ(alice.consumption, 0, 0, 0, mounth.inflation);
            bob.consumption = summ(bob.consumption, 0, 0, 0, mounth.inflation);
            bob.appartment = summ(bob.appartment, 0, 0, 0, mounth.inflation);
        } 
        alice.sallary = summ(0, alice.sallary, 0, 0, year.inflation);
        bob.sallary = summ(0, bob.sallary, 0, 0, year.inflation);
    }
    alice.capital = alice.contribution;
    bob.capital = bob.contribution + bob.appartment;
    out(alice.capital, bob.capital);
    return 0;
}