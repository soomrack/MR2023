#pragma once 

#include <cstring>
#include <cmath>
#include <iostream>
#include <random>
#include <iomanip>

template <typename Matrix_Item>
class Matrix : public std::exception
{
    static Matrix &me() {
		static Matrix d;
		return d;
	}
    std::string exception;
private:
    size_t m_rows{0};
    size_t m_cols{0};
    Matrix_Item *m_data{nullptr};
public:
    Matrix();
    ~Matrix();
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    Matrix_Item &operator()(int rows, int cols) { return m_data[rows][cols]}
    Matrix &operator=(const Matrix &M);
    Matrix &operator=(Matrix &&M) noexcept;
    Matrix operator+(const Matrix &M) const;
    Matrix operator-(const Matrix &M) const;
    Matrix operator*(double scalar) const;
    Matrix operator*(const Matrix &M) const;
    void operator+=(const Matrix& M);
    void operator-=(const Matrix& M);
    void operator*=(double scalar);
    void operator*=(const Matrix& M);
protected:
    const char *what() const noexcept override { return exception.c_str(); }
};
