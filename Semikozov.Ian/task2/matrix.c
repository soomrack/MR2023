#include "matrix.h"

enum Error_Type {
    Memory_Error, 
    Bad_Matix_Error, 
    Matrix_Dimension_Error,   
    Determinant_Error
};

typedef void (*error_printer)();

const char* error_messages[] = {
    "Memory error!",
    "Bad matrix error!",
    "Matrix dimension error!",
    "Determinant error!"
};

// double matrixSum(Matrix *matrix) {
//     double sum = 0;
//     __asm__ (
//         "xorpd %0, %0;"        
//         "begin_loop:"
//         "movupd (%1), %%xmm1;"     
//         "addpd %%xmm1, %0;"        
//         "add $16, %1;"             
//         "dec %2;"                  
//         "jnz begin_loop;"
//         : "+x"(sum)
//         : "r"(matrix->data), "r"(matrix->rows * matrix->cols)
//     );
//     return sum;
// }   

/************************ Basic matrix functions ************************/
Matrix_Instance create_default_matrix(int rows, int cols) { // --> overloaded in create_matrix
    Matrix_Instance matrix;
    matrix.numRows = rows;
    matrix.numCols = cols;
    matrix.pData = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.pData[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

Matrix_Instance create_type_matrix(int rows, int cols, enum Matrix_Type matrix_type) { // --> overloaded in create_matrix
    printf("Type matrix with %d", matrix_type);
}
Matrix_Instance matrix_copy(const Matrix_Instance A, const Matrix_Instance B);

void free_matrix(Matrix_Instance matrix) {
    for (int i = 0; i < matrix.numRows; i++) {
        free(matrix.pData[i]);
    }
    free(matrix.pData);
}

void fill_matrix_random(Matrix_Instance matrix) {
    srand(time(NULL));
    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            matrix.pData[i][j] = (double)rand() / RAND_MAX; 
        }
    }
}

void fill_matrix_values(Matrix_Instance matrix, double value) {
    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            matrix.pData[i][j] = value;
        }
    }
}

void print_matrix(Matrix_Instance matrix) {
    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            printf("%f\t", matrix.pData[i][j]);
        }
        printf("\n");
    }
}

static inline void print_matrix_error(enum Error_Type error) {
    fprintf(stderr, "%s\n", error_messages[error]);
}

/************************ Math matrix functions ************************/
static Matrix_Instance multiply_matrixes(const Matrix_Instance A, const Matrix_Instance B) { // --> overloaded in multiply_matrix
    if (A.numCols != B.numRows) {
        print_matrix_error(Matrix_Dimension_Error);
        exit(EXIT_FAILURE);
    }

    Matrix_Instance result = create_matrix(A.numRows, B.numCols);

    for (int i = 0; i < A.numRows; i++) {
        for (int j = 0; j < B.numCols; j++) {
            result.pData[i][j] = 0;
            for (int k = 0; k < A.numCols; k++) {
                result.pData[i][j] += A.pData[i][k] * B.pData[k][j];
            }
        }
    }

    return result;
}

Matrix_Instance multiply_matrix_scalar(const Matrix_Instance A, const double scalar); // --> overloaded in multiply_matrix
Matrix_Instance substract_matrix(const Matrix_Instance A, const Matrix_Instance B);

Matrix_Instance sum_matrix(const Matrix_Instance A, const Matrix_Instance B) {
    if (A.numRows != B.numRows || A.numCols != B.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        exit(EXIT_FAILURE);
    }

    Matrix_Instance result = create_matrix(A.numRows, A.numCols);

    for (size_t i = 0; i < A.numRows; ++i) {
        for (size_t j = 0; j < A.numCols; ++j) {
            result.pData[i][j] = A.pData[i][j] + B.pData[i][j];
        }
    }

    return result;
}
Matrix_Instance transpose_matrix(const Matrix_Instance A);
Matrix_Instance exponent_matrix(const Matrix_Instance A, const unsigned int n);
double sum_elements_matrix(const Matrix_Instance A);
double determinant_matrix(const Matrix_Instance A);