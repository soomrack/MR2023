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
    BLANK,
    RAISING
};


enum Errors {
    MALLOC_ERROR,
    DETERMINANT_ERROR,
    MATH_DOMAIN_ERROR
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

extern double *** recursively_alloated_memory;

void init_data(Matrix * this);
Matrix init_matrix(uint16_t rows, uint16_t cols);
void fill_matrix(Matrix * this, enum InfillPattern pattern, const bool print_option);
void fill_with_data(Matrix * this, double* filling_array, const bool print_option, const bool dynamical_array);
void delete_data(Matrix *this);
void delete_matrix(Matrix * this);
void __print_single_val(const double val, const uint8_t counter, const  int16_t cols);
void print_matrix(const Matrix * this);
void error_handler(enum Errors error, const char * func_name);
Matrix  matrix_sum(const Matrix * matrix_1, const Matrix * matrix_2);  //  done
Matrix  matrix_sub(const Matrix * matrix_1, const Matrix * matrix_2);  //  done
void matrix_transposition(Matrix  *this);  // done
double matrix_determinant(const Matrix * this);  //  done 
Matrix __get_submatrix(const Matrix * this, uint16_t row_to_delete, uint16_t col_to_delete);  //  done
Matrix matrix_multiplication(const Matrix * matrix_1, const Matrix matrix_2);
static inline uint32_t matrix_size(const Matrix * this) {
    return this->cols * this->rows;
}







