#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

const double EPS = 0.00000001;

typedef struct Matrix
{
    unsigned int rows;
    unsigned int cols;
    double *data;
} Matrix;

Matrix memory_allocation(const unsigned int rows, const unsigned int cols)
{
    Matrix mem = {rows, cols, NULL};
    mem.data = (double *)malloc(rows * cols * sizeof(double));
    if (mem.data == NULL)
    {
        mem.rows = 0;
        mem.cols = 0;
        printf("Error:memory are not allocated\n");
    }
    return mem;
}


// Создание матрицы заполненной нулями
Matrix create_zero(const unsigned int rows, const unsigned int cols)
{
    Matrix matrix = memory_allocation(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++)
        matrix.data[idx] = 0.0;
    return matrix;
}

Matrix create_identity(const unsigned int size)
{ // Создание единичной матрицы
    Matrix mat = create_zero(size, size);
    for (unsigned int idx = 0; idx < size * size; idx += size + 1)
        mat.data[idx] = 1.0;
    return mat;
}

void matrix_free(Matrix *A) 
{
    free(A->data);
}

Matrix EMPTY()
{ // Нулевая матрица в случае ошибочного ввода
    Matrix EMPTY = memory_allocation(0, 0);
    EMPTY.data = NULL;
    return EMPTY;
}

Matrix fill_random(Matrix matrix)
{
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++)
    {
        matrix.data[index] = rand() % 10;
    }
    return matrix;
}

void output(const char *function_name, Matrix A)
{ // Блок вывода
    printf("\n%s\n", function_name);
    for (unsigned int row = 0; row < A.rows; row++)
    {
        for (unsigned int col = 0; col < A.cols; col++)
        {
            printf("%lf ", A.data[row * A.cols + col]);
        }
        printf("\n"); // перевод на новую строку
    }
}

Matrix fill_from_array(double* array, const unsigned int rows, const unsigned int cols)
{
    Matrix matrix = memory_allocation(rows, cols);
    memcpy(matrix.data, array, rows * cols * sizeof(double));
    return matrix;
}

Matrix addition(Matrix A, Matrix B)
{
    if ((A.rows != B.rows) || (A.cols != B.cols))
    {
        printf("For Addition Matrix should have same size\n");
        return EMPTY();
    }
    Matrix sum = memory_allocation(A.rows, A.cols);
    for (unsigned int index = 0; index < A.rows * A.cols; index++)
    {
        sum.data[index] = A.data[index] + B.data[index];
    }
    return sum;
}

Matrix substact(Matrix A, Matrix B)
{
    if ((A.rows != B.rows) || (A.cols != B.cols))
    {
        printf("For Addition Matrix should have same size\n");
        return EMPTY();
    }
    Matrix sub = memory_allocation(A.rows, A.cols);
    for (unsigned int index = 0; index < A.rows * A.cols; index++)
    {
        sub.data[index] = A.data[index] - B.data[index];
    }
    return sub;
}

Matrix multiplication(const Matrix A, const Matrix B)
{
    if (A.cols != B.rows)
    {
        printf("For Multiplication First Matrix cols should equal to Second Matrix rows\n");
        return EMPTY();
    }
    Matrix multy = memory_allocation(A.rows, B.cols);
    for (unsigned int row = 0; row < multy.rows; row++)
    {
        for (unsigned int col = 0; col < multy.cols; col++)
        {
            double sum = 0;
            for (unsigned int k = 0; k < A.cols; k++)
            {
                sum += A.data[row * A.cols + k] * B.data[k * B.cols + col];
            }
            multy.data[row * multy.cols + col] = sum;
        }
    }
    return multy;
}

Matrix multy_k(const Matrix matrix, const double k)
{ // Умножение матрицы на число
    Matrix multy = memory_allocation(matrix.rows, matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++)
    {
        multy.data[index] = matrix.data[index] * k;
    }
    return multy;
}

Matrix division_k(const Matrix matrix, const double k)
{ // Деление матрицы на число
    Matrix division = memory_allocation(matrix.rows, matrix.cols);
    for (unsigned int index = 0; index < matrix.rows * matrix.cols; index++)
    {
        division.data[index] = matrix.data[index] / k;
    }
    return division;
}

Matrix minor(const Matrix matrix, const unsigned int row, const unsigned int col)
{ // Минор
    Matrix minor = memory_allocation(matrix.rows - 1, matrix.cols - 1);
    unsigned int shiftrow = 0; // Смещение индекса строки в матрице
    unsigned int shiftcol;     // Смещение индекса столбца в матрице
    for (unsigned int rows = 0; rows < minor.rows; rows++)
    {
        // Пропустить rows-ую строку
        if (rows == row)
            shiftrow = 1; // Как только встретили строку, которую надо пропустить,
        // делаем смещение для исходной матрицы
        shiftcol = 0; // Обнулить смещение столбца
        for (unsigned int cols = 0; cols < minor.cols; cols++)
        {
            if (cols == col)
            {
                shiftcol = 1;
            }
            minor.data[rows * minor.cols + cols] = matrix.data[(rows + shiftrow) * matrix.cols + (cols + shiftcol)];
        }
    }
    return minor;
}


double determinant(const Matrix matrix, const unsigned int size)
{// Определитель с рекурсивным вызовом
    if (matrix.rows != matrix.cols)
    {
        printf("Matrix should be nxn\n");
        return 0;
    }
    double det = 0;
    int k = 1;
    if (size == 0)
        return 0;
    if (size == 1)
        return matrix.data[0];
    if (size == 2)
    return (matrix.data[0] * matrix.data[3] - matrix.data[2] * matrix.data[1]);
    for (unsigned int idx = 0; idx < size; idx++)
    {
        Matrix temp = minor(matrix, 0, idx);
        det += k * matrix.data[idx] * determinant(temp, size - 1);
        k = -k;
        matrix_free(&temp);
    }
    return det;
}

// Транспонирование матрицы
Matrix transposition(const Matrix A)
{
    Matrix trans = memory_allocation(A.cols, A.rows);
    for (unsigned int row = 0; row < trans.rows; row++)
    {
        for (unsigned int col = 0; col < trans.cols; col++)
        {
            trans.data[row * trans.cols + col] = A.data[col * trans.rows + row];
        }
    }
    return trans;
}

Matrix reverse_matrix(const Matrix A, const unsigned int size)
{ // Функция нахождения обратной матрицы
    double det = determinant(A, size);
    if (A.rows != A.cols)
    {
        printf("Matrix should have size nxn\n");
        return EMPTY();
    }
    if (fabs(det) < EPS)
    {
        printf("Matrix is degenerative, determinate is not determined\n");
        return EMPTY();
    }
    Matrix reverse = memory_allocation(size, size);
    Matrix temp;
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++)
    {
        for (unsigned int col = 0; col < reverse.cols; col++)
        {
            temp = minor(A, row, col);
            reverse.data[row * size + col] = k * determinant(temp, size - 1);
            k = -k;
        }
        matrix_free(&temp);
    }
    Matrix temp_transpose = transposition(reverse);
    matrix_free(&reverse);
    Matrix temp_division = division_k(temp_transpose, det);
    matrix_free(&temp_transpose);
    reverse = temp_division;
    return reverse;
}

Matrix exponent_matrix(const Matrix matrix, const unsigned int n)
{ // Функция нахождения экспоненты матрицы

    if (matrix.rows != matrix.cols)
    {
        printf("Matrix should have size nxn\n");
        return EMPTY(); // Если матрица не квадратная, возвращаем пустую матрицу
    }

    Matrix ex = create_identity(matrix.rows); // Создаем единичную матрицу того же размера

    Matrix temp = create_identity(matrix.rows); // Создаем временную единичную матрицу

    Matrix temp_multiply; // Создаем временную матрицу для хранения результата умножения временной матрицы на исходную матрицу.

    Matrix temp_add; // Создаем временную матрицу для хранения результата сложения матриц ex и temp с делением.

    double fact = 1.0; // Инициализируем переменную fact, которая будет хранить факториал числа i.

    for (unsigned int i = 1; i < n; i++)
    {
        fact *= i; // Увеличиваем значение факториала на каждой итерации.

        temp_multiply = multiplication(temp, matrix); // Умножаем временную матрицу temp на исходную матрицу exponent.

        matrix_free(&temp); // Освобождаем память, занимаемую временной матрицей temp, так как она больше не нужна.

        temp = temp_multiply; // Передаем результат умножения в temp.

        temp_add = addition(ex, division_k(temp, fact)); // Складываем матрицы ex и temp с делением на fact.

         matrix_free(&ex); // Освобождаем память, занимаемую матрицей ex, так как она больше не нужна.

        ex = temp_add; // Передаем результат сложения в ex.
    }

    matrix_free(&temp_multiply); // Освобождаем память, занимаемую временной матрицей temp_multiply.

    return ex; // Возвращаем результат экспоненциации матрицы.
}