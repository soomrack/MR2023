#include <stdio.h>
int main()
        {
    int nach, kvart, i, j ; //начальный капитал, стоимость квартиры, срок

    float procvclad, doxod, razhod, trativmesicA, trativmesicB, inf; // процент вклада, доход, траты на жизнь, траты на квартиру А и B.

    float kapitalA, kapitalB, moneyB;

    nach = 1000000;
    kvart = 20000000;
    procvclad = 0.11;
    doxod = 200000;
    razhod = 60000; 
    trativmesicB = 10000 + 126407;
    trativmesicA = 30000;
    inf = 1.07; 
    kapitalA = nach;
    kapitalB = 0;
    moneyB = 0;

    for (j = 1; j <= 30; j++ ) {

        for (i = 1; i <= 12; i++)
        {

            kapitalA = kapitalA+kapitalA*procvclad/12 + doxod - razhod - trativmesicA;
            moneyB = moneyB+moneyB*procvclad/12 + doxod - razhod - trativmesicB;

        }

        doxod = doxod * inf;
        razhod = razhod * inf;
        trativmesicA = trativmesicA * inf;
        kvart = kvart * 1.07;
    }

    kapitalB = moneyB + kvart; 
    printf ("Каптал A: %.0f \n", kapitalA);
    printf("Каптал B: %.0f \n", kapitalB);
    
    return 0;
}