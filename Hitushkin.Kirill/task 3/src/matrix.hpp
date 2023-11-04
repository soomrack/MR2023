#include <initializer_list>
#include <stddef.h>
#include <vector>
#include <memory>

typedef double MatrixItem;

using namespace std;

struct Matrix
{
    friend ostream& operator<<(ostream& os, const Matrix& A);
    
    friend Matrix operator+(const Matrix& A, const Matrix& B);
    friend Matrix& operator+(Matrix&& A, const Matrix& B);
    friend Matrix& operator+(const Matrix& A, Matrix&& B);
    friend Matrix& operator+(Matrix&& A, Matrix&& B);

    friend Matrix operator-(const Matrix& A, const Matrix& B);
    friend Matrix& operator-(Matrix&& A, const Matrix& B);
    friend Matrix& operator-(const Matrix& A, Matrix&& B);
    friend Matrix& operator-(Matrix&& A, Matrix&& B);

    friend Matrix& matrix_mult_to(Matrix& Save, const Matrix& A, const Matrix& B);
    
private:
    size_t rows;
    size_t cols;
    vector<MatrixItem> items;

public:
    Matrix();
    Matrix(const size_t& a, const size_t& b);
    
    Matrix& operator=(std::initializer_list<MatrixItem> lst);

    Matrix(const Matrix& A);
    Matrix& operator=(const Matrix& A);
    
    Matrix(Matrix&& A);
    Matrix& operator=(Matrix&& A);

    void set_zero();
    void set_one();
    
    MatrixItem& operator()(const size_t& row, const size_t& col);
    const MatrixItem& operator()(const size_t& row, const size_t& col) const;

    const size_t& Rows() const;
    const size_t& Cols() const;

    Matrix& operator+=(const Matrix& A);

    Matrix& operator-=(const Matrix& A);

    Matrix operator*(const Matrix& A) const;
    Matrix& operator*=(const Matrix& A);

    Matrix operator*(const MatrixItem& factor);
    Matrix& operator*=(const MatrixItem& factor);
    
    Matrix T();

    double det() const;

    MatrixItem max() const;

    Matrix expm(const double& accuracy) const;

    bool operator==(const Matrix& A) const;

    ~Matrix();
};
