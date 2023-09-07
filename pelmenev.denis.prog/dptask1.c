#include <stdio.h>
#include <math.h>

int S = 2000000;
int p = 200000;
int X0 = 1000000;
int t = 20;
double infl = 0.07;
double st = 0.09;
int mw = 15000;
int rp = 30000;

double Perspective (char word) {
    double pp = p;
    double X = 0;
    double ppm;
    double Xa = 0;
    if (word == 'A') {
        ppm = rp;
        X = X0;
        Xa = S*powf((1+infl), t);
    }
    else if (word == 'B') {
        ppm = (S-X0)*(st/12)/(1-powf((1+st/12), (1-t*12)));
    }
    else {
        printf("Who is this? \n");
        return 0;
    };
    int i = 0;
    while (i<t*12) {
        i+=1;
        X = (X + pp - ppm - mw) * (1 + st/12);
        if ((i%12==0)&&(i>11)) {
            pp = pp*(1+infl);
        };
    };
    X = X - Xa;
    return X;
}

int main(void) {
    double a, b, c;
    a = Perspective(65);
    b = Perspective(66);
    c = Perspective(67);
    printf("%2f\n", a, "\n");
    printf("%2f\n", b, "\n");
    printf("%2f\n", c, "\n");
    return 0;
}
