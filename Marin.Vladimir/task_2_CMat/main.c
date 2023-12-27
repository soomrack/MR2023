#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <stdio.h>
#include <math.h>
#include <malloc.h>
//#include <stdlib.h>
#include <math.h>
#include <minmax.h>


const unsigned int Max_range = 100;
const double Comparison_const = 0.001;

typedef struct Mat {
    unsigned int cols;
    unsigned int rows;

    double *data;
    double **value;
}Mat;

const Mat NULL_MATRIX = {.cols = 0, .rows = 0, .data = NULL, .value = NULL};

Mat allocate_mat (const unsigned int rows, const unsigned int cols) {

    if (cols == 0 || rows == 0) return NULL_MATRIX;
    if (rows >= SIZE_MAX / sizeof(double) / cols) return NULL_MATRIX;

    Mat rez = {.rows = rows, .cols = cols, .data = NULL, .value = NULL};
    rez.data = (double *) malloc(rows * cols * sizeof(double));
    rez.value = (double**) malloc(rows * sizeof(double *));

    for(unsigned int row = 0; row < rows; row ++){
        rez.value[row] = rez.data + row * cols;
    }
    return rez;
}

void release(Mat x){
    free(x.value);
    free(x.data);
}

Mat copy_matrix (const Mat x) {
   Mat cx = allocate_mat(x.rows, x.cols);
    for (unsigned int number = 0; number < x.cols * x.rows; number ++) {
        cx.data [number] = x.data [number];
    }
    return cx;
}

void output(const Mat x){
    for (unsigned int row = 0; row < x.rows; row++){
        for (unsigned int col = 0; col < x.cols; col++){
            printf("%.2lf ", x.value[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

Mat empty() {
    Mat rez = {0, 0};
    return rez;
}

Mat zero(const unsigned int rows, const unsigned int cols){
    Mat rez = allocate_mat(rows, cols);
    for(unsigned int dx = 0; dx < rows * cols; dx++){
        rez.data[dx]=0.0;
    }
    return rez;
}

Mat one(const unsigned int rows, const unsigned int cols){
    Mat rez = zero(rows, cols);
    for (unsigned int dx = 0; dx < min(rows, cols); dx++){
        rez.value[dx][dx] = 1.0;
    }
    return rez;
}

Mat transponation(Mat x){
    Mat rez = allocate_mat(x.cols, x.rows);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = x.value[col][row];
        }
    }
    return rez;
}

Mat minor(const unsigned int cur_row, const unsigned int cur_col, const Mat x) {
    Mat rez = allocate_mat(x.rows - 1, x.cols - 1);
    unsigned int k = 0;
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++) {
        if ((dx % x.cols != cur_col) && (dx / x.cols != cur_row)) {
            rez.data[k++] = x.data[dx];
        }
    }
    return rez;
}

Mat sum(const Mat x, const Mat y){
    //if (x.data == NULL || y.data == NULL) return empty();
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    Mat rez = allocate_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] + y.data[dx];
    }
    return rez;

}

Mat subtraction(const Mat x, const Mat y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return empty();

    Mat rez = allocate_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] - y.data[dx];
    }
    return rez;

}

Mat multiplication(const Mat x, const Mat y){
    if (x.cols != y.rows) return empty();

    Mat rez = allocate_mat(x.rows, y.cols);
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            rez.value[row][col] = 0.0;
            for (unsigned int dx = 0; dx < x.cols; dx++){
                rez.value[row][col] += x.value[row][dx] * y.value[dx][col];
            }
        }
    }
    return rez;
}

Mat multiplication_k(const Mat x, const double k){

    Mat rez = allocate_mat(x.rows, x.cols);
    for (unsigned int dx = 0; dx < x.rows * x.cols; dx++){
        rez.data[dx] = x.data[dx] * k;
    }
    return rez;
}

double det(const Mat x){
    if (x.cols != x.rows) return 0.0;

    if (x.cols == 1){
        return x.value[0][0];
    }
    double rez = 0.0;
    int ratio = 1;
    for (unsigned int dx = 0; dx < x.cols; dx++) {
        Mat temp = minor(0, dx, x);
        rez += ratio * x.value[0][dx] * det(temp);
        ratio *= -1;
        release(temp);
    }
    return rez;
}

Mat reverse(const Mat x){
    double deter = det(x);
    if ((x.cols != x.rows) || (deter == 0.0)) return empty();

    Mat rez = allocate_mat(x.rows, x.cols);
    int ratio = 1;
    for (unsigned int row = 0; row < rez.rows; row++){
        for (unsigned int col = 0; col < rez.cols; col++){
            Mat temp = minor(row, col, x);
            rez.value[row][col] = ratio * det(temp);
            ratio *= -1;
            release(temp);
        }
    }
    Mat ans = transponation(rez);
    rez = multiplication_k(ans, 1/deter);
    release(ans);
    return rez;

}

Mat pow_m(const Mat x, const unsigned int n){
    if (x.rows != x.cols) return empty();
    if (n == 0) return one(x.rows, x.cols);

    Mat rez = copy_matrix(x);

    for (unsigned int dx = 1; dx < n; dx++){
        rez = multiplication(x, rez);
    }
    return rez;
}

Mat exponent(const Mat x, const unsigned int kol_slog){
    if (x.cols != x.rows) return empty();

    Mat rez = zero(x.rows, x.cols);
    double ratio = 1;

    for (unsigned int dx = 0; dx < kol_slog; dx++){
        Mat degree = pow_m(x, dx);
        Mat multiplier = multiplication_k(degree, ratio);
        rez = sum(rez, multiplier);

        ratio /= (dx + 1);
        release(degree);
        release(multiplier);
    }
    return rez;

}

Mat certain(const unsigned int rows, const unsigned int cols,
                      const double *arrey, const unsigned int arr_length){
    if (rows * cols - arr_length > 0) return empty();

    Mat rez = allocate_mat(rows, cols);
    for (unsigned int dx = 0; dx < rows * cols; dx++){
        rez.data[dx] = arrey[dx];
    }
    return rez;

}


void test_of_add(){
    double arr_first[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Mat first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    Mat second = certain(2,3, arr_second, sizeof(arr_second) / sizeof(double));

    Mat rez_add = sum(first, second);

    int flag = (sum(zero(2,2), first).rows == empty().rows);
    for (unsigned int dx = 0; dx < rez_add.rows * rez_add.cols; dx++){
        flag *= (fabs(rez_add.data[dx] - 7.0) < Comparison_const);
    }

    if (flag){
        printf("Test of sum was successful\n");
    } else {
        printf("Test of sum was failed\n");
    }

    release(first);
    release(second);
    release(rez_add);
}


void test_of_sub(){

    double arr_first[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Mat first = certain(2, 3, arr_first, sizeof(arr_first) / sizeof(double));

    double arr_second[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Mat second = certain(2, 3, arr_second, sizeof(arr_second) / sizeof(double));

    Mat rez_sub = subtraction(first, second);

    int flag = (subtraction(zero(2,2), one(3, 3)).rows == empty().rows);
    for (unsigned int dx = 0; dx < rez_sub.rows * rez_sub.cols; dx++){
        flag *= (fabs(rez_sub.data[dx] - 0.0) < Comparison_const);
    }

    if (flag){
        printf("Test of subtraction was successful\n");
    } else {
        printf("Test of subtraction was failed\n");
    }

    release(first);
    release(second);
    release(rez_sub);
}


void test_of_multy(){
    double arr_first[6] = {1.0, 5.0, 6.0, 3.0, 9.0, 4.0};
    Mat first = certain(2, 3, arr_first, sizeof (arr_first) / sizeof (double));

    double arr_second[3] = {1.0, 0.0, 1.0};
    Mat second = certain(3, 1, arr_second, sizeof (arr_second) / sizeof (double));

    Mat rez_mul = multiplication(first, second);

    int flag = 1;
    for (unsigned int dx = 0; dx < rez_mul.rows * rez_mul.cols; dx++){
        flag *= (fabs(rez_mul.data[dx] - 7.0) < Comparison_const);
    }

    if (flag){
        printf("Test of multiplication was successful\n");
    } else {
        printf("Test of multiplication was failed\n");
    }

    release(first);
    release(second);
    release(rez_mul);
}


void test_of_reverse(){
    unsigned int n = 3;
    Mat obj = allocate_mat(n, n);
    for (unsigned int dx = 0; dx < obj.rows * obj.cols; dx++){
        obj.data[dx] = rand() % Max_range;
    }

    Mat rez = multiplication(obj, reverse(obj));
    Mat one_3 = one(n, n);

    int flag = (rez.rows != empty().rows);
    for (unsigned int idx = 0; idx < rez.rows * rez.cols; idx++){
        flag *= (fabs(rez.data[idx] - one_3.data[idx]) < Comparison_const);
    }

    if (flag){
        printf("Test of reverseMatrix was successful\n");
    } else {
        printf("Test of reverseMatrix was failed\n");
    }

    release(obj);
    release(rez);
    release(one_3);
}

void test_of_exponent(){
    Mat base = allocate_mat(3, 3);
    for (unsigned int dx = 0; dx < base.rows * base.cols; dx++){
        base.data[dx] = (double)(rand() % Max_range) / Max_range;
    }

    Mat option_1 = exponent(base, 30);
    output(option_1);
    Mat option_2 = sum(one(3, 3), sum(base, multiplication_k(multiplication(base, base), 0.5)));

    int flag = (option_1.rows == option_2.rows);
    for (unsigned int dx = 0; dx < option_1.rows * option_1.cols; dx++){
        flag *= (fabs(option_1.data[dx] - option_2.data[dx]) < Comparison_const);
    }

    if (flag){
        printf("Test of exponent was successful\n");
    } else {
        printf("Test of exponent was failed\n");
    }

    release(base);
    release(option_1);
    release(option_2);
}

void block_tests(){
    test_of_add();
    test_of_sub();
    test_of_multy();
    test_of_reverse();
    test_of_exponent();
    printf("\n");
}

void block_output(){
    Mat A = allocate_mat(3, 3);
    Mat B = allocate_mat(3, 3);

    for (unsigned int dx = 0; dx < A.rows * A.cols; dx++){
        A.data[dx] = rand() % Max_range;
    }
    for (unsigned int dx = 0; dx < B.rows * B.cols; dx++){
        B.data[dx] = rand() % Max_range;
    }

    printf("This is emptyMatrix\n");
    output(empty());
    printf("This is zeroMatrix\n");
    output(zero(5,5));
    printf("This is oneMatrix\n");
    output(one(5, 5));

    printf("This isMatrix A\n");
    output(A);
    printf("This isMatrix B\n");
    output(B);

    printf("This is transporation ofMatrix A\n");
    output(transponation(A));

    printf("This isMatrix A + B\n");
    output(sum(A,B));
    printf("This isMatrix A - B\n");
    output(subtraction(A,B));
    printf("This isMatrix A * B\n");
    output(multiplication(A, B));
    printf("This isMatrix A * 0.33\n");
    output(multiplication_k(A, 0.33));

    printf("This is det ofMatrix A\n");
    printf("%.2lf\n\n", det(A));

    printf("This is reverse ofMatrix A\n");
    output(reverse(A));
    printf("This isMatrix A in degree 3\n");
    output(pow_m(A, 3));

    printf("This is exp ofMatrix A\n");
    output(exponent(A, 2));
}

int main() {

    block_tests();
    block_output();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();

    getchar();
    return 0;
}