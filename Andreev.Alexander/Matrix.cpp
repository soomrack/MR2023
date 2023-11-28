#include <iostream>
#include <string>
#include <cstring>
#include <memory> // Для использования std::unique_ptr
#include <vector> // Для использования std::vector
#include <random> // Для использования генератора случайных чисел

typedef double MatrixItem;
enum MatrixType { ZERO, ONES, RANDOM, I };

class Matrix {
private:
    size_t rows;
    size_t cols;
    std::unique_ptr<MatrixItem[]> data; // Используем std::unique_ptr вместо сырых указателей

public:
    Matrix();
    Matrix(const size_t n);
    Matrix(const size_t row, const size_t col);
    Matrix(const Matrix& M);
    Matrix(Matrix&& M) noexcept;
    ~Matrix();

public:
    Matrix& operator= (const Matrix& M);
    Matrix& operator+= (const Matrix& M);
    Matrix& operator-= (const Matrix& M);
    Matrix& operator*= (const double k);
    Matrix& operator*= (const Matrix& M);

public:
    void print();
    void set(MatrixType mat_type);
    void transposition(const Matrix& M);
    double determinant();
    void exp(unsigned int level);
};

Matrix operator+(const Matrix& M, const Matrix& K);
Matrix operator-(const Matrix& M, const Matrix& K);
Matrix operator*(const Matrix& M, const Matrix& K);
Matrix operator*(const double k, const Matrix& M);
Matrix operator*(const Matrix& M, const double k);

class Matrix_Exception : public std::exception {
private:
    std::string message;

public:
    Matrix_Exception(std::string message) : message{ message } {}
    std::string get_message() const { return message; }
};

Matrix_Exception INCORRECT_INPUT_MATRIX("Incorrect input matrix\n");
Matrix_Exception INCORRECT_DIMENSION_OF_MATRIX("The matrix has an incorrect dimension\n");
Matrix_Exception NULL_MATRIX("Your matrix is empty\n");
Matrix_Exception OTHER_ERROR("An unfamiliar error\n");

Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::Matrix(const size_t n) : rows(n), cols(n), data(new MatrixItem[n * n]) {}

Matrix::Matrix(const size_t row, const size_t col) : rows(row), cols(col), data(new MatrixItem[row * col]) {}

Matrix::Matrix(const Matrix& M) : rows(M.rows), cols(M.cols), data(new MatrixItem[M.rows * M.cols]) {
    std::copy(M.data.get(), M.data.get() + rows * cols, data.get());
}

Matrix::Matrix(Matrix&& M) noexcept : rows(M.rows), cols(M.cols), data(std::move(M.data)) {
    M.rows = 0;
    M.cols = 0;
}

Matrix::~Matrix() = default;

void Matrix::print() {
    if (!data) throw NULL_MATRIX;

    std::cout << "\n";
    for (size_t r = 0; r < rows; r++) {
        std::cout << "[";
        for (size_t c = 0; c < cols; c++) {
            std::cout << data[r * cols + c];
            if (c != cols - 1)
                std::cout << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}

void Matrix::set(MatrixType mat_type) {
    switch (mat_type) {
    case (ZERO):
        std::fill(data.get(), data.get() + cols * rows, 0.0); // Используем std::fill вместо memset
        break;

    case (ONES):
        std::fill(data.get(), data.get() + cols * rows, 1.0);
        break;

    case (RANDOM): {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 10.0);

        for (size_t idx = 0; idx < cols * rows; idx++)
            data[idx] = dis(gen);
        break;
    }

    case (I):
        set(ZERO);
        for (size_t row_col = 0; row_col < rows; row_col++)
            data[row_col * cols + row_col] = 1;
        break;
    }
}

void Matrix::transposition(const Matrix& M) {
    if (!data) throw NULL_MATRIX;

    for (size_t row = 0; row < M.rows; row++)
        for (size_t col = 0; col < M.cols; col++)
            data[row * M.rows + col] = M.data[col * M.cols + row];
}

double Matrix::determinant() {
    if (cols == 2) {
        return data[0] * data[3] - data[1] * data[2];
    }

    if (cols == 3) {
        return (data[0] * data[4] * data[8]) +
            (data[1] * data[5] * data[6]) +
            (data[2] * data[3] * data[7]) -
            (data[2] * data[4] * data[6]) -
            (data[0] * data[5] * data[7]) -
            (data[1] * data[3] * data[8]);
    }

    throw INCORRECT_INPUT_MATRIX;
}

void Matrix::exp(unsigned int level) {
    if (!data) throw NULL_MATRIX;

    Matrix R(rows, cols);
    R.set(I);

    double n = 1.0;
    Matrix temp = R;
    for (unsigned int idx = 1; idx < level; idx++) {
        temp *= *this;
        n /= (idx);
        R += (temp * n);
    }
    *this = R;
}

Matrix& Matrix::operator= (const Matrix& M) {
    if (this == &M) return *this;
    rows = M.rows;
    cols = M.cols;
    data = std::make_unique<MatrixItem[]>(rows * cols); // Используем std::make_unique вместо new
    std::copy(M.data.get(), M.data.get() + rows * cols, data.get());
    return *this;
}

Matrix& Matrix::operator+= (const Matrix& M) {
    if ((rows != M.rows) or (cols != M.cols))
        throw INCORRECT_DIMENSION_OF_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += M.data[idx];
    }
    return *this;
}

Matrix& Matrix::operator-= (const Matrix& M) {
    if ((rows != M.rows) or (cols != M.cols))
        throw INCORRECT_DIMENSION_OF_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= M.data[idx];
    }
    return *this;
}

Matrix& Matrix::operator*= (const double k) {
    if (!data) throw NULL_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
    return *this;
}

Matrix& Matrix::operator*= (const Matrix& M) {
    if (cols != M.rows)
        throw INCORRECT_DIMENSION_OF_MATRIX;

    Matrix R(rows, M.cols);
    R.set(ZERO);
    for (size_t row = 0; row < R.rows; row++)
        for (size_t col = 0; col < R.cols; col++)
            for (size_t idx = 0; idx < M.rows; idx++)
                R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col];

    cols = R.cols;
    rows = R.rows;
    data = std::move(R.data); // Используем std::move для эффективного перемещения данных
    return *this;
}

Matrix operator+(const Matrix& M, const Matrix& K) {
    Matrix rez = M;
    rez += K;
    return rez;
}

Matrix operator-(const Matrix& M, const Matrix& K) {
    Matrix rez = M;
    rez -= K;
    return rez;
}

Matrix operator*(const Matrix& M, const Matrix& K) {
    Matrix rez = M;
    rez *= K;
    return rez;
}

Matrix operator*(const double k, const Matrix& M) {
    Matrix rez = M;
    rez *= k;
    return rez;
}

Matrix operator*(const Matrix& M, const double k) {
    return k * M;
}

int main(void) {
    try {
        unsigned int choise, run = 1;
        Matrix A(3), B(3, 3), C(4);

        while (run) {
            std::cout << "\n"
                "0 - exit\n"
                "1 - set\n"
                "2 - print A, B, C\n"
                "3 - C = A\n"
                "4 - C += A\n"
                "5 - C -= A\n"
                "6 - C *= 2.0\n"
                "7 - C *= B\n"
                "8 - C = A + B\n"
                "9 - C = A - B\n"
                "10 - C = A * 2\n"
                "11 - C = A * B\n"
                "12 - A.print()\n"
                "13 - B.print()\n"
                "14 - C.transposition(A)\n"
                "15 - C.determinant()\n"
                "16 - C.exp(20)\n"
                << std::endl;

            std::cout << "choise: " << std::endl;
            std::cin >> choise;

            switch (choise) {
            case 0:
                run = 0;
                break;
            case 1:
                A.set(RANDOM);
                B.set(RANDOM);
                C.set(I);
                break;
            case 2:
                A.print();
                B.print();
                C.print();
                break;
            case 3:
                C = A;
                C.print();
                break;
            case 4:
                C += A;
                C.print();
                break;
            case 5:
                C -= A;
                C.print();
                break;
            case 6:
                C *= 2.0;
                C.print();
                break;
            case 7:
                C *= B;
                C.print();
                break;
            case 8:
                C = A + B;
                C.print();
                break;
            case 9:
                C = A - B;
                C.print();
                break;
            case 10:
                C = A * 2;
                C.print();
                break;
            case 11:
                C = A * B;
                C.print();
                break;
            case 12:
                A.print();
                break;
            case 13:
                B.print();
                break;
            case 14:
                C.transposition(A);
                C.print();
                break;
            case 15:
                std::cout << C.determinant() << std::endl;
                break;
            case 16:
                C.exp(20);
                C.print();
                break;
            case 17:
                break;
            default:
                printf("wrong choice\n");
                break;
            }
        }
        return 0;
    }
    catch (const Matrix_Exception& exception) {
        std::cout << exception.get_message() << std::endl;
    }
}
