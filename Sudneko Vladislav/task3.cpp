#include <cstdlib>
#include <iostream>

const double PRECISION = 10e-8;  // computation precision
using namespace std;

class Matrix {
private:
    size_t rows;
    size_t columns;
    double* cells;

public:
    // 1. Class constructors
    Matrix();
    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& other_matrix);
    Matrix(Matrix&& other_matrix) noexcept;

    // 2. Matrix Filling Functions
    Matrix fill_with_value(double value);
    Matrix fill_random(size_t min_value, size_t max_value);
    Matrix fill_identity();
    Matrix fill_from_array(double* array);

    // 3. Change Matrix Cell
    double get(size_t row, size_t column);
    void set(size_t row, size_t column, double val);


    // 4. Assignment Operators
    Matrix& operator=(const Matrix& other_matrix);
    Matrix& operator=(Matrix&& other_matrix) noexcept;

    // 5. Comparison Operators
    bool operator==(const Matrix& other_matrix);
    bool operator!=(const Matrix& other_matrix);

    // 6. Matrix arithmetic operators
    double* operator[](size_t row);
    Matrix operator+(const Matrix& other_matrix) const;
    Matrix operator-(const Matrix& other_matrix) const;
    Matrix operator*(const Matrix& other_matrix) const;
    Matrix operator*(double value) const;
    Matrix operator/(double value) const;
    void operator+=(const Matrix& other_matrix) {
        *this = *this + other_matrix;
    }
    void operator-=(const Matrix& other_matrix) {
        *this = *this - other_matrix;
    }
    void operator*=(const Matrix& other_matrix) {
        *this = *this * other_matrix;
    }

    // 7. Linear algebra matrix operations
    Matrix T() const;
    void swap_rows(size_t row1, size_t row2) const;
    size_t upper_triangle() const;
    double det() const;
    double trace() const;
    Matrix exp() const;

    // 8. Outputting the matrix to the console
    void print() {
        cout << endl;
        for (size_t row = 0; row < this->rows; row++) {
            for (size_t column = 0; column < this->columns; column++) {
                cout << this->cells[column + row * this->columns] << " ";
            }
            if (row != this->rows - 1) cout << endl;
        }
        cout << endl << endl;
    }

    // 9. Destructor
    ~Matrix() {
        columns = 0;
        rows = 0;
        delete[] this->cells;
    }
};

class MatrixException : public std::exception {
public:
    MatrixException(const char* const& msg) : exception(msg) {}
};

MatrixException SQUARE_ERROR("\nMatrix must be square!\n\n");
MatrixException SIZE_ERROR("\nError: matrices should have the same size\n\n");
MatrixException SHAPE_ERROR(
    "\nError: first matrix columns not equal to second matrix row.\n\n");
MatrixException MEMORY_ERROR("\nError: memory are not allocated\n\n");
MatrixException INDEX_ERROR(
    "\nError: one of the indexes is bigger than matrix size\n\n");

void function_testing() {
    // Create
    Matrix A = Matrix(3, 3);
    Matrix B = Matrix(3, 3);
    Matrix C = Matrix(3, 3);
    double det = 0.0;

    // Fill
    A.fill_random(1, 10);
    B.fill_random(1, 10);
    C.fill_with_value(0);

    // Show
    cout << "Matrix A:" << endl;
    A.print();
    cout << "Matrix B:" << endl;
    B.print();
    cout << "Matrix C:" << endl;
    C.print();

    // Operations

    cout << "Operations" << endl;

    C = A + B;
    cout << "SUM:" << endl;
    C.print();

    C = A - B;
    cout << "DIFFERENCE:" << endl;
    C.print();

    C = A * B;
    cout << "PRODUCT:" << endl;
    C.print();

    C = A.T();
    cout << "TRANSPOSITION OF MATRIX A:" << endl;
    C.print();

    det = A.det();
    cout << "DETERMINANT OF MATRIX A:" << endl;
    cout << det << endl << endl;

    C = A.exp();
    cout << "EXPONENT OF MATRIX A:" << endl;
    C.print();
}

int main() {
    srand(3);
    function_testing();

    return 0;
};

// 1. Class constructors

Matrix::Matrix() : rows(0), columns(0), cells(nullptr) {}

Matrix::Matrix(size_t r_num, size_t c_num) {
    rows = r_num;
    columns = c_num;
    cells = new double[rows * columns];
    if (!cells) throw MEMORY_ERROR;
}

Matrix::Matrix(const Matrix& other_matrix) {
    rows = other_matrix.rows;
    columns = other_matrix.columns;
    cells = new double[rows * columns];
    if (!cells) throw MEMORY_ERROR;
    memcpy(cells, other_matrix.cells, sizeof(double) * rows * columns);
}

Matrix::Matrix(Matrix&& other_matrix) noexcept {
    rows = other_matrix.rows;
    columns = other_matrix.columns;
    cells = other_matrix.cells;
    other_matrix.cells = nullptr;
    other_matrix.rows = 0;
    other_matrix.columns = 0;
}

// 2. Matrix Filling Functions

Matrix Matrix::fill_with_value(double value) {
    for (size_t cell = 0; cell < rows * columns; cell++) cells[cell] = value;
    return *this;
}

Matrix Matrix::fill_random(size_t min_value, size_t max_value) {
    for (size_t cell = 0; cell < rows * columns; cell++) {
        cells[cell] = min_value + rand() % (max_value - min_value + 1);
    }
    return *this;
}

Matrix Matrix::fill_identity() {
    if (rows != columns) throw SQUARE_ERROR;
    this->fill_with_value(0.0);
    for (size_t cell = 0; cell < rows * columns; cell += columns + 1) {
        this->cells[cell] = 1.0;
    }
    return *this;
}

Matrix Matrix::fill_from_array(double* array) {
    memcpy(cells, array, rows * columns * sizeof(double));
    return *this;
}

// 3. Change Matrix Cell

double Matrix::get(size_t row, size_t column) {
    if (row > rows || column > columns) throw INDEX_ERROR;
    return cells[column + row * columns];
}

void Matrix::set(size_t row, size_t column, double value) {
    if (row > rows || column > columns) throw INDEX_ERROR;
    cells[column + row * columns] = value;
}

// 4. Assignment Operators

Matrix& Matrix::operator=(const Matrix& other_matrix) {
    if (this == &other_matrix) return *this;
    delete[] cells;
    rows = other_matrix.rows;
    columns = other_matrix.columns;
    cells = new double[rows * columns];
    memcpy(cells, other_matrix.cells, rows * columns * sizeof(double));
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other_matrix) noexcept {
    if (this == &other_matrix) return *this;
    delete[] cells;
    rows = other_matrix.rows;
    columns = other_matrix.columns;
    cells = other_matrix.cells;
    other_matrix.rows = 0;
    other_matrix.columns = 0;
    other_matrix.cells = nullptr;
    return *this;
}

// 5. Comparison Operators

bool Matrix::operator==(const Matrix& other_matrix) {
    if (this->columns != other_matrix.columns ||
        this->rows != other_matrix.rows)
        return false;

    for (size_t cell = 0; cell < this->columns * this->rows; cell++) {
        if (abs(this->cells[cell] - other_matrix.cells[cell]) > PRECISION)
            return false;
    }

    return true;
}

bool Matrix::operator!=(const Matrix& other_matrix) {
    return !(*this == other_matrix);
}

// 6. Matrix arithmetic operators

double* Matrix::operator[](size_t cell) {
    if (cell > rows) return nullptr;
    return cells + cell * columns;
}

Matrix Matrix::operator+(const Matrix& other_matrix) const {
    if (this->rows != other_matrix.rows ||
        this->columns != other_matrix.columns)
        throw SIZE_ERROR;

    Matrix result = { rows, columns };
    for (size_t cell = 0; cell < rows * columns; cell++) {
        result.cells[cell] = this->cells[cell] + other_matrix.cells[cell];
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& other_matrix) const {
    if (this->rows != other_matrix.rows ||
        this->columns != other_matrix.columns)
        throw SIZE_ERROR;

    Matrix result = { rows, columns };
    for (size_t cell = 0; cell < rows * columns; cell++) {
        result.cells[cell] = this->cells[cell] - other_matrix.cells[cell];
    }

    return result;
}

Matrix Matrix::operator*(const double value) const {
    Matrix result = *this;

    for (size_t cell = 0; cell < rows * columns; cell++)
        result.cells[cell] *= value;

    return result;
}

Matrix Matrix::operator/(const double value) const {
    Matrix result = *this;

    for (size_t cell = 0; cell < rows * columns; cell++)
        result.cells[cell] /= value;

    return result;
}

Matrix Matrix::operator*(const Matrix& other_matrix) const {
    if (this->columns != other_matrix.rows) throw SHAPE_ERROR;

    Matrix result = { this->rows, this->columns };

    for (size_t row = 0; row < result.rows; row++) {
        for (size_t column = 0; column < result.columns; column++) {
            double final_cell_value = 0.0;
            for (size_t cell = 0; cell < this->columns; cell++) {
                final_cell_value +=
                    this->cells[row * this->columns + cell] *
                    other_matrix.cells[cell * other_matrix.columns + column];
            }
            result.cells[result.columns * row + column] = final_cell_value;
        }
    }

    return result;
}

// 7. Linear algebra matrix operations

Matrix Matrix::T() const {
    Matrix result = { this->columns, this->rows };
    for (size_t row = 0; row < result.rows; row++) {
        for (size_t column = 0; column < result.columns; column++) {
            result.cells[row * result.columns + column] =
                this->cells[column * result.rows + row];
        }
    }

    return result;
}

double Matrix::det() const {
    if (rows != columns) throw SQUARE_ERROR;

    Matrix triangular_matrix = { this->rows, this->columns };
    triangular_matrix = *this;

    for (size_t current_row = 0; current_row < this->rows; current_row++) {
        for (size_t next_row = current_row + 1; next_row < this->rows;
            next_row++) {
            if (triangular_matrix
                .cells[current_row * this->columns + current_row] == 0) {
                triangular_matrix
                    .cells[current_row * this->columns + current_row] = 1.0e-18;
            }

            double current_row_scaler =
                triangular_matrix
                .cells[next_row * this->columns + current_row] /
                triangular_matrix
                .cells[current_row * this->columns + current_row];

            for (size_t column = 0; column < this->rows; column++) {
                triangular_matrix.cells[next_row * this->columns + column] =
                    triangular_matrix.cells[next_row * this->columns + column] -
                    current_row_scaler *
                    triangular_matrix
                    .cells[current_row * this->columns + column];
            }
        }
    }

    double det = 1.0;
    for (size_t row = 0; row < this->rows; row++) {
        det *= triangular_matrix.cells[row * this->columns + row];
    }

    return det;
}

Matrix Matrix::exp() const {
    if (rows != columns) throw SQUARE_ERROR;

    Matrix result = *this;

    size_t number_of_terms_in_exponential_expansion = 50;
    Matrix current_element = Matrix(this->rows, this->columns).fill_identity();
    result.fill_identity();
    for (size_t term = 1; term < number_of_terms_in_exponential_expansion;
        term++) {
        current_element = (current_element * *this) / (double)term;
        result += current_element;
    }
    return result;
}