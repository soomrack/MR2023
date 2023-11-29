#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <random>

typedef double MatrixItem;
enum MatrixType { ZERO, ONES, RANDOM, I };

class Matrix_Exception : public std::exception {
private:
    std::string message;

public:
    Matrix_Exception(std::string message) : message{ message } {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Matrix {
private:
    size_t rows;
    size_t cols;
    MatrixItem* data;

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

    Matrix operator+(const Matrix& K) const;
    Matrix operator-(const Matrix& K) const;
    Matrix operator*(const Matrix& K) const;
    Matrix operator*(const double k) const;

public:
    void print();
    void set(MatrixType mat_type);
    void transpose();
    double determinant();
    void exp(unsigned int level);
};

Matrix operator*(const double k, const Matrix& M);

Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

Matrix::Matrix(const size_t n) : rows(n), cols(n) {
    if (n == 0) {
        throw Matrix_Exception("Incorrect input matrix: size cannot be zero");
    }

    data = new MatrixItem[rows * cols]{};
}

Matrix::Matrix(const size_t row, const size_t col) : rows(row), cols(col) {
    if (row == 0 || col == 0) {
        throw Matrix_Exception("Incorrect input matrix: size cannot be zero");
    }

    data = new MatrixItem[rows * cols]{};
}

Matrix::Matrix(const Matrix& M) : rows(M.rows), cols(M.cols) {
    if (M.data) {
        data = new MatrixItem[rows * cols]{};
        std::copy(M.data, M.data + rows * cols, data);
    }
    else {
        throw Matrix_Exception("Incorrect input matrix: source matrix is empty");
    }
}

Matrix::Matrix(Matrix&& M) noexcept : rows(M.rows), cols(M.cols), data(M.data) {
    M.rows = 0;
    M.cols = 0;
    M.data = nullptr;
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix& Matrix::operator= (const Matrix& M) {
    if (this == &M) return *this;

    if (M.rows == 0 || M.cols == 0) {
        throw Matrix_Exception("Incorrect input matrix: source matrix is empty");
    }

    rows = M.rows;
    cols = M.cols;
    delete[] data;
    data = new MatrixItem[rows * cols]{};
    std::copy(M.data, M.data + rows * cols, data);
    return *this;
}

Matrix& Matrix::operator+= (const Matrix& M) {
    if ((rows != M.rows) or (cols != M.cols))
        throw Matrix_Exception("The matrix has an incorrect dimension");

    if (data && M.data) {
        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] += M.data[idx];
        }
    }
    else {
        throw Matrix_Exception("Your matrix is empty");
    }

    return *this;
}

Matrix& Matrix::operator-= (const Matrix& M) {
    if ((rows != M.rows) or (cols != M.cols))
        throw Matrix_Exception("The matrix has an incorrect dimension");

    if (data && M.data) {
        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] -= M.data[idx];
        }
    }
    else {
        throw Matrix_Exception("Your matrix is empty");
    }

    return *this;
}

Matrix& Matrix::operator*= (const double k) {
    if (data) {
        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] *= k;
        }
    }
    else {
        throw Matrix_Exception("Your matrix is empty");
    }

    return *this;
}

Matrix& Matrix::operator*= (const Matrix& M) {
    if (cols != M.rows)
        throw Matrix_Exception("The matrix has an incorrect dimension");

    Matrix R(rows, M.cols);
    R.set(ZERO);

    if (data && M.data) {
        for (size_t row = 0; row < R.rows; row++)
            for (size_t col = 0; col < R.cols; col++)
                for (size_t idx = 0; idx < M.rows; idx++)
                    R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col];

        cols = R.cols;
        rows = R.rows;
        delete[] data;
        data = R.data;
        R.data = nullptr;
    }
    else {
        throw Matrix_Exception("Your matrix or the source matrix is empty");
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix& K) const {
    Matrix result = *this;
    result += K;
    return result;
}

Matrix Matrix::operator-(const Matrix& K) const {
    Matrix result = *this;
    result -= K;
    return result;
}

Matrix Matrix::operator*(const Matrix& K) const {
    Matrix result = *this;
    result *= K;
    return result;
}

Matrix Matrix::operator*(const double k) const {
    Matrix result = *this;
    result *= k;
    return result;
}

Matrix operator*(const double k, const Matrix& M) {
    Matrix result = M;
    result *= k;
    return result;
}

void Matrix::print() {
    if (!data) throw Matrix_Exception("Your matrix is empty");

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
    if (!data) throw Matrix_Exception("Your matrix is empty");

    switch (mat_type) {
    case (ZERO):
        std::fill(data, data + cols * rows, 0.0);
        break;

    case (ONES):
        std::fill(data, data + cols * rows, 1.0);
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

void Matrix::transpose() {
    if (!data) throw Matrix_Exception("Your matrix is empty");

    MatrixItem* newData = new MatrixItem[rows * cols]{};

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < cols; col++)
            newData[row * cols + col] = data[col * rows + row];

    delete[] data;
    data = newData;
    std::swap(rows, cols);
}

double Matrix::determinant() {
    if (cols == 2) {
        if (data) {
            return data[0] * data[3] - data[1] * data[2];
        }
        else {
            throw Matrix_Exception("Your matrix is empty");
        }
    }

    if (cols == 3) {
        if (data) {
            return (data[0] * data[4] * data[8]) +
                (data[1] * data[5] * data[6]) +
                (data[2] * data[3] * data[7]) -
                (data[2] * data[4] * data[6]) -
                (data[0] * data[5] * data[7]) -
                (data[1] * data[3] * data[8]);
        }
        else {
            throw Matrix_Exception("Your matrix is empty");
        }
    }

    throw Matrix_Exception("Incorrect input matrix");
}

void Matrix::exp(unsigned int level) {
    if (!data) throw Matrix_Exception("Your matrix is empty");

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

int main(void) {
    try {
        unsigned int choice, run = 1;
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
                "14 - C.transpose()\n"
                "15 - C.determinant()\n"
                "16 - C.exp(20)\n"
                << std::endl;

            std::cout << "choice: " << std::endl;
            std::cin >> choice;

            switch (choice) {
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
                C.transpose();
                C.print();
                break;
            case 15:
                std::cout << C.determinant() << std::endl;
                break;
            case 16:
                C.exp(20);
                C.print();
                break;
            default:
                printf("wrong choice\n");
                break;
            }
        }
        return 0;
    }
    catch (const Matrix_Exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}
