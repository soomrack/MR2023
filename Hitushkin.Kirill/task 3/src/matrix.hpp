#include <initializer_list>

typedef double MatrixItem;

class Matrix
{        
private:
    size_t rows;
    size_t cols;
    MatrixItem* items;

    MatrixItem* begin();
    MatrixItem* end();
    const MatrixItem* begin() const;
    const MatrixItem* end() const;

    Matrix& mult_to(Matrix& trg, const Matrix& A) const;

    void set_null();

public:
    Matrix();
    Matrix(const size_t a, const size_t b);
    
    Matrix& operator=(std::initializer_list<MatrixItem> lst);

    Matrix(const Matrix& A);
    Matrix& operator=(const Matrix& A);
    
    Matrix(Matrix&& A);
    Matrix& operator=(Matrix&& A);

    void set_zero();
    void set_one();
    
    MatrixItem& operator[](const size_t row, const size_t col);
    const MatrixItem& operator[](const size_t row, const size_t col) const;

    size_t get_rows() const;
    size_t get_cols() const;

    Matrix& operator+=(const Matrix& A);
    Matrix& operator-=(const Matrix& A);

    Matrix operator*(const Matrix& A) const;
    Matrix& operator*=(const Matrix& A);

    Matrix operator*(const MatrixItem& factor);
    Matrix& operator*=(const MatrixItem& factor);
    
    Matrix T();

    double det() const;

    Matrix expm(const double& accuracy) const;

    bool operator==(const Matrix& A) const;

    MatrixItem max();

    ~Matrix();
};

Matrix operator+(const Matrix& A, const Matrix& B);
Matrix operator+(const Matrix& A, Matrix&& B);

Matrix operator-(const Matrix& A, const Matrix& B);
Matrix operator-(const Matrix& A, Matrix&& B);

std::ostream& operator<<(std::ostream& os, const Matrix& A);
