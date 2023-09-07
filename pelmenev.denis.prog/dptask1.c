#include <stdio.h>
#include <math.h>

int S = 2000000;
int p = 200000;
int X0 = 1000000;
int t = 20;
double infl = 0.07;
double st = 0.09;
int mw = 15000;

double Bob (double Ss) {
    int Xb = Ss - X0;
    double ppm;
    ppm = Xb*(st/12)/(1-powf((1+st/12), (1-t*12)));
    int i = 0;
    double zp = 0;
    double pp = p;
    while (i<t*12) {
        i+=1;
        zp = (zp + pp - ppm - mw) * (1 + st/12);
        if ((i%12==0)&&(i>11)) {
            pp = pp*(1+infl);
        };
    };
    return zp;
}

double Alice (double Ss) {
    double Sa;
    Sa = Ss*powf((1+infl), t);
    double Xa = X0;
    int i = 0;
    double pp = p;
    int rp = 30000;
    while (i<t*12) {
        i+=1;
        Xa = (Xa + pp - rp - mw) * (1 + st/12);
        if ((i%12==0)&&(i>11)) {
            pp = pp*(1+infl);
        };
    };
    Xa = Xa - Sa;
    return Xa;
}

int main(void) {
    double a, b;
    a = Alice(S);
    b = Bob(S);
    printf("%2f\n", a, "\n");
    printf("%2f\n", b, "\n");
    return 0;
}
