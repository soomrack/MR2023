#include <iostream>
#include <vector>

class Matrix
{
private:
    std::vector<std::vector<int>> data;
    size_t rows;
    size_t cols;

public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& other);
    Matrix(std::initializer_list<std::initializer_list<int>> list);
    Matrix(Matrix&& other) noexcept;

    Matrix* operator+(const Matrix& other) const;

    Matrix* operator*(const Matrix& other) const;
    Matrix* operator*(int scalar) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    Matrix& operator/=(int scalar);

    void display() const;

    Matrix* transpose() const;

    int determinant() const;
    Matrix exp() const;

private:
    int cofactor(size_t row, size_t col) const;
};
