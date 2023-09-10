#include <stdio.h>

int main() {
    double doxod = 200000;
    double rasxodAlice = 50000;
    double rasxodBob = 30000;
    double vkladAlice = 1000000;
    double vkladBob = 0;
    double capitalAlice;
    double capitalBob;
    double procentvklad = 1 + 0.11 / 12;
    double procentinf = 1 + 0.07 / 12;
    double kvartira = 20000000;

    for (int i = 0; i < 30; i++)
    {
        for (int i = 0; i < 12; i++)
        {
            
            vkladAlice = (vkladAlice + doxod - rasxodAlice) * (procentvklad);
            vkladBob = (vkladBob + doxod - rasxodBob - 126407.47) * (procentvklad);
            capitalAlice = vkladAlice;
            capitalBob = vkladBob;
            rasxodAlice = rasxodAlice * (procentinf);
            rasxodBob = rasxodBob * (procentinf);
            kvartira = kvartira * procentinf;
        } 
        doxod = doxod * 1.07;
    }
    capitalBob = capitalBob + kvartira;
    if (capitalAlice > capitalBob)
    {
        printf("Стратегия Alice выгодней");
    }
    else
    {
        printf("Стратегия Bob выгодней");
    }
    return 0;
}