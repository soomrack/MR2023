#pragma once
typedef struct
{
    int rows;
    int cols;
    int valid;
    double* data;
} Matrix;
Matrix Matrix_create(int rows, int cols);
void Matrix_free(Matrix mat);
void Matrix_display(Matrix* mat);
Matrix Matrix_add(Matrix* mat1, Matrix* mat2);
Matrix Matrix_multiply(Matrix* mat1, Matrix* mat2);
Matrix Matrix_exponential(const Matrix* mat);
int Matrix_determinant(const Matrix* mat);
