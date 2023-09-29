#include <stdio.h>
#include <math.h>

int main(void)
{
    double flatprice = 20000000;
    int salary = 200000;
    int food = 5000;
    int utilities = 15000;
    int capital = 1000000;
    int infl = 7;
    int depositperc = 9;
    int interestperc = 7;
    int years = 20;
    int month = years*12;
    int rent = 30000;
    double alicetotal = capital;
    double bobtotal = 0;

    double mor_per = interestperc/12.0/100.0;
    double dep_per = 1+depositperc/12.0/100.0;
    double mortgage = (flatprice - capital)*((mor_per*pow(1+mor_per,month))/(pow(1+mor_per,month)-1));
    double aliceadd = salary - food - utilities - rent;
    double bobadd = salary - food - utilities - mortgage;

    int i = 0;
    while (i<month)
    {
        alicetotal *= dep_per;
        alicetotal += aliceadd;
        bobtotal *= dep_per;
        bobtotal += bobadd;
        
        if (i%12==0)
        {
            flatprice *= (1+(double)infl/100.0);
        }
        i++;     
    }
    
    bobtotal += flatprice;

    printf("Alice capital =  %f, Bob capital =  %f\n", alicetotal, bobtotal);
    if (alicetotal>bobtotal)
        printf("Alice has larger capital\n");
    else
        printf("Bob has larger capital\n");
    
    
    Test commit

}