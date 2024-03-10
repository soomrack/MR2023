#include "libmatrix.h"

const struct Matrix MATRIX_NULL = {0, 0, NULL};
const matrix_item RANDOM_LOW = -10., RANDOM_HIGH = 10.;


void matrix_error(enum ErrorType error) {
    switch (error) {
        case MEMORY_ERROR:
            printf("Memory allocation error\n");
            break;
        case BAD_MATRIX_ERROR:
            printf("Incalculable or empty matrix error\n");
            break;
        case COLS_ROWS_ERROR:
            printf("Wrong number of columns or rows\n");
            break;
        case COPY_ERROR:
            printf("Memory copy error\n");
            break;
        case DET_ERROR:
            printf("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrix\n");
            break;
        default:
            printf("Undefined error\n");
            break;
    }
}


struct Matrix matrix_allocate(const size_t rows, const size_t cols) {
    if (rows == 0 && cols == 0) return MATRIX_NULL;

    if (rows >= SIZE_MAX / sizeof(matrix_item) / cols) {
        matrix_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix M = {cols, rows, NULL};

    M.data = (matrix_item *) malloc(M.cols * M.rows * sizeof(matrix_item));

    if (M.data == NULL) {
        matrix_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    return M;
}


void matrix_fill(struct Matrix *M, enum MatrixType matrix_type) {
    switch (matrix_type) {
        case (ZEROS):
            memset(M->data, 0, M->cols * M->rows * sizeof(matrix_item));
            break;

        case (ONES):
            for (size_t idx = 0; idx < M->cols * M->rows; idx++) M->data[idx] = 1.;
            break;

        case (RANDOM):
            for (size_t idx = 0; idx < M->cols * M->rows; idx++)
                M->data[idx] = ((matrix_item) rand() * (RANDOM_HIGH - RANDOM_LOW))
                               / (matrix_item) RAND_MAX + RANDOM_LOW;
            break;

        case (IDENTITY):
            memset(M->data, 0, M->rows * M->cols * sizeof(matrix_item));
            if (M->cols == M->rows)
                for (size_t row = 0; row < M->rows; row++)
                    for (size_t col = 0; col < M->cols; col++) {
                        if (row == col) M->data[row * M->cols + col] = 1.;
                    }
            else matrix_error(COLS_ROWS_ERROR);
            break;
    }
}


void matrix_print(const struct Matrix M) {
    if (M.data == NULL) matrix_error(BAD_MATRIX_ERROR);

    for (size_t idx = 1; idx <= M.cols * M.rows; ++idx) {
        printf("%.2f \t", M.data[idx - 1]);
        if (idx % M.cols == 0 && idx >= M.cols) printf("\n");
    }
    printf("\n");
}


struct Matrix matrix_create(const size_t rows, const size_t cols, enum MatrixType mat_type) {
    if (rows == 0 && cols == 0) return MATRIX_NULL;

    struct Matrix M = matrix_allocate(rows, cols);

    if (M.data == NULL) return MATRIX_NULL;

    if (rows == 0 || cols == 0) {
        M.rows = rows;
        M.cols = cols;
        M.data = NULL;
        return M;
    }

    matrix_fill(&M, mat_type);

    return M;
}


void matrix_free(struct Matrix *M) {
    if (M->data == NULL) matrix_error(FREE_ERROR);

    free(M->data);
    *M = MATRIX_NULL;
}


struct Matrix matrix_copy(const struct Matrix A, struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    matrix_free(&B);

    B = matrix_allocate(A.rows, A.cols);
    memcpy(B.data, A.data, B.cols * B.rows * sizeof(matrix_item));

    if (B.data == NULL) {
        matrix_error(COPY_ERROR);
        return MATRIX_NULL;
    }

    return B;
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.cols || A.rows != B.rows) {
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = matrix_allocate(A.rows, A.cols);

    if (C.data == NULL) return MATRIX_NULL;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) C.data[idx] = A.data[idx] + B.data[idx];

    return C;
}


struct Matrix matrix_subtract(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.cols || A.rows != B.rows) {
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = matrix_allocate(A.rows, A.cols);

    if (C.data == NULL) return MATRIX_NULL;

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) C.data[idx] = A.data[idx] - B.data[idx];

    return C;
}


struct Matrix matrix_multiply(const struct Matrix A, const double scalar) {
    if (A.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix B = matrix_allocate(A.rows, A.cols);

    if (B.data == NULL) return MATRIX_NULL;

    for (size_t idx = 0; idx < A.rows * A.cols; idx++) B.data[idx] = (matrix_item) scalar * A.data[idx];

    return B;
}


struct Matrix matrix_product(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.rows) {
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = matrix_create(A.rows, A.cols, ZEROS);

    if (C.data == NULL) return MATRIX_NULL;

    for (size_t row_A = 0; row_A < A.rows; row_A++)
        for (size_t col_B = 0; col_B < B.cols; col_B++)
            for (size_t idx = 0; idx < A.cols; idx++)
                C.data[row_A * A.cols + col_B] += A.data[row_A * A.cols + idx] * B.data[idx * B.cols + col_B];

    return C;
}


struct Matrix matrix_transpose(const struct Matrix A) {
    if (A.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix B = matrix_allocate(A.cols, A.rows);

    if (B.data == NULL) return MATRIX_NULL;

    for (size_t row = 0; row < A.rows; row++)
        for (size_t col = 0; col < A.cols; col++) B.data[col * A.rows + row] = A.data[row * A.cols + col];

    return B;
}


double matrix_det(const struct Matrix A) {
    if (A.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return NAN;
    }

    if (A.cols != A.rows) {
        matrix_error(COLS_ROWS_ERROR);
        return NAN;
    }

    if (A.cols == 1)
        return (double) A.data[0];
    if (A.cols == 2)
        return (double) (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
    if (A.cols == 3)
        return (double) (A.data[0] * A.data[4] * A.data[8]) + \
                       (A.data[1] * A.data[5] * A.data[6]) + \
                       (A.data[2] * A.data[3] * A.data[7]) - \
                       (A.data[2] * A.data[4] * A.data[6]) - \
                       (A.data[0] * A.data[5] * A.data[7]) - \
                       (A.data[1] * A.data[3] * A.data[8]);

    matrix_error(DET_ERROR);
    return NAN;
}


struct Matrix matrix_exp(const struct Matrix A, const unsigned int n) {
    if (A.data == NULL) {
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.rows != A.cols) {
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix exponent = matrix_create(A.rows, A.cols, IDENTITY);
    struct Matrix summand = matrix_create(A.rows, A.cols, IDENTITY);
    struct Matrix temp = matrix_allocate(A.rows, A.cols);
    if (exponent.data == NULL || summand.data == NULL || temp.data == NULL) {
        matrix_free(&exponent);
        matrix_free(&summand);
        matrix_free(&temp);
        return MATRIX_NULL;
    }

    if (n == 0) return exponent;

    if (n == 1) {
        temp = matrix_sum(exponent, A);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, exponent);
        matrix_free(&summand);
        matrix_free(&temp);
        return exponent;
    }

    for (unsigned int idx = 1; idx <= n; idx++) {
        temp = matrix_product(summand, A);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, summand);
        matrix_free(&temp);

        temp = matrix_multiply(summand, 1. / idx);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, summand);
        matrix_free(&temp);

        temp = matrix_sum(exponent, summand);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, exponent);
        matrix_free(&temp);
    }

    matrix_free(&summand);

    return exponent;
}