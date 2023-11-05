#include "libmatrix.h"

const struct Matrix MATRIX_NULL = {0, 0, NULL};
const matrix_item RANDOM_LOW = -10., RANDOM_HIGH = 10.;


void error_print(enum ErrorType error) {
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
        case DET_ERROR:
            printf("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrix\n");
            break;
        case EXP_LEVEl_ERROR:
            printf("Exponential level cannot be smaller than 1\n");
            break;
        default:
            printf("Undefined error\n");
            break;
    }
}

struct Matrix allocate_memory(const size_t rows, const size_t cols) {
    if (rows >= SIZE_MAX / sizeof(matrix_item) / cols) {
        error_print(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix M = {cols, rows, NULL};

    if (cols != 0 || rows != 0) {
        M.data = (matrix_item *) malloc(M.cols * M.rows * sizeof(matrix_item));

        if (M.data == NULL) {
            error_print(MEMORY_ERROR);
            return MATRIX_NULL;
        }
    }

    return M;
}


void fill_matrix(struct Matrix *M, enum MatrixType matrix_type) {
    switch (matrix_type) {
        case (ZEROS):
            memset(M->data, 0, M->cols * M->rows * sizeof(matrix_item));
            break;

        case (ONES):
            for (size_t idx = 0; idx < M->cols * M->rows; idx++)
                M->data[idx] = 1.;
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
                        if (row == col)
                            M->data[row * M->cols + col] = 1.;
                    }
            else error_print(COLS_ROWS_ERROR);
            break;
    }
}


void matrix_print(struct Matrix *M) {
    if (M->data != NULL) {
        printf("\n");
        for (size_t row = 1; row <= M->cols * M->rows; ++row) {
            printf("%.2f \t", M->data[row - 1]);
            if (row % M->cols == 0 && row >= M->cols)
                printf("\n");
        }
        printf("\n");
    } else {
        error_print(BAD_MATRIX_ERROR);
    }
}


struct Matrix matrix_create(size_t rows, size_t cols, enum MatrixType mat_type) {
    struct Matrix M = allocate_memory(rows, cols);
    if (M.data != NULL) fill_matrix(&M, mat_type);
    return M;
}


void matrix_remove(struct Matrix *M) {
    free(M->data);
    *M = MATRIX_NULL;
}


struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) {
        error_print(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = allocate_memory(A.cols, A.rows);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = A.data[idx] + B.data[idx];

    return C;
}


struct Matrix matrix_subtract(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.cols || A.rows != B.rows) {
        error_print(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = allocate_memory(A.cols, A.rows);

    for (size_t idx = 0; idx < A.cols * A.rows; ++idx)
        C.data[idx] = A.data[idx] - B.data[idx];

    return C;
}


struct Matrix matrix_multiply(const struct Matrix A, const double scalar) {
    struct Matrix B = allocate_memory(A.cols, A.rows);

    for (size_t idx = 0; idx < A.rows * A.cols; idx++)
        B.data[idx] = (matrix_item) scalar * A.data[idx];

    return B;
}


struct Matrix matrix_product(const struct Matrix A, const struct Matrix B) {
    if (A.cols != B.rows) {
        error_print(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    struct Matrix C = allocate_memory(A.cols, A.rows);

    for (size_t row_A = 0; row_A < A.rows; row_A++)
        for (size_t col_B = 0; col_B < B.cols; col_B++)
            for (size_t idx = 0; idx < A.cols; idx++)
                C.data[row_A * A.cols + col_B] += A.data[row_A * A.cols + idx] * B.data[idx * B.cols + col_B];

    return C;
}


struct Matrix matrix_transpose(const struct Matrix A) {
    struct Matrix B = allocate_memory(A.cols, A.rows);

    for (size_t row = 0; row < A.rows; row++)
        for (size_t col = 0; col < A.cols; col++)
            B.data[row * A.rows + col] = A.data[col * A.cols + row];

    return B;
}


double matrix_det(const struct Matrix A) {
    if (A.cols != A.rows) {
        error_print(COLS_ROWS_ERROR);
        return 0.;
    }

    double det;

    if (A.cols == 1)
        det = (double) A.data[0];
    else if (A.cols == 2)
        det = (double) (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
    else if (A.cols == 3)
        det = (double) (A.data[0] * A.data[4] * A.data[8]) + \
                       (A.data[1] * A.data[5] * A.data[6]) + \
                       (A.data[2] * A.data[3] * A.data[7]) - \
                       (A.data[2] * A.data[4] * A.data[6]) - \
                       (A.data[0] * A.data[5] * A.data[7]) - \
                       (A.data[1] * A.data[3] * A.data[8]);
    else {
        error_print(DET_ERROR);
        det = 0.;
    }

    return det;
}

struct Matrix matrix_exp(const struct Matrix A, const int n) {
    if (A.cols != A.rows) {
        error_print(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    if (n < 1) {
        error_print(EXP_LEVEl_ERROR);
        return MATRIX_NULL;
    }

    if (n == 1)
        return A;

    return matrix_product(A, matrix_exp(A, n - 1));
}