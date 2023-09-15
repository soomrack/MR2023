
#include <stdio.h>



int main()
{
    typedef long long int Money;
    Money ipoteka = 20*1000*1000*100; //копейки
    Money kvartira = 20*1000*1000*100; //копейки
    Money ostatok = 0; //копейки
    Money vklad = 0; //копейки
    
    double percent = 1.07;
    double rper = 0.07;
        
    struct Person {
        int zp;
        int trata;
        int ost_zp;
        Money vznos;
    };

    struct Person Bob;
    Bob.zp = 200 * 1000 * 100; //копейки
    Bob.trata = 70 * 1000 * 100; //копейки
    Bob.ost_zp = Bob.zp - Bob.trata; //копейки
    Bob.vznos = 1000 * 1000 * 100;  //копейки

    struct Person Alice;
    Alice.zp = 200 * 1000 * 100; //копейки
    Alice.trata = 70 * 1000 * 100; //копейки
    Alice.ost_zp = Alice.zp - Alice.trata; //копейки
    Alice.vznos = 1000 * 1000 * 100;  //копейки
    
    //Bob

    ipoteka = ipoteka - Bob.vznos;

    for (int a = 0; a < 30; ++a) {
        for (int i = 0; i < 12; ++i) {

            ipoteka += (Money)((double)ipoteka * rper / 12.0);
            ipoteka = ipoteka - Bob.ost_zp;

            if (ipoteka < 0)
                ostatok = 0 - ipoteka;
            if (i != 0)
                Bob.trata = (int)((double)Bob.trata * rper);

            Bob.ost_zp = Bob.zp - Bob.trata;

        }

        if (a != 0) {
            Bob.zp = (int)((double)Bob.zp * percent);
            kvartira = (Money)((double)kvartira * percent);
        }

    }
        
    //Alice

    for (int a = 0; a < 30; ++a) {
        for (int i = 0; i < 12; ++i) {
            vklad = vklad + Alice.ost_zp;
            vklad += (Money)((double)vklad * rper / 12.0);
            if (i != 0) {
                Alice.trata = (int)((double)Alice.trata * rper);
            }
            Alice.ost_zp = Alice.zp - Alice.trata;

        }
        if (a != 0) 
            Alice.zp = (int)((double)Alice.zp * percent);
        
    }
    
    ostatok = ostatok / 100; //рубли
    kvartira = kvartira / 100; //рубли
    vklad = vklad / 100; //рубли

    printf("\nU boba est' i kvartira, i den'gi na schetu: %lld\n", ostatok);
    printf("Pri etom kvartira uzhe stoit: %lld\n", kvartira);

    printf("\nU alice na vklade: %lld\n", vklad);
}
