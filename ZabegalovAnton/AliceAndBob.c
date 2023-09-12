#include <stdio.h>

int main(void)
{
    float a, av, b, bv, bp, bk;
    a=0;
    b=0;
    av=1000000;
    bv=0;
    bp=147306.8;
    bk=20000000;
    for(int i=0; i<240; i++){
        bk=bk+bk*0.07/12;
        bv=bv+bv*0.09/12;
        av=av+av*0.09/12;
        av=av+200000-15000-35000;
        if(i==239)
        break;
        bv=bv+200000-bp-15000-5000;
    }
    bv=bv+200000-142021.9-15000-5000;
    b=bv+bk;
    a=av;
    if(a>b)
    printf("Не бери кредит");
    else 
    printf("Бери кредит");
    printf("\na=%.2f\nb=%.2f", a, b);
return 0;
}  