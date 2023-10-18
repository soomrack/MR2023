#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

void main(void)
{
    struct Matrix A, B, RES;

    int run = 1, choise;
    double multiplier;

    srand(time(NULL));

    while (run)
    {
        printf("\n\n0 - exit\n"
            "1 - initialization\n"
            "2 - free matrix\n"
            "3 - print matrix\n"
            "4 - summ matrix\n"
            "5 - mult matrix\n"
            "6 - mult matrix on a multiplier\n"
            "7 - transposition\n"
            "8 - difference\n"
            "9 - determinant\n"
            "10 - exponential\n"
            "\n");

        scanf_s("%d", &choise);

        switch (choise)
        {
        case 0: 
            run = 0;
            break;
        case 1:
            mat_type = random;
            matrix_initialization(&A, 3, 3);
            mat_type = random;
            matrix_initialization(&B, 3, 3);
            mat_type = random;
            matrix_initialization(&RES, 3, 3);
            break;
        case 2:
            matrix_free(&A);
            matrix_free(&B);
            matrix_free(&RES);
            break;
        case 3:
            matrix_print(&A);
            matrix_print(&B); 
            matrix_print(&RES);
            break;
        case 4:
            matrix_summ(&A, &B, &RES);
            break;
        case 5:
            matrix_mult(&A, &B, &RES);
            break;
        case 6:
            printf("enter a number ");
            scanf_s("%lf", &multiplier);
            printf("enter a number %lf", multiplier);
            matrix_mult_on_number(&A, &RES, multiplier);
            break;
        case 7:
            transposition(&A, &RES);
            break;
        case 8:
            matrix_difference(&A, &B, &RES);
            break;
        case 9:
            printf("determinan = %.1lf\n", determinant(&A));
            break;
        case 10:
            matrix_exponential(&A, &RES);
            break;
        default:
            printf("wrong choise\n");
            break;
        }
    }
}