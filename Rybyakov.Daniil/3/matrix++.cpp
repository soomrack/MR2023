#include <iostream>
#include <cstdlib>
#include <cstring>

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NOTSQUARE("Make matrix square\n");
Matrix_Exception SIZEERROR("Change a size\n");
Matrix_Exception DIVISIONERROR("Can't divide by zero\n");


class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
    double* value;

public:
    Matrix();
    Matrix(unsigned int col, unsigned int row);
    Matrix(unsigned int col);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();

    void matrix_print();
    void matrix_fill(int max_value);

    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator*(double number) const;
    Matrix operator=(Matrix& matrix);
    Matrix operator=(Matrix&& matrix);
    Matrix operator^(const int number) const;
    Matrix operator/(const double number) const;
    static Matrix  exp(const Matrix& A, const unsigned int accuracy);
    Matrix matrix_minor(Matrix& mat1, unsigned int row, unsigned int col);
    Matrix matrix_transp();
    double matrix_det(Matrix matrix);


};

Matrix::~Matrix() {
    if (value != nullptr) delete[] value;
}


Matrix::Matrix() {
    cols = 0;
    rows = 0;
    value = nullptr;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    value = new double[cols * rows];

    for (unsigned int idx = 0; idx < cols * rows; ++idx) {
        value[idx] = 0.0;
    }
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    value = new double[rows * cols];
    memcpy(value, matrix.value, rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    value = matrix.value;
    matrix.value = nullptr;
}


void Matrix::matrix_print() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << value[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::matrix_fill(int max_value = 10) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        value[index] = rand() % max_value;
    }
}


Matrix::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    value = new double[cols * rows];

    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            value[row * cols + col] = (row == col) ? 1.0 : 0.0;

        }
    }
}


Matrix Matrix::operator+ (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);

    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.value[idx] += value[idx];
    }
    return result;
}


Matrix Matrix::operator- (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);

    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.value[idx] -= value[idx];
    }
    return result;
}


Matrix Matrix::operator* (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);

    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.value[row * result.rows + col] = 0.00;
            for (unsigned int k = 0; k < result.cols; k++) {
                result.value[row * result.cols + col] += value[row * cols + k] * matrix.value[k * result.cols + col];
            }
        }
    }
    return result;
}


Matrix Matrix::operator* (const double coefficient) const {
    Matrix result(cols, rows);

    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        result.value[idx] = value[idx] * coefficient;
    }
    return result;
}



Matrix Matrix::operator= (Matrix& matrix) {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]value;
    value = new double[cols * rows];
    memcpy(value, matrix.value, rows * cols * sizeof(double));
    return *this;
}


Matrix Matrix::operator= (Matrix&& matrix) {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]value;
    value = matrix.value;
    matrix.value = nullptr;
    return *this;
}


Matrix Matrix::operator^(int number) const {
    if (cols != rows) throw NOTSQUARE;
    Matrix result(*this);

    if (number == 0) {
        Matrix matrix(cols);
        return matrix;
    }

    if (number == 1) {
        return result;
    }

    const Matrix& start(result);

    for (unsigned int idx = 0; idx < number; idx++) {
        result = result * start;
    }
    return result;
}


Matrix Matrix::operator/(const double number) const {
    if (number == 0) throw DIVISIONERROR;
    Matrix result(cols, rows);

    for (unsigned int idx = 0; idx < rows * cols; ++idx) {
        result.value[idx] = value[idx] / number;
    }
    return result;
}


Matrix Matrix::exp(const Matrix& A, const unsigned int accuracy = 30) {
    if (A.rows != A.cols) throw NOTSQUARE;
    Matrix result(A.cols);
    Matrix temp(A.cols);
    double factorial = 1.0;

    for (int step = 1; step < accuracy; step++) {
        factorial *= step;
        temp = temp * A;
        result = result + temp / factorial;
    }
    return result;
}



Matrix Matrix::matrix_minor(Matrix& A, unsigned int row, unsigned int col) {
    int new_row = A.rows - 1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix result = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if ((idx % cols == col) or (idx / cols == row)) continue;
        result.value[k++] = A.value[idx];
    }

    return result;
}

Matrix Matrix::matrix_transp() {
    Matrix result = { cols, rows };

    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.value[row * result.cols + col] = value[col * result.cols + row];
        }
    }
    return result;
}




int main() {
    Matrix mat1(3, 3);
    mat1.matrix_fill();
    mat1.matrix_print();
    Matrix mat2(3, 3);
    mat2.matrix_fill();
    mat2.matrix_print();
    Matrix sum = mat1 + mat2;
    sum.matrix_print();
    Matrix sub = mat1 - mat2;
    sub.matrix_print();
    Matrix mult = mat1 * mat2;
    mult.matrix_print();
    Matrix mult_number = mat1 * 2;
    mult_number.matrix_print();
    Matrix pow = mat1 ^ 2;
    pow.matrix_print();
    Matrix exp = Matrix::exp(mat1);
    exp.matrix_print();
    return 0;
}

     