#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix.h"


void error_control(enum Error_type error){
    if (error == memory_alloccation_error)
        printf("no memory was allocated for the array\n");
    if (error == false_matrix)
        printf("the original matrix is incorrect or difficult to calculate\n");
}


void filling_with_zeros(struct Matrix* M){
    memset(M->data, 0.0, M->col * M->row);
}


int matrix_print(struct Matrix* M){
    if (M->data == NULL)
    {
        printf("Matrix are empty\n");
        return 0;
    }

    for (unsigned int row = 0; row < M->row; row++)
    {
        printf("[");
        for (unsigned int col = 0; col < M->col; col++)
        {
            printf("%.1f", M->data[row * M->col + col]);
            if (col != M->col - 1)
                printf("\t");
        }
        printf("]\n");
    }
    printf("\n\n");
    return 1;
}


void memory_allocation(struct Matrix* M){
    M->data = (double*)malloc(sizeof(double) * M->col * M->row);
    if (M->data == NULL)
        error_control(memory_alloccation_error);
}


void fill_matrix(struct Matrix* M){
    if (mat_type == zero)
        for (unsigned int counter = 0; counter < M->col * M->row; counter++)
            M->data[counter] = 0.0;

    if (mat_type == ones)
        for (unsigned int counter = 0; counter < M->col * M->row; counter++)
            M->data[counter] = 1.0;

    if (mat_type == random)
        for (unsigned int counter = 0; counter < M->col * M->row; counter++)
            M->data[counter] = (double)(rand() % 100);
}


void matrix_initialization(struct Matrix* M, unsigned int row, unsigned int col){
    M->row = row;
    M->col = col;
    memory_allocation(M);

    printf("your matrix %d x %d\n", M->row, M->col);

    fill_matrix(M);
}


void matrix_difference(struct Matrix* A, struct Matrix* B, struct Matrix* RES){
    for (unsigned int counter = 0; counter < A->row * A->col; counter++)
        RES->data[counter] = B->data[counter] - A->data[counter];
}


void matrix_summ(struct Matrix* A, struct Matrix* B, struct Matrix* RES){
    for (unsigned int counter = 0; counter < A->row * A->col; counter++)
        RES->data[counter] = B->data[counter] + A->data[counter];
}


void matrix_mult_on_number(struct Matrix* A, struct Matrix* RES, double multiplier){
    for (unsigned int counter = 0; counter < A->row * A->col; counter++)
        RES->data[counter] = multiplier * A->data[counter];
}


void matrix_mult(struct Matrix* A, struct Matrix* B, struct Matrix* RES){
    filling_with_zeros(RES);

    for (unsigned int row = 0; row < A->row; row++)
        for (unsigned int col = 0; col < A->col; col++)
            for (unsigned int counter = 0; counter < A->col; counter++)
                RES->data[row * A->col + col] += A->data[row * A->col + counter] * B->data[counter * A->col + col];
}

void transposition(struct Matrix* A, struct Matrix* RES){
    filling_with_zeros(RES);

    for (unsigned int row = 0; row < A->row; row++)
        for (unsigned int col = 0; col < A->col; col++)
            RES->data[row * A->row + col] = A->data[col * A->col + row];
}

double determinant(struct Matrix* A){
    unsigned row_end = A->row, col_end = A->col;
    double* counter_A = A->data;


    if (A->col == 2)
        return *A->data * A->data[3] - A->data[1] * A->data[2];
    else if (A->col == 3)
        return (A->data[0] * A->data[4] * A->data[8]) + \
                (A->data[1] * A->data[5] * A->data[6]) + \
                (A->data[2] * A->data[3] * A->data[7]) - \
                (A->data[2] * A->data[4] * A->data[6]) - \
                (A->data[0] * A->data[5] * A->data[7]) - \
                (A->data[1] * A->data[3] * A->data[8]);
    else
    {
        error_control(false_matrix);
        return 0;
    }
}

void matrix_free(struct Matrix* M){
    free(M->data);
    M->col = 0;
    M->row = 0;
    M->data = NULL;
}

unsigned int factorial(unsigned int n){
    unsigned int res = 1;

    for (unsigned int i = 1; i <= n; i++)
        res *= i;
    return res;
}


void matrix_exponential(struct Matrix* M, struct Matrix* RES) {
    unsigned int n = 4;

    for (unsigned int row = 0; row < M->row; row++)
        for (unsigned int col = 0; col < M->col; col++) {
            if (col == row)
                RES->data[row * M->col + col] = 1.;
            else
                RES->data[row * M->col + col] = 0.;
            for (unsigned int counter = 1; counter < n; counter++) 
                RES->data[row * M->col + col] += ((M->data[row * M->col + col]) / factorial(counter));           
        }
}