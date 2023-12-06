#include "matrix.h"

/************************ Private matrix variables ************************/

const Matrix_Instance null_matrix = {0, 0, NULL};

enum Error_Type {
    Memory_Error, 
    Bad_Matrix_Error, 
    Matrix_Dimension_Error,   
    Determinant_Error,
    Bad_Arguments
};

typedef void (*error_printer)();

const char* error_messages[] = {
    "Memory error!",
    "Bad matrix error!",
    "Matrix dimension error!",
    "Determinant error!",
    "Bad arguments error!"
};

/************************ Private matrix functions ************************/

static inline void print_matrix_error(enum Error_Type error) {
    fprintf(stderr, "%s\n", error_messages[error]);
}

static inline Matrix_Instance allocate_matrix(int rows, int cols) {
    Matrix_Instance matrix = {
        .numRows = rows,
        .numCols = cols
    };

    matrix.pData = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.pData[i] = (double *)malloc(cols * sizeof(double));
    }
    if (NULL == matrix.pData) {
        print_matrix_error(Memory_Error);
        return null_matrix;
    }
    return matrix;
}

static inline Matrix_Instance create_submatrix(const Matrix_Instance matrix, int excludeRow, int excludeCol) {
    Matrix_Instance submatrix = allocate_matrix(matrix.numRows - 1, matrix.numCols - 1);

    if (NULL == submatrix.pData) {
        return null_matrix;
    }

    int sub_i = 0, sub_j = 0;
    for (int i = 0; i < matrix.numRows; i++) {
        if (i == excludeRow) {
            continue;
        }
        sub_j = 0;
        for (int j = 0; j < matrix.numCols; j++) {
            if (j == excludeCol) {
                continue;
            }
            submatrix.pData[sub_i][sub_j] = matrix.pData[i][j];
            sub_j++;
        }
        sub_i++;
    }
    return submatrix;
}

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

Matrix_Instance _internal_create_default_matrix(int rows, int cols) { // --> overloaded in create_matrix
    if (0 == rows || 0 == cols) {
        print_matrix_error(Bad_Arguments);
        return null_matrix;
    }
    Matrix_Instance matrix = allocate_matrix(rows, cols);
    return matrix;
}

Matrix_Instance _internal_create_type_matrix(int rows, int cols, enum Matrix_Type matrix_type) { // --> overloaded in create_matrix
    // printf("Creating type matrix with %d\n", matrix_type);
    if (0 == rows || 0 == cols) {
        print_matrix_error(Bad_Arguments);
        return null_matrix;
    }
    Matrix_Instance matrix = allocate_matrix(rows, cols);
    
    if (NULL == matrix.pData) {
        return null_matrix;
    }

    switch (matrix_type) {
        case (Zero_Matrix):
            memset(matrix.pData, 0., matrix.numCols * matrix.numRows * sizeof(double));
            break;
        case (Ones_Matrix):
            memset(matrix.pData, 1., matrix.numCols * matrix.numRows * sizeof(double));
            break;
        case Identity_Matrix:
            if (matrix.numCols == matrix.numRows) {
                for (int i = 0; i < matrix.numRows; i++) {
                    for (int j = 0; j < matrix.numCols; j++) {
                        matrix.pData[i][j] = (i == j) ? 1. : 0.;
                    }
                }
            } else {
                print_matrix_error(Matrix_Dimension_Error);
            }
            break;
        case (Random_Matrix):
            fill_matrix_random(matrix);
            break;
    }
    return matrix;
}

Matrix_Instance copy_matrix(const Matrix_Instance A, const Matrix_Instance B) {
    if (A.numRows != B.numRows || A.numCols != B.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        return null_matrix;
    } else if (NULL == A.pData || NULL == B.pData) {
        print_matrix_error(Memory_Error);
        return null_matrix;
    }

    for (int i = 0; i < A.numRows; i++) {
        memcpy(B.pData[i], A.pData[i], A.numCols * sizeof(double));
    }
    return B;
}

void free_matrix(Matrix_Instance matrix) {
    if (matrix.pData != NULL) {
        for (int i = 0; i < matrix.numRows; i++) {
            free(matrix.pData[i]);
        }
        free(matrix.pData);
    }
    matrix = null_matrix;
}

void fill_matrix_random(Matrix_Instance matrix) {
    srand(time(NULL));
    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            matrix.pData[i][j] = (double)rand() / 10000000; 
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

/************************ Math matrix functions ************************/

Matrix_Instance _internal_multiply_matrices(const Matrix_Instance A, const Matrix_Instance B) { // --> overloaded in multiply_matrix
    if (A.numCols != B.numRows) {
        print_matrix_error(Matrix_Dimension_Error);
        return null_matrix;
    }

    Matrix_Instance result = create_matrix(A.numRows, B.numCols);

    if (NULL == result.pData) {
        return null_matrix;
    }

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

Matrix_Instance _internal_multiply_matrix_scalar(const Matrix_Instance matrix, const double scalar) { // --> overloaded in multiply_matrix
    if (matrix.pData == NULL) {
        print_matrix_error(Bad_Arguments);
        return null_matrix;
    }
    Matrix_Instance result = allocate_matrix(matrix.numRows, matrix.numCols);

    if (NULL == result.pData) {
        return null_matrix;
    }

    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            result.pData[i][j] = matrix.pData[i][j] * scalar;
        }
    }
    return result;
}

Matrix_Instance substract_matrices(const Matrix_Instance A, const Matrix_Instance B) {
    if (A.numRows != B.numRows || A.numCols != B.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        return null_matrix;
    } else if (A.pData == NULL || B.pData == NULL) {
        print_matrix_error(Bad_Arguments);
        return null_matrix;
    }

    Matrix_Instance result = allocate_matrix(A.numRows, A.numCols);
    
    if (NULL == result.pData) {
        return null_matrix;
    }

    for (int i = 0; i < A.numRows; i++) {
        for (int j = 0; j < A.numCols; j++) {
            result.pData[i][j] = A.pData[i][j] - B.pData[i][j];
        }
    }
    return result;
}

Matrix_Instance sum_matrices(const Matrix_Instance A, const Matrix_Instance B) {
    if (A.numRows != B.numRows || A.numCols != B.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        return null_matrix;
    }

    Matrix_Instance result = create_matrix(A.numRows, A.numCols);
    
    if (NULL == result.pData) {
        return null_matrix;
    }

    for (size_t i = 0; i < A.numRows; ++i) {
        for (size_t j = 0; j < A.numCols; ++j) {
            result.pData[i][j] = A.pData[i][j] + B.pData[i][j];
        }
    }
    return result;
}

Matrix_Instance transpose_matrix(const Matrix_Instance matrix) {
    if (NULL == matrix.pData) {
        print_matrix_error(Bad_Arguments);
        return matrix;
    }
    Matrix_Instance result = allocate_matrix(matrix.numCols, matrix.numRows);
    if (NULL == result.pData) {
        return null_matrix;
    }

    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            result.pData[j][i] = matrix.pData[i][j];
        }
    }
    return result;
}

Matrix_Instance exponent_matrix(const Matrix_Instance matrix, const unsigned int n) {
    if (NULL == matrix.pData) {
        print_matrix_error(Bad_Matrix_Error);
        return null_matrix;
    }

    if (matrix.numRows != matrix.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        return null_matrix;
    }

    Matrix_Instance exponent = create_matrix(matrix.numRows, matrix.numCols, Identity_Matrix);
    Matrix_Instance summand = create_matrix(matrix.numRows, matrix.numCols, Identity_Matrix);
    Matrix_Instance temp = create_matrix(matrix.numRows, matrix.numCols);

    if (exponent.pData == NULL || summand.pData == NULL || temp.pData == NULL) {
        return null_matrix;
    }

    if (n == 0) return exponent;

    if (n == 1) {
        temp = sum_matrices(exponent, matrix);
        if (temp.pData == NULL) {
            free_matrix(exponent);
            free_matrix(summand);
            free_matrix(temp);
            return null_matrix;
        }
        copy_matrix(temp, exponent);
        free_matrix(summand);
        free_matrix(temp);
        return exponent;
    }

    for (int i = 1; i <= n; i++) {
        temp = multiply_matrix(summand, matrix);
        if (temp.pData == NULL) {
            free_matrix(exponent);
            free_matrix(summand);
            free_matrix(temp);
            return null_matrix;
        }
        copy_matrix(temp, summand);
        free_matrix(temp);

        temp = multiply_matrix(summand, 1. / i);
        if (temp.pData == NULL) {
            free_matrix(exponent);
            free_matrix(summand);
            free_matrix(temp);
            return null_matrix;
        }
        copy_matrix(temp, summand);
        free_matrix(temp);

        temp = sum_matrices(exponent, summand);
        if (temp.pData == NULL) {
            free_matrix(exponent);
            free_matrix(summand);
            free_matrix(temp);
            return null_matrix;
        }
        copy_matrix(temp, exponent);
        free_matrix(temp);
    }

    free_matrix(summand);

    return exponent;
}

double sum_elements_matrix(const Matrix_Instance matrix) {
    if (NULL == matrix.pData) {
        print_matrix_error(Bad_Arguments);
        return 0;
    }

    double sum = 0.0;

    for (int i = 0; i < matrix.numRows; i++) {
        for (int j = 0; j < matrix.numCols; j++) {
            sum += matrix.pData[i][j];
        }
    }
    return sum;
}

double determinant_matrix(const Matrix_Instance matrix) {
    if (NULL == matrix.pData) {
        print_matrix_error(Bad_Arguments);
        return 0;
    } else if (matrix.numRows != matrix.numCols) {
        print_matrix_error(Matrix_Dimension_Error);
        return 0.0; 
    }

    if (2 == matrix.numRows && 2 == matrix.numCols) {
        return matrix.pData[0][0] * matrix.pData[1][1] - matrix.pData[0][1] * matrix.pData[1][0];
    }

    double det = 0.0;
    Matrix_Instance submatrix = {0, 0, NULL};

    for (int col = 0; col < matrix.numCols; col++) {
        submatrix = create_submatrix(matrix, 0, col);
        if (NULL == submatrix.pData) {
            return 0;
        }
        det += pow(-1, col) * matrix.pData[0][col] * determinant_matrix(submatrix);
        free_matrix(submatrix);
    }
    return det;
}