#include "libmatrix.h"

void Matrix::error(enum ErrorType error_type) {
    switch (error_type) {
        case MEMORY_ERROR:
            std::cout << "Memory allocation error" << std::endl;
            break;
        case BAD_MATRIX_ERROR:
            std::cout << "Incalculable or empty matrix error" << std::endl;
            break;
        case COLS_ROWS_ERROR:
            std::cout << "Wrong number of columns or rows" << std::endl;
            break;
        case DET_ERROR:
            std::cout << "Determinant can be only calculated for 1x1, 2x2 or 3x3 matrix" << std::endl;
            break;
        case EXP_LEVEl_ERROR:
            std::cout << "Exponential level cannot be smaller than 1" << std::endl;
            break;
        default:
            std::cout << "Undefined error" << std::endl;
            break;
    }
}


void Matrix::fill(enum MatrixType matrix_type) {
    switch (matrix_type) {
        case (ZEROS):
            memset(data, 0, cols * rows * sizeof(matrix_item));
            break;

        case (ONES):
            for (size_t idx = 0; idx < cols * rows; idx++)
                data[idx] = 1.;
            break;

        case (RANDOM):
            for (size_t idx = 0; idx < cols * rows; idx++)
                data[idx] = uniform(random_engine);
            break;

        case (IDENTITY):
            memset(data, 0, cols * rows * sizeof(matrix_item));
            if (cols == rows)
                for (size_t row = 0; row < rows; row++)
                    for (size_t col = 0; col < cols; col++) {
                        if (row == col)
                            data[row * cols + col] = 1.;
                    }
            else error(COLS_ROWS_ERROR);
            break;

        case (UNFILLED):
            break;
    }
}


Matrix::Matrix(size_t rows_amount, size_t cols_amount, MatrixType matrix_type) {
    if (rows_amount != 0 || cols_amount != 0) {
        data = new matrix_item[rows_amount * cols_amount];
        if (data == nullptr)
            error(MEMORY_ERROR);
        else {
            rows = rows_amount;
            cols = cols_amount;
            fill(matrix_type);
        }
    }
}


matrix_item Matrix::get(size_t row, size_t col) {
    if (row > rows || col > cols) {
        error(COLS_ROWS_ERROR);
        return 0.;
    } else return data[col + cols * row];
}


void Matrix::set(size_t row, size_t col, matrix_item item) {
    if (row > rows || col > cols) error(COLS_ROWS_ERROR);
    else data[col + cols * row] = item;
}


void Matrix::print() {
    std::cout.precision(2);
    if (data != nullptr) {
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                std::cout << std::fixed << data[row * cols + col] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    } else {
        error(BAD_MATRIX_ERROR);
    }
}


Matrix::Matrix(const Matrix &M) {
    rows = M.rows;
    cols = M.cols;
    data = new matrix_item[rows * cols];
    std::copy(M.data, M.data + rows * cols, data);
}


Matrix &Matrix::operator=(const Matrix &M) {
    if (this != &M) {
        delete[] data;
        rows = M.rows;
        cols = M.cols;
        data = new matrix_item[rows * cols];
        std::copy(M.data, M.data + rows * cols, data);
    }
    return *this;
}


Matrix Matrix::operator+(const Matrix &M) const {
    if (rows != M.rows || cols != M.cols) {
        error(COLS_ROWS_ERROR);
        return *this;
    }

    Matrix sum = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        sum.data[idx] = data[idx] + M.data[idx];
    return sum;
}


Matrix Matrix::operator-(const Matrix &M) const {
    if (rows != M.rows || cols != M.cols) {
        error(COLS_ROWS_ERROR);
        return *this;
    }

    Matrix sub = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        sub.data[idx] = data[idx] - M.data[idx];
    return sub;
}


Matrix Matrix::operator*(double scalar) const {
    Matrix product = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        product.data[idx] = data[idx] * scalar;
    return product;
}


Matrix Matrix::operator*(const Matrix &M) const {
    if (cols != M.rows)
        error(COLS_ROWS_ERROR);

    Matrix product = {rows, cols, UNFILLED};
    for (size_t this_row = 0; this_row < rows; this_row++)
        for (size_t M_col = 0; M_col < M.cols; M_col++)
            for (size_t idx = 0; idx < cols; idx++)
                product.data[this_row * cols + M_col] += data[this_row * cols + idx] * M.data[idx * M.cols + M_col];
    return product;
}


Matrix Matrix::T() {
    Matrix transposed = {cols, rows, UNFILLED};
    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            transposed.data[row * rows + col] = data[col * cols + row];
    return transposed;
}


double Matrix::det() {
    if (cols != rows) {
        error(COLS_ROWS_ERROR);
        return 0.;
    }

    double det = 0.;
    if (cols == 1)
        det = (double) data[0];
    else if (cols == 2)
        det = (double) (data[0] * data[3] - data[1] * data[2]);
    else if (cols == 3)
        det = (double) (data[0] * data[4] * data[8]) + \
                       (data[1] * data[5] * data[6]) + \
                       (data[2] * data[3] * data[7]) - \
                       (data[2] * data[4] * data[6]) - \
                       (data[0] * data[5] * data[7]) - \
                       (data[1] * data[3] * data[8]);
    else error(DET_ERROR);
    return det;
}


Matrix Matrix::exp(int n) {
    if (cols != rows) error(COLS_ROWS_ERROR);
    if (n < 1) error(EXP_LEVEl_ERROR);
    if (n == 1) return *this;

    Matrix exponent(rows, cols, IDENTITY);
    Matrix base = *this;
    while (n > 0) {
        if (n % 2 == 1) {
            exponent = exponent * base;
            base = base * base;
            n = (n - 1) / 2;
        } else {
            base = base * base;
            n /= 2;
        }
    }

    return exponent;
}