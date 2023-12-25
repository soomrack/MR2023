#include "matrix.hpp"


namespace MatrixSpace 
{
Matrix::Matrix(size_t m_rows, size_t m_cols) : m_rows(m_rows), m_cols(m_cols), m_type(MatrixType::Zero_Matrix)
{
    if (m_rows == 0 || m_cols == 0) 
    {   
        throw MatrixException("Bad arguments passed to the constructor");
    }
    m_data = new double[m_rows * m_cols];
}

Matrix::Matrix(size_t m_rows, size_t m_cols, MatrixType type) : m_rows(m_rows), m_cols(m_cols), m_type(type)
{
    if (m_rows >= SIZE_MAX / sizeof(double) / m_cols)
    {
        throw MatrixException("Memory allocation error");
    } 

    if (m_rows == 0 || m_cols == 0) 
    {   
        throw MatrixException("Bad arguments passed to the constructor");
    }

    m_data = new double[m_rows * m_cols];
    this->fill_matrix(type);
}

Matrix::Matrix(const Matrix &other) : m_rows(other.m_rows), m_cols(other.m_cols), m_type(other.m_type) 
{
    if (m_rows >= SIZE_MAX / sizeof(double) / m_cols)
    {
        throw MatrixException("Memory allocation error");
    }

    if (m_rows == 0 || m_cols == 0) 
    {   
        throw MatrixException("Bad arguments passed to the constructor");
    }

    m_data = new double[m_rows * m_cols];
    std::memcpy(m_data, other.m_data, m_rows * m_cols * sizeof(double));
}

Matrix::Matrix(Matrix &&M) noexcept : m_rows(M.m_rows), m_cols(M.m_cols), m_data(M.m_data)
{
    M.m_rows = 0;
    M.m_cols = 0;
    M.m_data = nullptr;
}

Matrix::~Matrix() 
{
    delete[] m_data;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) 
{
    for (size_t i = 0; i < matrix.m_rows; ++i) 
    {
        for (size_t j = 0; j < matrix.m_cols; ++j) 
        {
            os << matrix.m_data[i * matrix.m_cols + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

double &Matrix::operator()(size_t row, size_t col) 
{ 
    return m_data[row * m_cols + col];
}

Matrix &Matrix::operator=(const Matrix &M) 
{
    if (this == &M) 
    {
        return *this;
    }

    double* new_data = static_cast<double*>(realloc(m_data, M.m_rows * M.m_cols * sizeof(double)));
    if (!new_data) 
    {
        throw std::bad_alloc(); 
    }

    m_rows = M.m_rows;
    m_cols = M.m_cols;
    m_data = new_data;

    std::memcpy(m_data, M.m_data, m_rows * m_cols * sizeof(double));
    return *this;
}

Matrix &Matrix::operator=(Matrix &&M)
{
    if (m_rows >= SIZE_MAX / sizeof(double) / m_cols)
    {
        throw MatrixException("Memory allocation error");
    }

    if (this == &M)
    {
        return *this;
    }

    std::swap(m_rows, M.m_rows);
    std::swap(m_cols, M.m_cols);
    std::swap(m_data, M.m_data);
    std::swap(m_type, M.m_type);

    return *this;
}

Matrix Matrix::operator+(const Matrix &M) const
{
    if (m_data == nullptr || M.m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_rows != M.m_rows || m_cols != M.m_cols)
    {
        throw MatrixException("Matrix dimensions do not match");
    } 
    
    Matrix result(*this);
    for (size_t row = 0; row < m_rows; row++) 
    {
        for (size_t col = 0; col < m_cols; col++) 
        {
            result.m_data[row * result.m_cols + col] = m_data[row * m_cols + col] + M.m_data[row * M.m_cols + col];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &M) const 
{
    if (m_data == nullptr || M.m_data == nullptr)
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_rows != M.m_rows || m_cols != M.m_cols)
    {
        throw MatrixException("Matrix dimensions do not match");
    } 

    Matrix sub{m_rows, m_cols, MatrixType::Zero_Matrix};
    for (size_t idx = 0; idx < m_rows * m_cols; idx++) 
    {
        sub.m_data[idx] = m_data[idx] - M.m_data[idx];
    }

    return sub;
}

Matrix Matrix::operator*(double scalar) const 
{
    if (m_data == nullptr)
    {
        throw MatrixException("Bad matrix error");
    }

    Matrix result{m_rows, m_cols};
    for (size_t idx = 0; idx < m_rows * m_cols; idx++) 
    {
        result.m_data[idx] = m_data[idx] * scalar;
    }

    return result;
}

Matrix Matrix::operator*(const Matrix &M) const 
{
    if (m_data == nullptr || M.m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_cols != M.m_rows)
    {
        throw MatrixException("Matrix outer dimensions do not match");
    } 

    Matrix result{m_rows, M.m_cols, MatrixType::Zero_Matrix};
    
    #pragma omp parallel for
    for (size_t this_row = 0; this_row < m_rows; this_row++)
    {
        for (size_t M_col = 0; M_col < M.m_cols; M_col++)
        {
            double& resultElement = result.m_data[this_row * m_cols + M_col];
            for (size_t idx = 0; idx < m_cols; idx++)
            {
                size_t thisIdx = this_row * m_cols + idx;
                size_t MIdx = idx * M.m_cols + M_col;
                resultElement += m_data[thisIdx] * M.m_data[MIdx];
            }
        }
    }

    return result;
}

void Matrix::operator+=(const Matrix &M) 
{
    if (m_data == nullptr || M.m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_rows != M.m_rows || m_cols != M.m_cols) 
    {
        throw MatrixException("Matrix dimensions do not match");
    }

    for (size_t idx = 0; idx < m_rows * m_cols; idx++)
    {
        m_data[idx] += M.m_data[idx];
    } 
}

void Matrix::operator-=(const Matrix &M) 
{
    if (m_data == nullptr || M.m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_rows != M.m_rows || m_cols != M.m_cols) 
    {
        throw MatrixException("Matrix dimensions do not match");
    }

    for (size_t idx = 0; idx < m_rows * m_cols; ++idx)
    {
        m_data[idx] -= M.m_data[idx];
    } 
}

void Matrix::operator*=(double scalar) 
{
    if (m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    for (size_t idx = 0; idx < m_rows * m_cols; idx++) 
    {
        m_data[idx] *= scalar;
    }
}

void Matrix::operator*=(const Matrix &M) 
{
    if (m_data == nullptr || M.m_data == nullptr)
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_cols != M.m_rows) 
    {
        throw MatrixException("Matrix dimensions do not match for multiplication");
    }
    

    Matrix result{m_rows, M.m_cols, MatrixType::Zero_Matrix};

    #pragma omp parallel for
    for (size_t this_row = 0; this_row < m_rows; this_row++)
    {
        for (size_t M_col = 0; M_col < M.m_cols; M_col++)
        {
            double& resultElement = result.m_data[this_row * m_cols + M_col];
            for (size_t idx = 0; idx < m_cols; idx++)
            {
                size_t thisIdx = this_row * m_cols + idx;
                size_t MIdx = idx * M.m_cols + M_col;
                resultElement += m_data[thisIdx] * M.m_data[MIdx];
            }
        }
    }

    *this = result;
}

Matrix Matrix::transpose() 
{
    if (m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    Matrix result{m_cols, m_rows};

    for (size_t row = 0; row < m_rows; row++)
    {
        for (size_t col = 0; col < m_cols; col++)
        {
            result.m_data[row * m_rows + col] = m_data[col * m_cols + row];
        }
    }
    return result;
}

double Matrix::determinant() 
{
    if (m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }
    
    if (m_cols != m_rows) 
    {
        throw MatrixException("Matrix should be square");
    }

    if (m_cols == 1)
    {
        return static_cast<double>(m_data[0]);
    }

    if (m_cols == 2)
    {
        return static_cast<double>(m_data[0] * m_data[3] - m_data[1] * m_data[2]);
    }
    if (m_cols == 3)
    {
        return static_cast<double>(m_data[0] * m_data[4] * m_data[8]) + (m_data[1] * m_data[5] * m_data[6]) + \
                                    (m_data[2] * m_data[3] * m_data[7]) - (m_data[2] * m_data[4] * m_data[6]) - \
                                    (m_data[0] * m_data[5] * m_data[7]) - (m_data[1] * m_data[3] * m_data[8]);
    }
    throw MatrixException("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrices");
}


Matrix Matrix::exponent(unsigned int n) const 
{
    if (m_data == nullptr) 
    {
        throw MatrixException("Bad matrix error");
    }

    if (m_cols != m_rows)
    {
        throw MatrixException("Matrix should be square");
    } 

    Matrix exponent{m_rows, m_cols, MatrixType::Identity_Matrix};
    Matrix summand{m_rows, m_cols, MatrixType::Identity_Matrix};

    if (n == 0) 
    {
        return exponent;
    }

    if (n == 1) 
    {
        exponent += (*this);
        return exponent;
    }

    for (unsigned int idx = 1; idx <= n; idx++) 
    {
        summand *= (*this);
        summand *= (1. / idx);
        exponent += summand;
    }

    return exponent;
}

void Matrix::fill_matrix(MatrixType type)
{
    if (m_rows == 0 || m_cols == 0) 
    {
        throw MatrixException("No columns or m_rows to fill");
    } 

    switch (type) 
    {
        case (MatrixType::Zero_Matrix):
            std::memset(m_data, 0, m_cols * m_rows * sizeof(double));
            break;
        case (MatrixType::Ones_Matrix):
            std::memset(m_data, 1, m_cols * m_rows * sizeof(double));
            break;
        case (MatrixType::Identity_Matrix):
            if (m_cols != m_cols) 
            {
                throw MatrixException("Bad matrix dimension");
            } 
            for (size_t row = 0; row < m_rows; row++) 
            {
                for (size_t col = 0; col < m_cols; col++) 
                {
                    m_data[row * m_cols + col] = (row == col) ? 1. : 0.;
                }
            }
            break;
        case (MatrixType::Random_Matrix):
            this->random();
            break;
    }
}

void Matrix::random()
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (size_t row = 0; row < m_rows; row++) 
    {
        for (size_t col = 0; col < m_cols; col++) 
        {
            m_data[row * m_cols + col] = rand() % 100;
        }
    }
}
}; // MatrixSpace