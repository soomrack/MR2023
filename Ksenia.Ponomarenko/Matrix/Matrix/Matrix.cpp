#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

typedef double MatrixItem;

typedef struct Matrix {
    size_t rows;
    size_t cols;
    MatrixItem* data;
} Matrix;


const Matrix NULL_MATRIX = { .rows = 0, .cols = 0, .data = NULL };


Matrix matrix_allocation(const size_t rows, const size_t cols)
{
    if (cols == 0 || rows == 0) {
        Matrix A = { .rows = rows, .cols = cols, .data = NULL };
        return A;
    }
    if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) return NULL_MATRIX;

    Matrix A = { .rows = rows, .cols = cols, .data = NULL };
    A.data = (MatrixItem*)malloc(sizeof(MatrixItem) * A.cols * A.rows);
    if (A.data == NULL) return NULL_MATRIX;
    return A;
}


void matrix_delete(Matrix* A)
{
    A->rows = 0;
    A->cols = 0;
    free(A->data);
    A->data = NULL;
}


void matrix_set_zero(Matrix A)
{
    if (A.data == NULL) return;
    memset(A.data, 0, sizeof(MatrixItem) * A.rows * A.cols);// Функция memset возвращает указатель на заполняемый массив. В нашем случае это массив из указателей A.data. ЧТО ЭТО БЛЯТЬ ТАКОЕ ЭТОТ ВАШ МЕМСЕТ.БЛЯТЬ
}


void matrix_set_one(struct Matrix A) 
{
    matrix_set_zero(A);
    for (size_t idx = 0; idx < A.rows * A.cols; idx += A.cols + 1)
        A.data[idx] = 1.;
}


void matrix_print(const struct Matrix A, const char* text) // Как понять, когда писать войд, а когда не войд? Функция вывода в матрице.
{
    printf("%s\n", text);// Какой нахуй текст? Откуда они его вщяли? Где он записан? А, это вообще указатель только на какую-то ячеку памяти, в которую будет записан непонятный текст. Заебись
    for (size_t row = 0; row < A.rows; ++row) { // Col? Почему они считают, что можно просто так взять и с нихуя догбавить переменную? Это столбец. 1 шт.Все еще не поняла, что такое size_t
        //Т.е. начиная по столбцам (хотя изначально в структуре было cols, а не col начинаем заполнять массив пока не достигнется количества стоблцов, которые соответстуют количетсву указателец стоблцов
        printf("[ ");
        for (size_t col = 0; col < A.cols; ++col) { 
            printf("%4.2f ", A.data[A.cols * row + col]);// Знак какой-то новый. Печатает внутрь указателей на дату что-то. Не поняла, почему внутри в кв скобочках [A.cols * row + col]
        }
        printf("]\n");// Закрыли типа один элемент скобошкой
    }
    printf("\n"); //Перенос на др строку
}


void value_print(MatrixItem A, const char* text) // Передаем что? Значение a? Или указатель на значения А? Все еще не понятно, где text
{
    printf("%s\n", text);

    printf("%4.2f ", A);
}


// A += B
void matrix_add( Matrix A, Matrix B) // Функция добавления одинаковой матрицы к первой другой матрице несколько раз? Чем эта функция отличается от следующей?
{
    if (A.cols != B.cols || A.rows != B.rows) return; // Почему return 1? А не 0? Потому что 0 занят ниже? И надо возвращать что-то другое. И это ошибка, ибо нельзя суммировать разнокалиберные матрицы. 
    // Хотя ошибка скорее в следующей функции, а тут не понятно что

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) // Jт куска структуры, под номером 0 (idx=0),до куска структуры меньше умножения столбцов и строк (указателей!) и инкрементировать.
        // Типа мы просто не говорим, пл толбцам или по строкам заполряем, а просто по номерам? А как эти номера идут? Где это написано?
        A.data[idx] += B.data[idx]; // Присваивать каждому элементу увеличенное на значение числа в другом таком же элементе 
}


// C = A + B
 Matrix matrix_sum( Matrix A, Matrix B) // Суммирование двух матриц. Ну тут похоже точно нельзя складывать разнокалиберные
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX; // Почему здесь нулевая, а в предыдущей функции возвращалось 1?

    Matrix C = matrix_allocation(A.cols, A.rows); // Создаем переменную типа структуры Matrix, называем ее sum. Выделяем под нее ячейки памяти через alloc в количестве A.cols /rows
    if (C.data == NULL) return NULL_MATRIX; // Если суммарная матрица выдает пустые указатели (почему-то???) возвращаем нулевую матрицу из 16 строки?
    // переписать ебаный костыль на нормальную релизацию сложения
    memcpy(C.data, A.data, sizeof(MatrixItem) * A.cols * A.rows); // Копируем память от data (к какой именно матрице относится data? Почему не сказали?) Сами указатели на числа в матрице А
    // и количество памяти, равное количествву памяти под все элементы
    matrix_add(C, B); // Добавить C, где мы выделили память под 

    return C;
}


// A -= B
void matrix_sub(struct Matrix A, struct Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        A.data[idx] -= B.data[idx];
}


// D = A - B
Matrix matrix_diff( Matrix A,  Matrix B)
{
    if (A.cols != B.cols || A.rows != B.rows) return NULL_MATRIX;

 Matrix D = matrix_allocation(A.cols, A.rows);
    if (D.data == NULL) return NULL_MATRIX;

    memcpy(D.data, A.data, sizeof(MatrixItem) * A.cols * A.rows); // Здесь A.data - это сколько выделить памяти? Типа откуда скопировать ее объем?
    matrix_add(D, B); // К чему прибавляем, что прибавляем

    return D;
}


// MULT = A * B
 Matrix matrix_mult(Matrix A, Matrix B)
{
    if (A.cols != B.rows) return NULL_MATRIX;

 Matrix mult = matrix_allocation(A.rows, B.cols); //Типа потому что умножение, поэтому надо выделять строки как столбцы, а столбцы, как строки?
    if (mult.data == NULL) return NULL_MATRIX; // Если ничего случайно не записалось, то возвращаем нулевую. Это ошибка так прописана

    for (size_t rowA = 0; rowA < A.rows; ++rowA) {      // Цикл для: вводим новый счетчик (потому что старый уже использовался? Или для понимания, что на что умножается
        // Инкрементируем почему-то по строкам. Это принципиально? Типа есть ли разница в зависимости от функции, по чему суммируем внешний цикл
        for (size_t colB = 0; colB < B.cols; ++colB) {
            MatrixItem sum = 0;                         // Ввели новую локальную переменную double, которая зачем-то суммирует (или просто так называется sum?)
            for (size_t idx = 0; idx < A.cols; ++idx) {     // 
                sum += A.data[rowA * A.cols + idx] * B.data[idx * B.cols + colB];      // Эта изначально в 145 строчке обнуленная сумма прибавляет значение к себе каждвй раз. Это значение
                // Обращается к ОПРЕДЕЛЕННОМУ ЭЛЕМЕНТУ, НЕ К АДРЕСУ БЛЯТЬ. А точнее к строке, которая была вычислена в счетчике выше, умноженной на количество столбцов +текущий номер элемента
                //Не поняла математику. РАЗОБРАТЬСЯ
            }
            mult.data[rowA * mult.cols + colB] = sum; // Здесь описаны значения, которые получаются в результирующей матрице. Они берутся из номеров, которые получаются
            // через умножение строчки, котрая в счетчике и почему-то mult.cols. Откуда там точка? Почему они так к столбцам обращаются? И плюс столбец матрицы B
            //Не поняла математику. Вообще. Нихуя. И это все равно sum (ПОЧЕМУ-ТО)
        }
    }
    return mult;
}


// A *= k
void matrix_mult_k(Matrix A, const MatrixItem k) //  Умножение матрицы на число в ту же матрицу
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) { // Перебирает индексы, которые номера, подряд, внутри одной матрицы. Почемц нет провкрки на долбаеба? Потому что усножаем на число?
        A.data[idx] *= k; // 
    }
    return;
}


// A /= k
void matrix_div_k(struct Matrix A, const MatrixItem k) //Деление матрицы на число в ту же матрицу
{
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        A.data[idx] /= k;
    }
    return;
}


// TPOSE = A^T
struct Matrix matrix_transpose(struct Matrix A)
{
    Matrix tpose = matrix_allocation(A.rows, A.cols);
    if (tpose.data == NULL) return tpose; // Это он так при ошибке возвращает первую нетранспонированную матрицу? Странно, потому что кажется, что мог не нажать или еще что

    for (size_t row = 0; row < tpose.rows; row++) { // А где мы объявили это значение tpose.rows? Это строки из матрицы A, судя по 183 строчке?
        for (size_t col = 0; col < tpose.cols; col++) {
            tpose.data[col * tpose.cols + row] = A.data[row * A.cols + col]; // Заполняем массив транспонированной матрицы. Обращаемся к элементам под номером: столбец по счетчику,
            // умноженный на  столбцы транспонироыанной матрицы (почему??) и плюс к этому умноженному номер строки из счетчика (той же самой, что и столбца).
            //Математику не поняла

        }
    }
    return tpose;
}



// det (A)
MatrixItem matrix_determinant(struct Matrix A)
{
    MatrixItem det;

    if (A.cols == 1 && A.rows == 1) {
        det = A.data[0];
        return det;
    }

    if (A.cols == 2 && A.rows == 2) {
        det = A.data[0] * A.data[3] - A.data[1] * A.data[2];
        return det;
    }

    if (A.cols == 3 && A.rows == 3) {
        det =
            A.data[0] * A.data[4] * A.data[8]
            + A.data[1] * A.data[5] * A.data[6]
            + A.data[2] * A.data[7] * A.data[3]
            - A.data[2] * A.data[4] * A.data[6]
            - A.data[0] * A.data[5] * A.data[7]
            - A.data[1] * A.data[8] * A.data[3];
        return det;
    }

    return NAN;
}


// EXP = e^A
struct Matrix matrix_exp(struct Matrix A)
{
    if (A.cols != A.rows) return NULL_MATRIX;
    if (A.cols == 0) return NULL_MATRIX;

    struct Matrix exp = matrix_allocation(A.rows, A.cols);
    if (exp.data == NULL) return NULL_MATRIX;
    matrix_set_one(exp);

    struct Matrix term_prev = matrix_allocation(A.rows, A.cols);
    if (term_prev.data == 0) {
        matrix_delete(&exp);
        return NULL_MATRIX;
    };
    matrix_set_one(term_prev);

    struct Matrix term_next;

    for (int idx = 1; idx < 100; ++idx) {

        term_next = matrix_mult(term_prev, A);
        if (term_next.data == NULL) {
            matrix_delete(&term_prev);
            matrix_delete(&exp);
            return NULL_MATRIX;
        }
        matrix_div_k(term_next, idx);
        memcpy(term_prev.data, term_next.data, sizeof(MatrixItem) * term_prev.cols * term_prev.rows);
        matrix_delete(&term_next);
        matrix_add(exp, term_prev);

    }
    matrix_delete(&term_prev);
    return exp;
}


// filling the matrix with values
void matrix_fill(struct Matrix A, const double* values)
{
    memcpy(A.data, values, sizeof(MatrixItem) * A.cols * A.rows);
    return;
}