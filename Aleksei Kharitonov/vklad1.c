#include <stdio.h>
#include <math.h>
int main()
{
	const int nachkapital = 1000000;  
	const int kv = 20000000;  
	const int plusvklad = 1+(0.11/12);
    const int plusip = 1.07;
	const int zp = 200000;
	const int trAlice = 30000;
	const int trBob = 10000;  
	const int inflation = 1.07;

   double moneyAlice = nachkapital; 
   double zpAlice = zp;
   double tratyAlice = trAlice;
    for (int j = 1; j <= 30; j++) //alice
    {

        for (int i = 1; i <= 12; i++)
        {

            moneyAlice = (moneyAlice+zpAlice+tratyAlice) * plusvklad;

        }
        zpAlice= zpAlice * inflation;
        tratyAlice = tratyAlice * inflation;
       
    }
    double moneyBob = 0;
    double zpBob = zp;
    double tratyBob = trBob;
    double nedvizh = kv;

    double platezh = ((kv - nachkapital)*plusip)/(12*30);

    for (int j = 1; j <= 30; j++) //Bob
    {

        for (int i = 1; i <= 12; i++)
        {

            moneyBob = moneyBob + zpBob + tratyBob + platezh;

        }
        zpBob = zpBob * inflation;
        tratyBob = tratyBob * inflation;
        nedvizh = nedvizh * inflation;
    }
    moneyBob = moneyBob + nedvizh;
    printf("Alice: %.0f \n", moneyAlice);
    printf("Bob: %.0f \n", moneyBob);
    printf("platezh: %.0f \n", platezh);
    return 0;
}