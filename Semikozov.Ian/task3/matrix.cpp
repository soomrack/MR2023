#include "matrix.hpp"

namespace MatrixSpace 
{
    Matrix::Matrix(size_t m_rows, size_t m_cols) : m_rows(m_rows), m_cols(m_cols), m_type(Matrix_Type::Zero_Matrix)
    {
        if (m_rows == 0 || m_cols == 0) 
        {   
            throw Matrix_Exception("Bad arguments passed to the constructor");
        }
        m_data = new double[m_rows * m_cols];
    }

    Matrix::Matrix(size_t m_rows, size_t m_cols, Matrix_Type type) : m_rows(m_rows), m_cols(m_cols), m_type(type)
    {
        if (m_rows == 0 || m_cols == 0) 
        {   
            throw Matrix_Exception("Bad arguments passed to the constructor");
        }
        m_data = new double[m_rows * m_cols];
        this->fill_matrix(type);
    }

    Matrix::Matrix(const Matrix& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_type(other.m_type) 
    {
        if (m_rows == 0 || m_cols == 0) 
        {   
            throw Matrix_Exception("Bad arguments passed to the constructor");
        }
        m_data = new double[m_rows * m_cols];
        std::copy(other.m_data, other.m_data + m_rows * m_cols, m_data);
    }

    Matrix::~Matrix() 
    {
        if (m_data != nullptr)
        {
            delete[] m_data;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) 
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

    double &Matrix::operator()(int row, int col) 
    { 
        return m_data[row * m_cols + col];
    }

    // Copy assignment operator definition
    Matrix& Matrix::operator=(const Matrix& M) {
        if (this != &M) {
            // Deallocate existing memory
            delete[] m_data;

            // Allocate new memory
            m_rows = M.m_rows;
            m_cols = M.m_cols;
            m_data = new double[m_rows * m_cols];

            // Copy data
            std::copy(M.m_data, M.m_data + m_rows * m_cols, m_data);
        }
        return *this;
    }

    // Move assignment operator definition
    Matrix& Matrix::operator=(Matrix&& M) noexcept {
        if (this != &M) {
            // Deallocate existing memory
            delete[] m_data;

            // Move data
            m_rows = M.m_rows;
            m_cols = M.m_cols;
            m_data = M.m_data;

            // Reset the source object
            M.m_rows = 0;
            M.m_cols = 0;
            M.m_data = nullptr;
        }
        return *this;
    }

    Matrix Matrix::operator+(const Matrix &M) const
    {
        if (m_data == nullptr || M.m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_rows != M.m_rows || m_cols != M.m_cols) throw Matrix_Exception("Matrix dimensions do not match");
        Matrix result(*this);
        for (size_t i = 0; i < m_rows; ++i) 
        {
            for (size_t j = 0; j < m_cols; ++j) 
            {
                result.m_data[i * result.m_cols + j] = m_data[i * m_cols + j] + M.m_data[i * M.m_cols + j];
            }
        }
        return result;
    }
    Matrix Matrix::operator-(const Matrix &M) const 
    {
        if (m_data == nullptr || M.m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_rows != M.m_rows || m_cols != M.m_cols) throw Matrix_Exception("Matrix dimensions do not match");

        Matrix sub = {m_rows, m_cols, Matrix_Type::Zero_Matrix};
        for (size_t idx = 0; idx < m_rows * m_cols; idx++)
            sub.m_data[idx] = m_data[idx] - M.m_data[idx];
        return sub;
    }

    Matrix Matrix::operator*(double scalar) const {
        if (m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        Matrix product = {m_rows, m_cols};
        for (size_t idx = 0; idx < m_rows * m_cols; idx++) product.m_data[idx] = m_data[idx] * scalar;
        return product;
    }

    Matrix Matrix::operator*(const Matrix &M) const {
        if (m_data == nullptr || M.m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_cols != M.m_rows) throw Matrix_Exception("Matrix outer dimensions do not match");

        Matrix product = {m_rows, M.m_cols, Matrix_Type::Zero_Matrix};
        for (size_t this_row = 0; this_row < m_rows; this_row++)
            for (size_t M_col = 0; M_col < M.m_cols; M_col++)
                for (size_t idx = 0; idx < m_cols; idx++)
                    product.m_data[this_row * m_cols + M_col] +=
                            m_data[this_row * m_cols + idx] * M.m_data[idx * M.m_cols + M_col];
        return product;
    }

    void Matrix::operator+=(const Matrix &M) {
        if (m_data == nullptr || M.m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_rows != M.m_rows || m_cols != M.m_cols) throw Matrix_Exception("Matrix dimensions do not match");

        for (size_t idx = 0; idx < m_rows * m_cols; idx++) m_data[idx] += M.m_data[idx];
    }


    void Matrix::operator-=(const Matrix &M) {
        if (m_data == nullptr || M.m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_rows != M.m_rows || m_cols != M.m_cols) throw Matrix_Exception("Matrix dimensions do not match");

        for (size_t idx = 0; idx < m_rows * m_cols; ++idx) m_data[idx] -= M.m_data[idx];
    }


    void Matrix::operator*=(double scalar) {
        if (m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        for (size_t idx = 0; idx < m_rows * m_cols; idx++) m_data[idx] *= scalar;
    }


    void Matrix::operator*=(const Matrix &M) {
        if (m_data == nullptr || M.m_data == nullptr)
            throw Matrix_Exception("Bad matrix error");

        if (m_cols != M.m_rows)
            throw Matrix_Exception("Matrix dimensions do not match for multiplication");

        Matrix product{m_rows, M.m_cols, Matrix_Type::Zero_Matrix};

        for (size_t this_row = 0; this_row < m_rows; this_row++)
            for (size_t M_col = 0; M_col < M.m_cols; M_col++)
                for (size_t idx = 0; idx < m_cols; idx++)
                    product.m_data[this_row * m_cols + M_col] +=
                            m_data[this_row * m_cols + idx] * M.m_data[idx * M.m_cols + M_col];

        *this = product;
    }


    Matrix Matrix::transpose() {
        if (m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        Matrix transposed = {m_cols, m_rows};
        for (size_t row = 0; row < m_rows; row++)
            for (size_t col = 0; col < m_cols; col++)
                transposed.m_data[row * m_rows + col] = m_data[col * m_cols + row];
        return transposed;
    }


    double Matrix::determinant() {
        if (m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_cols != m_rows) throw Matrix_Exception("Matrix should be square");

        if (m_cols == 1)
            return (double) m_data[0];
        if (m_cols == 2)
            return (double) (m_data[0] * m_data[3] - m_data[1] * m_data[2]);
        if (m_cols == 3)
            return (double) (m_data[0] * m_data[4] * m_data[8]) + \
                    (m_data[1] * m_data[5] * m_data[6]) + \
                    (m_data[2] * m_data[3] * m_data[7]) - \
                    (m_data[2] * m_data[4] * m_data[6]) - \
                    (m_data[0] * m_data[5] * m_data[7]) - \
                    (m_data[1] * m_data[3] * m_data[8]);
        throw Matrix_Exception("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrices");
    }


    Matrix Matrix::exponent(unsigned int n) const {
        if (m_data == nullptr) throw Matrix_Exception("Bad matrix error");

        if (m_cols != m_rows) throw Matrix_Exception("Matrix should be square");

        Matrix exponent{m_rows, m_cols, Matrix_Type::Identity_Matrix};
        Matrix summand{m_rows, m_cols, Matrix_Type::Identity_Matrix};

        if (n == 0) return exponent;

        if (n == 1) {
            exponent += (*this);
            return exponent;
        }

        for (unsigned int idx = 1; idx <= n; idx++) {
            summand *= (*this);
            summand *= (1. / idx);
            exponent += summand;
        }

        return exponent;
    }

    void Matrix::fill_matrix(Matrix_Type type)
    {
        if (m_rows == 0 || m_cols == 0) {
            throw Matrix_Exception("No columns or m_rows to fill");
        } 

        switch (type) {
            case (Matrix_Type::Zero_Matrix):
                std::memset(m_data, 0, m_cols * m_rows * sizeof(double));
                break;
            case (Matrix_Type::Ones_Matrix):
                std::memset(m_data, 1, m_cols * m_rows * sizeof(double));
                break;
            case (Matrix_Type::Identity_Matrix):
                if (m_cols == m_cols) 
                {
                    for (size_t i = 0; i < m_rows; i++) 
                    {
                        for (size_t j = 0; j < m_cols; j++) 
                        {
                            m_data[i * m_cols + j] = (i == j) ? 1. : 0.;
                        }
                    }
                } 
                else 
                {
                    throw Matrix_Exception("Bad matrix dimension");
                }
                break;
            case (Matrix_Type::Random_Matrix):
                this->random();
                break;
        }
    }

    void Matrix::random()
    {
        srand(static_cast<unsigned>(time(nullptr)));
        for (size_t i = 0; i < m_rows; ++i) {
            for (size_t j = 0; j < m_cols; ++j) {
                m_data[i * m_cols + j] = rand() % 100;
            }
        }
    }
}; // MatrixSpace