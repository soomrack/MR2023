#include "matrixHandler.hpp"
#include <cstring>
#include <math.h>



/*
TODO:
Custom Exceptions
Operators Overload
Exponent
*/


Matrix::Matrix() {
    this->_rows = 0;
    this->_cols = 0;
    this->_data = nullptr;
}  // default constructor


Matrix::Matrix(const size_t rows, const size_t cols) :
    _rows(rows), _cols(cols), _size(_rows * _cols), _data(new matrix_element[_size])
{

}  //  regular constructor


Matrix::Matrix(size_t rows, size_t cols, const InfillPattern pattern) :
    Matrix(rows, cols)

{
    switch(pattern) {

        case InfillPattern::BLANK: {
            this->blank_infill();
            break;
        }

        case InfillPattern::RAISING: {
            this->raising_infill();
            break;
        }

        case InfillPattern::RANDOM: {
            this->random_infill();
            break;
        }

        case InfillPattern::UNIT: {
            this->unit_infill();
            break;
        }

        case InfillPattern::NULL_MATRIX: {
            this->_data = nullptr;
            break;
        }
    }

}


Matrix::Matrix(const size_t rows, const size_t cols, const matrix_element * data) :
    Matrix(rows, cols)
{
    std::memcpy(this->_data, data, this->_size * sizeof(matrix_element));
}



Matrix::Matrix(const size_t dim) : 
    Matrix(dim, dim)
{

}


Matrix::Matrix(const size_t dim, const InfillPattern pattern) :
    Matrix(dim, dim, pattern)
{

}


Matrix::Matrix(const size_t dim, const matrix_element * data) :
    Matrix(dim, dim, data)
{

}


Matrix::Matrix(const Matrix & copy) :
    Matrix(copy._rows, copy._cols, copy._data)
{

}


Matrix::~Matrix() {
    if (nullptr != this->_data) {
        delete [] this->_data;
    }
    #ifdef DEBUG
    std::cout << "[DEBUG] desctructor for object at: " << this << std::endl;
    #endif
}


void Matrix::random_infill() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<matrix_element>
    distribution(FLOAT_MIN, FLOAT_MAX);
    for (size_t idx = 0; idx < _size; idx++) {
        this->_data[idx] = distribution(engine);
    }
}


void Matrix::unit_infill() {
    // TODO: exception for non-squared matrix
    for (size_t idx = 0; idx < _size; idx++) {
        this->_data[idx] = idx % (this->_rows + 1) == 0 ? 1 : 0;
    }
}


void Matrix::blank_infill() {
    std::memset(this->_data,  0, this->_size);
}


void Matrix::raising_infill() {
    for (size_t idx = 0; idx < this->_size; idx++) {
        this->_data[idx] = idx;
    }
}


matrix_element & Matrix::operator () (const size_t row, const size_t col) {
    // TODO: exception for bad indexing
    return *(this->_data + (this->_cols * row + col));
}


void Matrix::print() {
    // TODO: exception for null-matrix

    for (size_t row = 0; row < this->_rows; row++) {
        std::cout << "[";
        for (size_t col = 0; col < this->_cols; col++) {
            std::cout << std::setprecision(3);
            if (col == this->_cols - 1) {
                std::cout << this->_data[this->_cols * row + col];
            }
            else std::cout << this->_data[this->_cols * row + col] << ", ";
        }
        std::cout << "]\n";
    }

}
