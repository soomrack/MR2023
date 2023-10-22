#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#define SUCCESS 0
#define FAIL 1


// #define RANDOM (char)'r'
// #define UNIT (char)'u'
// #define BLANK (char)'b'


/*
next to create:
1. Error message enum and error handler function


*/

enum InfillPattern {
    RANDOM,
    UNIT,
    BLANK
};


enum Errors {
    MALLOC_ERROR,
    DETERMINANT_ERROR,
    OPERATION_ERROR
};



/*  p[1]: - - - 
    p[2]: - - -   
    p[3]: - - -
    .
    .
    p[n]: - - -

so p[i] is a pointer, and data is a pointer to first column pointer

*/


typedef struct {   
    uint16_t rows; // stroki
    uint16_t cols;  // stolbcbl
    double ** data; 
    // double determinant;
} Matrix; //  struct Matrix


void initMatrix(Matrix * this);
void fillMatrix(Matrix * this, enum InfillPattern pattern, const bool printOption);
void fillWithData(Matrix * this, const double* filling_array, const bool printOption);
void deleteData(Matrix *this);
void deleteMatrix(Matrix * this);
void __printSingleVal(const double val, const uint8_t counter, const  int16_t cols);
void printMatrix(const Matrix * this);
void errorHandler(enum Errors error, const char * func_name);
Matrix  matrixSum(Matrix * matrix_1, Matrix * matrix_2);
Matrix  matrixSub(Matrix * matrix_1, Matrix * matrix_2);
void matrixTransposition(Matrix  *this);







