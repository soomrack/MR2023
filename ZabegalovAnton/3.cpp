#include <iostream>
#include <string>
#include <cstring>

typedef double MatrixItem;
enum MatrixType { ZERO, ONES, RANDOM, I };

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
    Matrix(Matrix&& M);
    ~Matrix();

public:
    Matrix& operator= (const Matrix& M);
    Matrix& operator+= (const Matrix& M);
    Matrix& operator-= (const Matrix& M);
    Matrix& operator*= (const double k);
    Matrix& operator*= (const Matrix& M);

public:
    void print();
    void set(enum MatrixType mat_type);
    void transposition(const Matrix& M);
    double determinant(void);
    void exp(const unsigned int level);
};


Matrix operator+(const Matrix& M, const Matrix& K);
Matrix operator-(const Matrix& M, const Matrix& K);
Matrix operator*(const Matrix& M, const Matrix& K);
Matrix operator*(const double k, const Matrix& M);
Matrix operator*(const Matrix& M, const double k);


class Matrix_Exception : public std::exception
{
private:
    std::string message;
public:
    Matrix_Exception(std::string message) : message{ message } {}
    std::string get_message() const { return message; }
};

Matrix_Exception INCORRECT_INPUT_MATRIX("Incorrect input matrix\n");
Matrix_Exception INCORRECT_DIMENTION_OF_MATRIX("The matrix has an incorrect dimension\n");
Matrix_Exception NULL_MATRIX("Your matrix is empty\n");
Matrix_Exception OTHER_ERROR("An unfamiliar error\n");


Matrix::Matrix() {
    rows = 0;
    cols = 0;
    data = nullptr;
}


Matrix::Matrix(const size_t n) {
    rows = n;
    cols = n;

    data = new MatrixItem[n * n];
}


Matrix::Matrix(const size_t row, const size_t col) {
    rows = row;
    cols = col;

    data = new MatrixItem[row * col];
}


Matrix::Matrix(const Matrix& M) {
    rows = M.rows;
    cols = M.cols;

    delete[] data;
    data = new MatrixItem[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        data[idx] = M.data[idx];
    }
}


Matrix::Matrix(Matrix&& M) {
    rows = M.rows;
    cols = M.cols;
    data = M.data;

    M.rows = 0;
    M.cols = 0;
    M.data = nullptr;
}


Matrix::~Matrix() {
    rows = 0;
    cols = 0;
    delete[] data;
}


void Matrix::print()
{
    if (data == nullptr) throw NULL_MATRIX;

    std::cout <<  "\n";
    for (size_t r = 0; r < rows; r++) {
        std::cout << "[";
        for (size_t c = 0; c < cols; c++) {
            std::cout << data[r * cols + c];
            if (cols != cols - 1)
                std::cout << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}


void Matrix::set(enum MatrixType mat_type)
{
    switch (mat_type)
    {
    case (ZERO):
        memset(data, 0, cols * rows * sizeof(MatrixItem));        
        break;

    case (ONES):
        for (size_t idx = 0; idx < cols * rows; idx++)
            data[idx] = 1.0;
        break;

    case (RANDOM):
        for (size_t idx = 0; idx < cols * rows; idx++)
            data[idx] = (MatrixItem)(rand() % 10);
        break;

    case (I):
        this->set(ZERO);
        for (size_t row_col = 0; row_col < rows; row_col++) 
            data[row_col * cols + row_col] = 1;
        break;
    }   
}


void Matrix::transposition(const Matrix& M)
{
    if (data == nullptr) throw NULL_MATRIX;

    for (size_t row = 0; row < M.rows; row++)
        for (size_t col = 0; col < M.cols; col++)
            data[row * M.rows + col] = M.data[col * M.cols + row];
}


double Matrix::determinant(void)
{
    if (cols == 2) {
        return data[0] * data[3] - data[1] * data[2];
    }

    if (cols == 3) {
        return (data[0] * data[4] * data[8]) + \
            (data[1] * data[5] * data[6]) + \
            (data[2] * data[3] * data[7]) - \
            (data[2] * data[4] * data[6]) - \
            (data[0] * data[5] * data[7]) - \
            (data[1] * data[3] * data[8]);
    }

    else throw INCORRECT_INPUT_MATRIX;
}


void Matrix::exp(const unsigned int level) {
    if (data == nullptr) throw NULL_MATRIX;

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
    if (data != nullptr) delete data;

    rows = M.rows;
    cols = M.cols;

    this->data = new MatrixItem[rows * cols];
    memcpy(data, M.data, cols * rows * sizeof(MatrixItem));

    return *this;
}


Matrix& Matrix::operator+= (const Matrix& M) { 
    if ((rows != M.rows) or (cols != M.cols)) 
        throw INCORRECT_DIMENTION_OF_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator-= (const Matrix& M) {
    if ((rows != M.rows) or (cols != M.cols))
        throw INCORRECT_DIMENTION_OF_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator*= (const double k) {
    if (data == nullptr) throw NULL_MATRIX;

    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
    return *this;
}


Matrix& Matrix::operator*= (const Matrix& M) {
    if (cols != M.rows)
        throw INCORRECT_DIMENTION_OF_MATRIX;

    Matrix R(rows, M.cols);
    R.set(ZERO);
    for (size_t row = 0; row < R.rows; row++)
        for (size_t col = 0; col < R.cols; col++)
            for (size_t idx = 0; idx < M.rows; idx++)
                R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col]; 
    
    cols = R.cols;
    rows = R.rows;
    data = R.data;
    R.data = nullptr;
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



int main(void)
{
    try {
        Matrix A(3), B(3, 3), C(4);

        A.set(RANDOM);
        B.set(RANDOM);
        C.set(I);

        A.print();
        B.print();
        C.print();
         
        C = A + B;
        C.print();  
        return 0;
    }
    catch (const Matrix_Exception& exception)
    {
        std::cout << exception.get_message() << std::endl;
    }
}
