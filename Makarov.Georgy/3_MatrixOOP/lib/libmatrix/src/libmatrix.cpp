#include "libmatrix.h"


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
            else throw MatrixException("Wrong number of columns or rows");
            break;

        case (UNFILLED):
            break;
    }
}


Matrix::Matrix(const unsigned int n) {
    if (n < SIZE_MAX / sizeof(matrix_item) / n) {
        rows = n;
        cols = n;
        data = new matrix_item[n * n];
    } else throw MatrixException("Memory allocation error");
}


Matrix::Matrix(size_t rows_amount, size_t cols_amount, MatrixType matrix_type) {
    if (rows_amount >= SIZE_MAX / sizeof(matrix_item) / cols_amount)
        throw MatrixException("Memory allocation error");
    if (rows_amount != 0 || cols_amount != 0) {
        data = new matrix_item[rows_amount * cols_amount];
        rows = rows_amount;
        cols = cols_amount;
        fill(matrix_type);
    }
}


matrix_item Matrix::get(size_t row, size_t col) {
    if (row > rows || col > cols)
        throw MatrixException("Wrong number of columns or rows");
    else return data[col + cols * row];
}


void Matrix::set(size_t row, size_t col, matrix_item item) {
    if (row > rows || col > cols)
        throw MatrixException("Wrong number of columns or rows");
    else data[col + cols * row] = item;
}


void Matrix::print() {
    if (data == nullptr) throw MatrixException("Bad matrix error");

    std::cout.precision(2);
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            std::cout << std::fixed << data[row * cols + col] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


Matrix::Matrix(const Matrix &M) {
    if (rows < SIZE_MAX / sizeof(matrix_item) / cols) {
        rows = M.rows;
        cols = M.cols;
        data = new matrix_item[rows * cols];
        std::copy(M.data, M.data + rows * cols, data);
    } else throw MatrixException("Memory allocation error");
}


Matrix::Matrix(Matrix &&M) noexcept {
    rows = M.rows;
    cols = M.cols;
    data = M.data;
    M.rows = 0;
    M.cols = 0;
    M.data = nullptr;
}


Matrix &Matrix::operator=(const Matrix &M) {
    if (rows >= SIZE_MAX / sizeof(matrix_item) / cols)
        throw MatrixException("Memory allocation error");
    if (this != &M) {
        delete[] data;
        rows = M.rows;
        cols = M.cols;
        data = new matrix_item[rows * cols];
        std::copy(M.data, M.data + rows * cols, data);
    }
    return *this;
}


Matrix &Matrix::operator=(Matrix &&M) noexcept {
    if (this != &M) {
        delete[] data;
        rows = M.rows;
        cols = M.cols;
        data = M.data;
        M.rows = 0;
        M.cols = 0;
        M.data = nullptr;
    }
    return *this;
}


Matrix Matrix::operator+(const Matrix &M) const {
    if (data == nullptr) throw MatrixException("Bad matrix error");
    if (rows != M.rows || cols != M.cols) throw MatrixException("Wrong number of columns or rows");

    Matrix sum = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        sum.data[idx] = this->data[idx] + M.data[idx];
    return sum;
}


Matrix Matrix::operator-(const Matrix &M) const {
    if (data == nullptr) throw MatrixException("Bad matrix error");
    if (rows != M.rows || cols != M.cols) throw MatrixException("Wrong number of columns or rows");

    Matrix sub = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        sub.data[idx] = this->data[idx] - M.data[idx];
    return sub;
}


Matrix Matrix::operator*(double scalar) const {
    Matrix product = {rows, cols, UNFILLED};
    for (size_t idx = 0; idx < rows * cols; idx++)
        product.data[idx] = data[idx] * scalar;
    return product;
}


Matrix Matrix::operator*(const Matrix &M) const {
    if (data == nullptr) throw MatrixException("Bad matrix error");
    if (cols != M.rows) throw MatrixException("Wrong number of columns or rows");

    Matrix product = {rows, cols, ZEROS};
    for (size_t this_row = 0; this_row < rows; this_row++)
        for (size_t M_col = 0; M_col < M.cols; M_col++)
            for (size_t idx = 0; idx < cols; idx++)
                product.data[this_row * cols + M_col] +=
                        data[this_row * cols + idx] * M.data[idx * M.cols + M_col];
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
    if (data == nullptr) throw MatrixException("Bad matrix error");
    if (cols != rows) throw MatrixException("Wrong number of columns or rows");

    if (cols == 1)
        return (double) data[0];
    if (cols == 2)
        return (double) (data[0] * data[3] - data[1] * data[2]);
    if (cols == 3)
        return (double) (data[0] * data[4] * data[8]) + \
                   (data[1] * data[5] * data[6]) + \
                   (data[2] * data[3] * data[7]) - \
                   (data[2] * data[4] * data[6]) - \
                   (data[0] * data[5] * data[7]) - \
                   (data[1] * data[3] * data[8]);
    throw MatrixException("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrices");
}


unsigned long long Matrix::factorial(unsigned int value) {
    unsigned long long factorial = 1;
    for (unsigned int idx = 1; idx <= value; idx++)
        factorial *= idx;
    return factorial;
}


Matrix Matrix::exp(unsigned int n) const {
    if (data == nullptr) throw MatrixException("Bad matrix error");
    if (cols != rows) throw MatrixException("Wrong number of columns or rows");

    if (n >= 1) {
        Matrix exponent{rows, cols, IDENTITY};
        Matrix pow{rows, cols, IDENTITY};
        Matrix summand{rows, cols, UNFILLED};
        if (exponent.data != nullptr && pow.data != nullptr && summand.data != nullptr) {
            for (unsigned int idx = 1; idx <= n; idx++) {
                pow = pow * (*this);
                summand = pow * (1 / (double) factorial(idx));
                exponent = exponent + summand;
            }
        }
        return exponent;
    }
    throw MatrixException("Exponential level cannot be smaller than 1s");
}