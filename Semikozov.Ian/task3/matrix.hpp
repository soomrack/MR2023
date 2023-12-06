#pragma once 

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>
#include <stdint.h>

namespace Matrix 
{
    enum class Matrix_Type : uint8_t 
    {
        Zero_Matrix,
        Ones_Matrix,
        Identity_Matrix, 
        Random_Matrix
    };

    template <typename Matrix_Item>
    class Matrix
    {
    private:
        class Matrix_Exception : public std::exception {
        private:
            Matrix_Exception(std::string msg) : exception_msg(std::move(msg)) {}
            std::string exception_msg;
        public:
            const char *what() const noexcept override 
            { 
                return exception_msg.c_str(); 
            }
            friend class Matrix;
        };

        size_t m_rows{0};
        size_t m_cols{0};
        Matrix_Type m_type;
        Matrix_Item **m_data{nullptr};
    public:
        Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_type(Matrix_Type::Zero_Matrix)
        {
            if (m_rows == 0 || m_cols == 0) 
            {   
                throw Matrix_Exception("Bad arguments passed to the constructor");
            }
            m_data = new Matrix_Item*[rows];
            for (int i = 0; i < rows; ++i) 
            {
                m_data[i] = new Matrix_Item[cols];
            }
        }

        Matrix(size_t rows, size_t cols, Matrix_Type type) : m_rows(rows), m_cols(cols), m_type(type)
        {
            m_data = new Matrix_Item*[rows];
            for (int i = 0; i < rows; ++i) {
                m_data[i] = new Matrix_Item[cols];
            }
            fill_matrix(type);
        }

        Matrix(const Matrix& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_type(other.m_type) 
        {
            m_data = new int*[m_rows];
            for (int i = 0; i < m_rows; ++i) {
                m_data[i] = new int[m_cols];
                for (int j = 0; j < m_cols; ++j) {
                    m_data[i][j] = other.m_data[i][j];
                }
            }
        }

        ~Matrix() 
        {
            for (int i = 0; i < m_rows; ++i) {
                delete[] m_data[i];
            }
            delete[] m_data;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) 
        {
            for (int i = 0; i < matrix.m_rows; ++i) {
                for (int j = 0; j < matrix.m_cols; ++j) {
                    os << matrix.m_data[i][j] << " ";
                }
                os << std::endl;
            }
            return os;
        }

        Matrix_Item &operator()(int rows, int cols) 
        { 
            return m_data[rows][cols];
        }
        
        Matrix &operator=(const Matrix &M) 
        {
            if (this != &M) {
                for (int i = 0; i < m_rows; ++i) {
                    delete[] m_data[i];
                }
                delete[] m_data;

                // new matrix allocation
                m_rows = M.m_rows;
                m_cols = M.m_cols;
                m_data = new int*[m_rows];
                for (int i = 0; i < m_rows; ++i) {
                    m_data[i] = new int[m_cols];
                    for (int j = 0; j < m_cols; ++j) {
                        m_data[i][j] = M.m_data[i][j];
                    }
                }
            }
            return *this;
        }

        Matrix &operator=(Matrix &&M) noexcept
        {
            if (this != &M) 
            {
                for (int i = 0; i < m_rows; ++i) 
                {
                    delete[] m_data[i];
                }
                delete[] m_data;
                
                m_rows = M.m_rows;
                m_cols = M.m_cols;
                m_data = M.m_data;
            }
            return *this;
        }
        Matrix operator+(const Matrix &M) const
        {
            Matrix result(this);
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    result.m_data[i][j] = m_data[i][j] + M.m_data[i][j];
                }
            }
            return result;
        }
        Matrix operator-(const Matrix &M) const;
        Matrix operator*(double scalar) const;
        Matrix operator*(const Matrix &M) const;
        void operator+=(const Matrix& M);
        void operator-=(const Matrix& M);
        void operator*=(double scalar);
        void operator*=(const Matrix& M);

        void fill_matrix(Matrix_Type type)
        {
            if (m_rows == 0 || m_cols == 0) {
                throw Matrix_Exception("No columns or rows to fill");
            } 

            switch (type) {
                case (Matrix_Type::Zero_Matrix):
                    std::memset(m_data, 0, m_cols * m_rows * sizeof(Matrix_Item));
                    break;
                case (Matrix_Type::Ones_Matrix):
                    std::memset(m_data, 1, m_cols * m_rows * sizeof(Matrix_Item));
                    break;
                case (Matrix_Type::Identity_Matrix):
                    if (m_cols == m_cols) 
                    {
                        for (int i = 0; i < m_rows; i++) 
                        {
                            for (int j = 0; j < m_cols; j++) 
                            {
                                m_data[i][j] = (i == j) ? 1. : 0.;
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
        
        void random()
        {
            srand(static_cast<unsigned>(time(nullptr)));
            for (int i = 0; i < m_rows; ++i) {
                for (int j = 0; j < m_cols; ++j) {
                    m_data[i][j] = rand() % 100;
                }
            }
        }
    };
}; // Matrix

