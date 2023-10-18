#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Matrix {
    unsigned int row;
    unsigned int col;
    double* data;
};

enum Matrix_type { zero, ones, random } mat_type;
enum Error_type { memory_alloccation_error, false_matrix };

void error_control(enum Error_type error);
void filling_with_zeros(struct Matrix* M);
int matrix_print(struct Matrix* M);
void memory_allocation(struct Matrix* M);
void fill_matrix(struct Matrix* M);
void matrix_initialization(struct Matrix* M, unsigned int row, unsigned int col);
void matrix_difference(struct Matrix* A, struct Matrix* B, struct Matrix* RES);
void matrix_summ(struct Matrix* A, struct Matrix* B, struct Matrix* RES);
void matrix_mult_on_number(struct Matrix* A, struct Matrix* RES, double multiplier);
void matrix_mult(struct Matrix* A, struct Matrix* B, struct Matrix* RES);
void transposition(struct Matrix* A, struct Matrix* RES);
double determinant(struct Matrix* A);
void matrix_free(struct Matrix* M);
void matrix_exponential(struct Matrix* M, struct Matrix* RES);
unsigned int factorial(unsigned int n);