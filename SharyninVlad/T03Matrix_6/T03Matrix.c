#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"

void main(void)
{
    struct Matrix A, B, C;

    int run = 1, choise, flag = 0;
    double multiplier;

    srand(time(NULL));

    while (run)
    {
        printf("\n0 - exit\n"
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
            A = matrix_create(3, 3, I);
            B = matrix_create(3, 3, I);
            flag = 1;
            break;
        case 2:
            matrix_free(&A);
            matrix_free(&B);
            break;
        case 3:
            matrix_print(&A);
            matrix_print(&B);
            break;
        case 4:
            C = matrix_sum(A, B);
            matrix_print_free(&C);
            break;
        case 5:
            C = matrix_mult(A, B);
            matrix_print_free(&C);
            break;
        case 6:
            multiplier = 4;
            C = matrix_mult_on_number(A, multiplier);
            matrix_print_free(&C);
            break;
        case 7:
            C = transposition(A);
            matrix_print_free(&C);
            break;
        case 8:
            C = matrix_subst(A, B);
            matrix_print_free(&C);
            break;
        case 9:
            printf("determinan = %.1lf\n", determinant(A));
            break;
        case 10:
            C = matrix_exponential(A, 25);
            matrix_print_free(&C);
            break;
        default:
            printf("wrong choise\n");
            break;
        }
    }
    if (flag == 1) {
        matrix_free(&A);
        matrix_free(&B);
    }
    
}