#include "matrices.h"


const struct Matrix NULL_MATRIX = {0, 0, NULL};


void print_matrix(struct Matrix *M) {
    if (M->data != NULL) {
        printf("\n");
        for (size_t row = 1; row <= M->cols * M->rows; ++row) {
            printf("%.2f \t", M->data[row - 1]);
            if (row % M->cols == 0 && row >= M->cols)
                printf("\n");
        }
        printf("\n");
    } else {
        print_error(BAD_MATRIX_ERROR);
    }
}


void print_error(enum ErrorType error) {
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
    }
}


struct Matrix allocate_memory(const size_t rows, const size_t cols) {
    if (cols == 0 || rows == 0) {
        print_error(BAD_MATRIX_ERROR);
        return NULL_MATRIX;
    }

    if (rows >= SIZE_MAX / sizeof(double) / cols) {
        print_error(MEMORY_ERROR);
        return NULL_MATRIX;
    }

    struct Matrix M = {.cols = cols, .rows = rows, .data = NULL};
    M.data = (double *) malloc(M.cols * M.rows * sizeof(double));

    return M;
}


void fill_matrix(struct Matrix *M, enum MatrixType matrix_type) {
    switch (matrix_type) {
        case (ZEROS):
            for (size_t i = 0; i < M->cols * M->rows; i++)
                M->data[i] = 0.;
            break;

        case (ONES):
            for (size_t i = 0; i < M->cols * M->rows; i++)
                M->data[i] = 1.;
            break;

        case (RANDOM):
            for (size_t i = 0; i < M->cols * M->rows; i++)
                M->data[i] = (double) (rand() % 100);
            break;

        case (IDENTITY):
            if (M->cols == M->rows)
                for (size_t row = 0; row < M->rows; row++)
                    for (size_t col = 0; col < M->cols; col++) {
                        if (row == col)
                            M->data[row * M->cols + col] = 1.;
                        else
                            M->data[row * M->cols + col] = 0.;
                    }
            else print_error(COLS_ROWS_ERROR);
            break;
    }
}


struct Matrix create_matrix(const size_t rows, const size_t cols, enum MatrixType matrix_type) {
    struct Matrix M = allocate_memory(rows, cols);
    fill_matrix(&M, matrix_type);
    return M;
}


void delete_matrix(struct Matrix *matrix) {
    free(matrix->data);
    *matrix = NULL_MATRIX;
}


struct Matrix matrices_sum(const struct Matrix *A, const struct Matrix *B) {
    if (A->cols != B->cols || A->rows != B->rows) {
        print_error(COLS_ROWS_ERROR);
        return NULL_MATRIX;
    }

    struct Matrix C = create_matrix(A->rows, A->cols, ZEROS);

    for (size_t i = 0; i < A->cols * A->rows; ++i)
        C.data[i] = A->data[i] + B->data[i];

    return C;
}


struct Matrix matrices_subtraction(const struct Matrix *A, const struct Matrix *B) {
    if (A->cols != B->cols || A->rows != B->rows) {
        print_error(COLS_ROWS_ERROR);
        return NULL_MATRIX;
    }

    struct Matrix C = create_matrix(A->rows, A->cols, ZEROS);

    for (size_t i = 0; i < A->cols * A->rows; ++i)
        C.data[i] = A->data[i] - B->data[i];

    return C;
}


struct Matrix matrix_scalar_multiplication(const struct Matrix *A, double scalar) {
    struct Matrix B = create_matrix(A->rows, A->cols, ZEROS);

    for (size_t i = 0; i < A->rows * A->cols; i++)
        B.data[i] = scalar * A->data[i];

    return B;
}


struct Matrix matrices_multiplication(const struct Matrix *A, const struct Matrix *B) {
    if (A->cols != B->rows) {
        print_error(COLS_ROWS_ERROR);
        return NULL_MATRIX;
    }

    struct Matrix C = create_matrix(A->rows, B->cols, ZEROS);

    for (size_t row = 0; row < A->rows; row++)
        for (size_t col = 0; col < B->cols; col++)
            for (size_t i = 0; i < A->cols; i++)
                C.data[row * A->cols + col] += A->data[row * A->cols + i] * B->data[i * B->cols + col];

    return C;
}


struct Matrix matrix_transposition(const struct Matrix *A) {
    struct Matrix B = create_matrix(A->cols, A->rows, ZEROS);

    for (size_t row = 0; row < A->rows; row++)
        for (size_t col = 0; col < A->cols; col++)
            B.data[row * A->rows + col] = A->data[col * A->cols + row];
    return B;
}