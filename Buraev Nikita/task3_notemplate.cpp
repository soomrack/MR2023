#include <iostream>
#include <initializer_list>

class MatrixException : public std::exception
{
public:
    MatrixException(const std::string &message) : message(message) {}

    const char *what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message;
};

class Matrix
{
public:
    Matrix(std::initializer_list<std::initializer_list<double>> matrix);
    Matrix(std::initializer_list<double> matrix);
    Matrix(unsigned size);
    Matrix(const Matrix &original);
    ~Matrix();

    Matrix &operator=(const Matrix &right);

    Matrix operator+(const Matrix &right) const;
    Matrix &operator+=(const Matrix &right);
    Matrix operator-(const Matrix &right) const;
    Matrix &operator-=(const Matrix &right);
    Matrix operator*(const Matrix &right) const;
    Matrix &operator*=(const Matrix &right);

    Matrix operator+(double right) const;
    Matrix operator/(double right) const;
    Matrix operator-(double right) const;
    Matrix operator*(double right) const;

    Matrix &operator+=(double right);
    Matrix &operator-=(double right);
    Matrix &operator*=(double right);
    Matrix &operator/=(double right);

    double &operator()(std::size_t i, std::size_t j);
    const double &operator()(std::size_t i, std::size_t j) const;

    void print() const;
    double &element(std::size_t i, std::size_t j);
    double &element(std::size_t i);
    double &element(std::size_t i, std::size_t j) const;
    double &element(std::size_t i) const;

    Matrix transpose() const;
    Matrix power(unsigned n) const;
    bool is_square() const;
    std::size_t getRows() const;
    std::size_t getCols() const;

private:
    std::size_t rows;
    std::size_t cols;
    double **elements;

    void initializeElements(std::initializer_list<std::initializer_list<double>> matrix);
    void allocateMemory();
};

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> matrix)
{
    initializeElements(matrix);
}

Matrix::Matrix(std::initializer_list<double> matrix)
{
    initializeElements({matrix});
}

Matrix::Matrix(unsigned size)
{
    rows = cols = size;
    allocateMemory();

    for (unsigned i = 0; i < size; ++i)
        elements[i][i] = 1.0;
}

Matrix::Matrix(const Matrix &original)
{
    rows = original.rows;
    cols = original.cols;
    allocateMemory();

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] = original.elements[i][j];
}

Matrix::~Matrix()
{
    // Deallocate memory when the object is destroyed
    for (std::size_t i = 0; i < rows; ++i)
        delete[] elements[i];
    delete[] elements;
}

Matrix &Matrix::operator=(const Matrix &right)
{
    if (&right == this)
        return *this;

    if (rows != right.rows || cols != right.cols)
    {
        throw MatrixException("Matrix assignment requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] = right.elements[i][j];

    return *this;
}

Matrix Matrix::operator+(const Matrix &right) const
{
    if (rows != right.rows || cols != right.cols)
    {
        throw MatrixException("Matrix addition requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] + right.elements[i][j];

    return result;
}

Matrix &Matrix::operator+=(const Matrix &right)
{
    if (rows != right.rows || cols != right.cols)
    {
        throw MatrixException("Matrix addition requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] += right.elements[i][j];

    return *this;
}

Matrix Matrix::operator-(const Matrix &right) const
{
    if (rows != right.rows || cols != right.cols)
    {
        throw MatrixException("Matrix subtraction requires matrices of the same dimensions.");
    }

    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] - right.elements[i][j];

    return result;
}

Matrix &Matrix::operator-=(const Matrix &right)
{
    if (rows != right.rows || cols != right.cols)
    {
        throw MatrixException("Matrix subtraction requires matrices of the same dimensions.");
    }

    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            elements[i][j] -= right.elements[i][j];

    return *this;
}

Matrix Matrix::operator*(const Matrix &right) const
{
    if (cols != right.rows)
    {
        throw MatrixException("Matrices are incompatible for multiplication.");
    }

    Matrix result(rows, right.cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < right.cols; ++j)
        {
            double sum = 0.0;
            for (std::size_t k = 0; k < cols; ++k)
                sum += elements[i][k] * right.elements[k][j];

            result.elements[i][j] = sum;
        }

    return result;
}

Matrix &Matrix::operator*=(const Matrix &right)
{
    *this = *this * right;
    return *this;
}

Matrix Matrix::operator+(double right) const
{
    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] + right;

    return result;
}

Matrix Matrix::operator/(double right) const
{
    if (right == 0)
    {
        throw MatrixException("Division by zero.");
    }

    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] / right;

    return result;
}

Matrix Matrix::operator-(double right) const
{
    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] - right;

    return result;
}

Matrix Matrix::operator*(double right) const
{
    Matrix result(rows, cols);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] * right;

    return result;
}

Matrix &Matrix::operator+=(double right)
{
    *this = *this + right;
    return *this;
}

Matrix &Matrix::operator-=(double right)
{
    *this = *this - right;
    return *this;
}

Matrix &Matrix::operator*=(double right)
{
    *this = *this * right;
    return *this;
}

Matrix &Matrix::operator/=(double right)
{
    *this = *this / right;
    return *this;
}

double &Matrix::operator()(std::size_t i, std::size_t j)
{
    if (i >= rows || j >= cols)
    {
        throw MatrixException("Matrix index out of bounds!");
    }

    return elements[i][j];
}

const double &Matrix::operator()(std::size_t i, std::size_t j) const
{
    if (i >= rows || j >= cols)
    {
        throw MatrixException("Matrix index out of bounds!");
    }

    return elements[i][j];
}

void Matrix::print() const
{
    for (std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
            std::cout << elements[i][j] << " ";

        std::cout << std::endl;
    }
}

double &Matrix::element(std::size_t i, std::size_t j)
{
    if (i >= rows || j >= cols)
    {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ", " + std::to_string(j) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }
    return elements[i][j];
}

double &Matrix::element(std::size_t i)
{
    if (rows > 1)
    {
        throw MatrixException("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols)
    {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }

    if (rows == 0 && cols == 0)
    {
        throw MatrixException("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

double &Matrix::element(std::size_t i, std::size_t j) const
{
    if (i >= rows || j >= cols)
    {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ", " + std::to_string(j) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }
    return elements[i][j];
}

double &Matrix::element(std::size_t i) const
{
    if (rows > 1)
    {
        throw MatrixException("Incorrect use of index! Matrix has more than one row\nUse Matrix::element(row, col) instead.");
    }

    if (i >= cols)
    {
        throw MatrixException("Matrix index out of bounds! "
                              "Index (" + std::to_string(i) + ")"
                              " exceeds matrix dimensions (" + std::to_string(rows) + ", " + std::to_string(cols) + ")"
                              " in file " + std::string(__FILE__) + " at line " + std::to_string(__LINE__));
    }

    if (rows == 0 && cols == 0)
    {
        throw MatrixException("Matrix is empty! Index out of bounds!");
    }

    return elements[0][i];
}

Matrix Matrix::transpose() const
{
    Matrix result(cols, rows);
    for (std::size_t i = 0; i < rows; ++i)
        for (std::size_t j = 0; j < cols; ++j)
            result.elements[j][i] = elements[i][j];

    return result;
}

Matrix Matrix::power(unsigned n) const
{
    if (!is_square())
    {
        throw MatrixException("Matrix is incompatible for power() | rows != cols\n");
    }

    if (n == 0)
    {
        Matrix result(rows);
        return result;
    }

    Matrix result(rows, cols);
    result = *this;

    for (unsigned i = 1; i < n; ++i)
    {
        result *= *this;
    }

    return result;
}

bool Matrix::is_square() const
{
    return rows == cols;
}

std::size_t Matrix::getRows() const
{
    return rows;
}

std::size_t Matrix::getCols() const
{
    return cols;
}

void Matrix::initializeElements(std::initializer_list<std::initializer_list<double>> matrix)
{
    rows = matrix.size();
    cols = (rows > 0) ? matrix.begin()->size() : 0;
    allocateMemory();

    std::size_t i = 0;
    for (const auto &mat : matrix)
    {
        std::size_t j = 0;
        for (const auto &elem : mat)
        {
            elements[i][j] = elem;
            ++j;
        }
        ++i;
    }
}

void Matrix::allocateMemory()
{
    elements = new double *[rows];
    for (std::size_t i = 0; i < rows; ++i)
    {
        elements[i] = new double[cols];
    }
}
