#include <iostream>

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
    ~Matrix();

public:
    Matrix& operator = (const Matrix& M);
    Matrix& operator += (const Matrix& M);
    Matrix& operator -= (const Matrix& M);
    Matrix& operator *= (const double k);
    Matrix& operator *= (const Matrix& M);

    Matrix& operator + (const Matrix& M);
    Matrix& operator - (const Matrix& M);
    Matrix& operator * (const Matrix& M);
    Matrix& operator * (const double k);

public:
    void print();
    void fill(enum MatrixType mat_type);
    void transposition(const Matrix& M);
    double determinant(void);
    void exp(const unsigned int level);
};


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


Matrix::~Matrix() {
    rows = 0;
    cols = 0;
}


void Matrix::print()
{
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


void Matrix::fill(enum MatrixType mat_type)
{
    switch (mat_type)
    {
    case (ZERO):
        for (size_t idx = 0; idx < cols * rows; idx++)
            data[idx] = 0.0;
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
        for (size_t row = 0; row < rows; row++)
            for (size_t col = 0; col < cols; col++)
            {
                if (col == row)
                    data[row * cols + col] = 1;
                else
                    data[row * cols + col] = 0;
            }
        break;
    }   
}


void Matrix::transposition(const Matrix& M)
{
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
}


void Matrix::exp(const unsigned int level) {
    Matrix R(rows, cols);
    R.fill(I);

    double n = 1;
    Matrix temp = R;
    for (unsigned int idx = 1; idx < level; idx++) {
        temp *= *this;
        n /= (idx);
        R += (temp * n); //почему то tmp = R
    }

    *this = R;
}


Matrix& Matrix::operator = (const Matrix& M) {
    if (this != &M) {
        if (data != nullptr)
            delete[] data;

        rows = M.rows;
        cols = M.cols;

        this->data = new double[rows * cols];
        for (size_t idx = 0; idx < rows * cols; idx++) {
            data[idx] = M.data[idx];
        }
    }

    return *this;
}


Matrix& Matrix::operator += (const Matrix& M) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator -= (const Matrix& M) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator *= (const double k) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
    return *this;
}


Matrix& Matrix::operator *= (const Matrix& M) {
    Matrix R(rows, M.cols);
    R.fill(ZERO);
    for (size_t row = 0; row < R.rows; row++)
        for (size_t col = 0; col < R.cols; col++)
            for (size_t idx = 0; idx < M.rows; idx++)
                R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col];            
    return R;
}


Matrix& Matrix::operator + (const Matrix& M) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] += M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator - (const Matrix& M) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] -= M.data[idx];
    }
    return *this;
}


Matrix& Matrix::operator * (const Matrix& M) {
    Matrix R(rows, M.cols);
    R.fill(ZERO);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < M.cols; col++)
            for (size_t idx = 0; idx < cols; idx++)
                R.data[row * cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col];
    return R;
}


Matrix& Matrix::operator * (const double k) {
    for (size_t idx = 0; idx < rows * cols; idx++) {
        data[idx] *= k;
    }
    return *this;
}


int main(void)
{
    Matrix A(3), B(3, 3), C(3);
    A.fill(I);
    A.print();

    B.fill(RANDOM);
    B.print();

    C.fill(I);
    //C.print();

    //C.transposition(A);
    //std::cout << C.determinant() << std::endl;
    C.exp(20);
    //C = A;
    //C += A;
    //C -= A;
    //C *= 2.0;
    //C *= B;
    // 
    //C = A + B;
    //C = A - B;
    //C = A * 2;
    //C = A * B;

    C.print();
    return 0;
}
