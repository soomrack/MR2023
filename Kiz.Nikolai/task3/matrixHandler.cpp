#include "matrixHandler.hpp"
#include <cstring>
#include <math.h>
#include <iomanip>

#define DEBUG

namespace MatrixHandler {

Matrix::Matrix(const size_t rows, const size_t cols):
    _rows(rows), _cols(cols) {
    if (rows == 0 || cols == 0)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);

    if ( _rows > SIZE_MAX / sizeof(matrix_element) / _cols) 
        throw MatrixException(MatrixException::OVERFLOW_ERROR);

    _data = new matrix_element[get_size()]{};
}


Matrix::Matrix(size_t rows, size_t cols, const InfillPattern pattern):
Matrix(rows, cols) {
    switch(pattern) {

        case InfillPattern::BLANK: {
            blank_infill();
            break;
        }

        case InfillPattern::RAISING: {
            raising_infill();
            break;
        }

        case InfillPattern::RANDOM: {
            random_infill();
            break;
        }

        case InfillPattern::UNIT: {
            unit_infill();
            break;
        }
        throw MatrixException(MatrixException::BAD_INITIALIZER_ERROR);
    }
}


Matrix::Matrix(const size_t rows, const size_t cols, std::initializer_list<matrix_element> l):
Matrix(rows, cols) {
    if (get_size() != l.size())
        throw MatrixException(MatrixException::BAD_INITIALIZER_ERROR);
        
    std::copy(l.begin(), l.end(), _data); 
}


Matrix::Matrix(const size_t dim): Matrix(dim, dim) {}


Matrix::Matrix(const size_t dim, const InfillPattern pattern): Matrix(dim, dim, pattern) {}


Matrix::Matrix(const size_t dim, std::initializer_list<matrix_element> l): Matrix(dim, dim, l) {}


Matrix::Matrix(const Matrix& copy): Matrix(copy._rows, copy._cols) {
    std::memcpy(_data, copy._data, sizeof(matrix_element)*copy.get_size());    
}


Matrix::Matrix(Matrix&& other_rvalue):
_rows(other_rvalue._rows), _cols(other_rvalue._cols), _data(other_rvalue._data) {
    other_rvalue._data = nullptr;
    other_rvalue._rows = 0;
    other_rvalue._cols = 0;
}


Matrix::~Matrix() {
    delete [] _data;
    #ifdef DEBUG
    std::cout << "[DEBUG] desctructor for object at: " << this << std::endl;
    #endif
}


matrix_element& Matrix::operator()(const size_t row, const size_t col) {
    if (_rows <= row || _cols <= col)
        throw MatrixException(MatrixException::INDEX_ERROR);
    return *(_data + (_cols * row + col));
}


const matrix_element& Matrix::operator()(const size_t row, const size_t col) const {
    if (_rows <= row || _cols <= col)
        throw MatrixException(MatrixException::INDEX_ERROR);
    return *(_data + (_cols * row + col));
}


matrix_element& Matrix::operator[](const size_t idx) const {
    if (idx >= get_size())
        throw MatrixException(MatrixException::INDEX_ERROR);
    return _data[idx];
}


Matrix& Matrix::operator=(Matrix other) {
    this->swap(other);
    return *this;

}


// Matrix& Matrix::operator=(Matrix&& other_rvalue) {
//     Matrix m(std::move(other_rvalue));
//     this->swap(m);
//     return *this;
// }


Matrix& Matrix::operator=(std::initializer_list<matrix_element> l) {
    if (get_size() != l.size()) 
        throw MatrixException(MatrixException::BAD_INITIALIZER_ERROR);
    std::copy(l.begin(), l.end(), this->_data);
    return *this;
}


Matrix Matrix::operator+(const Matrix& second_summand) const{
    if (!_data || !second_summand._data) 
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);
    if (_rows != second_summand._rows || _cols != second_summand._cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);
    Matrix sum(*this);
    for (size_t idx = 0; idx < get_size(); ++idx) {
        sum._data[idx] += second_summand[idx];
    }
    return sum;  
}


Matrix Matrix::operator-(const Matrix& deductible) const {
    if (!_data || !deductible._data) 
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);
    if (_rows != deductible._rows || _cols != deductible._cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);
    Matrix sub(*this);
    for (size_t idx = 0; idx < get_size(); ++idx) {
        sub._data[idx] -= deductible[idx];
    }
    return sub;  
}


Matrix Matrix::operator*(const Matrix& multi) const {
    if (!_data || !multi._data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);
    if (_cols != multi._rows) 
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);
    Matrix result(_rows, multi._cols);
    for (size_t row = 0; row < _rows; ++row) 
        for (size_t col = 0; col < multi._cols; ++col)
            for (size_t dim = 0; dim < _cols; ++dim)
                result(row,col) += (*this)(row,dim) * multi(dim,col);
    return result;
}


Matrix Matrix::operator*(matrix_element scalar) const {
    if (!_data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);
    Matrix result(_rows, _cols);
    for (size_t idx = 0; idx < get_size(); ++idx)
        result[idx] = scalar * (*this)[idx];
    return result;
}


void Matrix::operator*=(matrix_element scalar) {
    if (!_data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);
    for (size_t idx = 0; idx < get_size(); ++idx) 
        (*this)[idx] *= scalar;
}


void Matrix::operator*=(const Matrix& multi) {
    *this = operator*(multi);
}


void Matrix::operator+=(const Matrix& summand) {
    if (!_data || !summand._data) 
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    if (_rows != summand._rows || _cols != summand._cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);

    for (size_t idx = 0; idx < get_size(); ++idx)
        (*this)[idx] += summand[idx];
}


void Matrix::operator-=(const Matrix& deductible) {
    if (!_data || !deductible._data) 
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    if (_rows != deductible._rows || _cols != deductible._cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);
        
    for (size_t idx = 0; idx < get_size(); ++idx)
        (*this)[idx] -= deductible[idx];
}


bool Matrix::operator==(const Matrix& comparison) const {
    if (_data == nullptr || comparison._data == nullptr)
            throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    if (_rows != comparison._rows || _cols != comparison._cols) 
        return false;

    for (size_t idx = 0; idx < get_size(); ++idx) {
        if ((*this)[idx] != comparison[idx]) return false;
    }

    return true;
}


std::ostream& operator<<(std::ostream& stream, const Matrix& output) {
    if (!output._data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    for (size_t row = 0; row < output._rows; row++) {
        stream << "[";
        for (size_t col = 0; col < output._cols; col++) {
            stream << std::setprecision(5);
            stream << std::right << std::setw(10);
            stream << output(row,col);
        }   
        stream << "]\n";
    }
    stream << "\n";
    return stream;
}


matrix_element Matrix::determinant() {
    if (!_data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    if (_rows != _cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);
    
    if (_cols == 1)
        return (_data[0]);
    
    if (_cols == 2)
        return (_data[0] * _data[3] - _data[1] * _data[2]);

    if (_cols == 3)
        return  (_data[0] * _data[4] * _data[8]) + (_data[1] * _data[5] * _data[6]) + 
                (_data[2] * _data[3] * _data[7]) - (_data[2] * _data[4] * _data[6]) - 
                (_data[0] * _data[5] * _data[7]) - (_data[1] * _data[3] * _data[8]); 

    throw MatrixException(MatrixException::DETERMINANT_ERROR);
}


void Matrix::transpose() {
    if (!_data) 
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    Matrix copy(*this);
    std::swap(_rows, _cols);

    for (size_t row = 0; row < _rows; ++row)
        for (size_t col = 0; col < _cols; ++col)
            (*this)(row,col) = copy(col,row);
}


Matrix Matrix::exponent(unsigned int degree) {
    if (!_data)
        throw MatrixException(MatrixException::NULL_MATRIX_ERROR);

    if (_rows != _cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);

    Matrix summand(*this);
    Matrix exponent(_rows, _cols, UNIT);

    if (degree == 0) {
        return exponent;
    }
    if (degree == 1) {
        return exponent + summand;
    }

    exponent += summand;

    for (unsigned int idx = 2; idx < degree; ++idx) {
        summand *= (*this);
        summand *= (1./idx);
        exponent += summand;
    }
    return exponent;
}


void Matrix::random_infill() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<matrix_element> d(FLOAT_MIN, FLOAT_MAX);

    for (size_t idx = 0; idx < get_size(); idx++) {
        this->_data[idx] = d(engine);
    }
}


void Matrix::unit_infill() {
    if (_rows != _cols)
        throw MatrixException(MatrixException::MATH_DOMAIN_ERROR);

    for (size_t idx = 0; idx < get_size(); idx++) 
        this->_data[idx] = idx % (this->_rows + 1) == 0 ? 1 : 0;
}


void Matrix::blank_infill() {
    std::memset(this->_data,  0, get_size());
}


void Matrix::raising_infill() {
    for (size_t idx = 0; idx < this->get_size(); idx++) {
        this->_data[idx] = idx;
    }
}


void Matrix::swap(Matrix& other) {
    std::swap(_data, other._data);
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
}

};  //  namespace Matrix