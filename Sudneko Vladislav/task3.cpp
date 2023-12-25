/*
Final Version
- Deleted all this->
- All multi-line functions are taken outside the class
- Correctly calculated the exponent
- main() moved to the end
- all returned Matrix objects are created via new
- added missing shape checks for some methods
*/

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
    double get_cell(size_t row, size_t column);
    void set_cell(size_t row, size_t column, double val);
    size_t get_rows() {
        return rows;
    }
    size_t get_columns() {
        return columns;
    }
        


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
    double det() const;
    Matrix exp() const;

    // 8. Outputting the matrix to the console
    void print();

    // 9. Destructor
    ~Matrix() {
        columns = 0;
        rows = 0;
        delete[] cells;
    }
};

class MatrixException : public exception {
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
MatrixException ARRAY_SIZE_ERROR("\nError: array size is not equal to matrix size");

void Matrix::print() {
    cout << endl;
    for (size_t row = 0; row < rows; row++) {
        for (size_t column = 0; column < columns; column++) {
            cout << cells[column + row * columns] << " ";
        }
        if (row != rows - 1) cout << endl;
    }
    cout << endl << endl;
}

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
    fill_with_value(0.0);
    for (size_t cell = 0; cell < rows * columns; cell += columns + 1) {
        cells[cell] = 1.0;
    }
    return *this;
}

Matrix Matrix::fill_from_array(double* array) {
    if (rows * columns != sizeof(array) / sizeof(double)) {
        throw ARRAY_SIZE_ERROR;
    }
    memcpy(cells, array, rows * columns * sizeof(double));
    return *this;
}

// 3. Change Matrix Cell

double Matrix::get_cell(size_t row, size_t column) {
    if (row > rows || column > columns) throw INDEX_ERROR;
    return cells[column + row * columns];
}

void Matrix::set_cell(size_t row, size_t column, double value) {
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
    if (cells == nullptr) throw MEMORY_ERROR;
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
    if (columns != other_matrix.columns ||
        rows != other_matrix.rows)
        return false;

    for (size_t cell = 0; cell < columns * rows; cell++) {
        if (abs(cells[cell] - other_matrix.cells[cell]) > PRECISION)
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
    if (rows != other_matrix.rows || columns != other_matrix.columns)
        throw SIZE_ERROR;

    Matrix* result = new Matrix(rows, columns);
    for (size_t cell = 0; cell < rows * columns; cell++) {
        result->cells[cell] = cells[cell] + other_matrix.cells[cell];
    }

    return *result;
}

Matrix Matrix::operator-(const Matrix& other_matrix) const {
    if (rows != other_matrix.rows || columns != other_matrix.columns)
        throw SIZE_ERROR;

    Matrix* result = new Matrix(rows, columns);
    for (size_t cell = 0; cell < rows * columns; cell++) {
        result->cells[cell] = cells[cell] - other_matrix.cells[cell];
    }

    return *result;
}

Matrix Matrix::operator*(const double value) const {
    Matrix* result = new Matrix(*this);

    for (size_t cell = 0; cell < rows * columns; cell++)
        result->cells[cell] *= value;

    return *result;
}

Matrix Matrix::operator/(const double value) const {
    Matrix* result = new Matrix(*this);

    for (size_t cell = 0; cell < rows * columns; cell++)
        result->cells[cell] /= value;

    return *result;
}


Matrix Matrix::operator*(const Matrix& other_matrix) const {
    if (columns != other_matrix.rows) throw SHAPE_ERROR;

    Matrix* result = new Matrix(rows, other_matrix.columns);

    for (size_t row = 0; row < result->rows; row++) {
        for (size_t column = 0; column < result->columns; column++) {
            double final_cell_value = 0.0;
            for (size_t cell = 0; cell < columns; cell++) {
                final_cell_value +=
                    cells[row * columns + cell] *
                    other_matrix.cells[cell * other_matrix.columns + column];
            }
            result->cells[result->columns * row + column] = final_cell_value;
        }
    }

    return *result;
}


// 7. Linear algebra matrix operations

Matrix Matrix::T() const {
    Matrix* result = new Matrix(columns, rows);
    for (size_t row = 0; row < result->rows; row++) {
        for (size_t column = 0; column < result->columns; column++) {
            result->cells[row * result->columns + column] =
                cells[column * result->rows + row];
        }
    }

    return *result;
}


double Matrix::det() const {
    if (rows != columns) throw SQUARE_ERROR;

    Matrix* triangular_matrix = new Matrix(rows, columns);
    *triangular_matrix = *this;

    for (size_t current_row = 0; current_row < rows; current_row++) {
        for (size_t next_row = current_row + 1; next_row < rows; next_row++) {
            if (triangular_matrix
                ->cells[current_row * columns + current_row] == 0) {
                triangular_matrix
                    ->cells[current_row * columns + current_row] = 1.0e-18;
            }

            double current_row_scaler =
                triangular_matrix
                ->cells[next_row * columns + current_row] /
                triangular_matrix
                ->cells[current_row * columns + current_row];

            for (size_t column = 0; column < rows; column++) {
                triangular_matrix->cells[next_row * columns + column] =
                    triangular_matrix->cells[next_row * columns + column] -
                    current_row_scaler *
                    triangular_matrix
                    ->cells[current_row * columns + column];
            }
        }
    }

    double det = 1.0;
    for (size_t row = 0; row < rows; row++) {
        det *= triangular_matrix->cells[row * columns + row];
    }

    delete triangular_matrix;
    return det;
}


Matrix Matrix::exp() const {
    if (rows != columns) throw SQUARE_ERROR;

    // Fix thirst element
    Matrix *result = new Matrix(rows, columns);
    result->fill_identity();

    size_t number_of_terms_in_exponential_expansion = 50;
    Matrix current_element = Matrix(rows, columns).fill_identity();
    result->fill_identity();
    for (size_t term = 1; term < number_of_terms_in_exponential_expansion;
        term++) {
        current_element = (current_element * *this) / (double)term;
        *result += current_element;
    }
    return *result;
}

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