#include <iostream>
#include <string>
#include <string.h>
#include <cstdint>
#include <cmath>

typedef double MatrixItem;

// Обработка исключений
class MyException : public std::exception {
private:
	std::string message;
public:
	MyException(std::string message) :message{ message } {}
};

MyException INIT_ER("Матрица не инициализированна");
MyException WRONG_COND("Неверные условия для создания матрицы"); 
MyException SQUARE_ER("матрица должна быть квадратной");
MyException DET_ER("Ошибка! rows должно быть <= 3");
MyException COND_ER("Неверные условия для выполнения операции");

class Matrix {
private:
	size_t rows;
	size_t cols;
	MatrixItem* data;

public:
	Matrix();
	Matrix(const size_t rows, const size_t cols);
	Matrix(const size_t rows, const size_t cols, const MatrixItem* value);
	Matrix(const Matrix& N);
	Matrix(Matrix&& N);
	~Matrix();

public:
	void print_matrix();
	void transp_matrix();
	void unit_matrix();
	MatrixItem determinant_matrix();
	Matrix exp(const size_t terms);

public:
	Matrix& operator=(const Matrix& M);
	Matrix& operator=(Matrix&& M);
	Matrix& operator+=(const Matrix& M);
	Matrix& operator+(const Matrix& M);
	Matrix& operator-=(const Matrix& M);
	Matrix& operator-(const Matrix& M);
	Matrix& operator*= (const Matrix& M);
	Matrix& operator* (const Matrix& M);
	Matrix& operator*= (const double scalar);
	Matrix& operator* (const double scalar);
};


// Конструкторы
Matrix::Matrix() {
	rows = 0;
	cols = 0;
	data = nullptr;
}

Matrix::Matrix(const size_t rows, const size_t cols) {
	if (rows == 0 || cols == 0)
		throw INIT_ER;
	
	if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols)
		throw INIT_ER;

	this->rows = rows;
	this->cols = cols;
	data = new MatrixItem[cols * rows];
}

Matrix::Matrix(const size_t rows, const size_t cols, const MatrixItem* value) {
	if (data == nullptr)
		throw INIT_ER;

	this->cols = cols;
	this->rows = rows;
	this->data = nullptr;
	data = new MatrixItem[cols * rows];
	for (size_t i=0; i < (cols * rows); i++)
		data[i] = value[i];             
}

Matrix::Matrix(const Matrix& N) {
	cols = N.cols;
	rows = N.rows;
	data = new MatrixItem[cols * rows]; 
	for (size_t i = 0; i < (cols * rows); i++)
		data[i] = N.data[i];
}

Matrix::Matrix(Matrix&& N){
	rows = N.rows;
	cols = N.cols;
	data = N.data;

	N.rows = 0;
	N.cols = 0;
	N.data = nullptr;
}

Matrix::~Matrix() {
	rows = 0;
	cols = 0;
	delete[] data;
	data = nullptr;
}


// Методы
void Matrix::print_matrix() {
	if (data == nullptr || rows == 0 || cols == 0)
		throw WRONG_COND;

	for (size_t i = 0; i < rows; i++) {
		std::cout << "[";
		for (size_t j = 0; j < cols; j++) {
			std::cout << data[i * cols + j];
			if (j != cols - 1)
				std::cout << "  ";
		}
		std::cout << "]\n";
	}
	std::cout << std::endl;
}
	
	

void Matrix::transp_matrix() {
	Matrix result(cols, rows);
	for (size_t i = 0; i < result.rows; i++) {
		for (size_t j = 0; j < result.cols; j++)
			result.data[i * result.cols + j] = data[j * result.rows + i];
	}
	*this=result;
}

void Matrix::unit_matrix() {
	if (data == nullptr)
		throw INIT_ER;
	else if (rows != cols)
		throw SQUARE_ER;

	Matrix result(cols, rows);
	for (size_t i = 0; i < result.rows; i++) {
		for (size_t j = 0; j < result.cols; j++) {
			if (i == j)
				result.data[i * result.cols + j] = 1.0;
			else
				result.data[i * result.cols + j] = 0.0;
		}
	}
	*this = result;
}

MatrixItem Matrix::determinant_matrix() {
	if (rows != cols)
		throw SQUARE_ER;

	if (rows == 1)
		return data[0];

	if (rows == 2)
		return (data[0] * data[3] - data[1] * data[2]);

	if (rows == 3) {
		return data[0] * data[4] * data[8] + \
			data[1] * data[5] * data[6] + \
			data[2] * data[3] * data[7] - \
			data[2] * data[4] * data[6] - \
			data[0] * data[5] * data[7] - \
			data[1] * data[3] * data[8];
	}
	throw DET_ER;
	return NAN;
}

Matrix Matrix::exp(const size_t terms) {
	if (data == nullptr)
		throw INIT_ER;
	else if (rows != cols)
		throw SQUARE_ER;

	Matrix* exp = new Matrix(rows, cols);
	exp->unit_matrix();
	*exp += *this;
	Matrix* term = new Matrix(*this);

	for (int i = 2; i <= terms; ++i) {
		*term *= (*this) * (1.0 / i);
		*exp += *term;
	};
	return *exp;
}

// Перегрузка операторов
Matrix& Matrix::operator= (const Matrix& M) {
	if (this == &M) 
		return *this;
	delete[] data;

	rows = M.rows;
	cols = M.cols;

	data = new MatrixItem[rows * cols];
	memcpy(data, M.data, cols * rows * sizeof(MatrixItem));

	return *this;
}

Matrix& Matrix::operator= (Matrix&& M) {
	if (this == &M) 
		return *this;
	delete[] data;

	rows = M.rows;
	cols = M.cols;
	data = M.data;

	M.cols = 0;
	M.rows = 0;
	M.data = nullptr;

	return *this;
}

Matrix& Matrix::operator+= (const Matrix& M) {
	if ((rows != M.rows) || (cols != M.cols))
		throw COND_ER;

	for (size_t i = 0; i < rows * cols; i++) {
		data[i] += M.data[i];
	}
	return *this;
}

Matrix& Matrix::operator+(const Matrix& M) {
	Matrix* sum = new Matrix(M.cols, M.rows);
	*sum = *this;
	*sum += M;
	return *sum;
}

Matrix& Matrix::operator-= (const Matrix& M) {
	if ((rows != M.rows) || (cols != M.cols))
		throw COND_ER;

	for (size_t i = 0; i < rows * cols; i++) {
		data[i] -= M.data[i];
	}
	return *this;
}

Matrix& Matrix::operator-(const Matrix& M) {
	Matrix* diff = new Matrix(M.cols, M.rows);
	*diff = *this;
	*diff -= M;
	return *diff;
}

Matrix& Matrix::operator*= (const Matrix& M) {
	if (cols != M.rows)
		throw COND_ER;

	Matrix R(rows, M.cols);
	for (size_t row = 0; row < R.rows; row++) {
		for (size_t col = 0; col < R.cols; col++) {
			for (size_t idx = 0; idx < M.rows; idx++)
				R.data[row * R.cols + col] += data[row * cols + idx] * M.data[idx * M.cols + col];
		}
	}
	cols = R.cols;
	rows = R.rows;
	delete[] data;
	data = R.data;
	R.data = nullptr;
	return *this;
}

Matrix& Matrix::operator*(const Matrix& M) {
	Matrix* rez = new Matrix(M.cols, M.rows);
	*rez = *this;
	*rez *= M;
	return *rez;
}

Matrix& Matrix::operator*= (const double scalar) {
	if (data == nullptr) 
		throw COND_ER;

	for (size_t i = 0; i < rows * cols; i++) {
		data[i] *= scalar;
	}
	return *this;
}

Matrix& Matrix::operator*(const double scalar) {
	Matrix* rez = new Matrix(cols, rows);
	*rez = *this;
	*rez *= scalar;
	return *rez;
}


int main() {
	setlocale(LC_ALL, "RU");

	Matrix A, B, C, E, N;
	double det;

	try
	{
		double arr[9] = {3, 4, 5, 6, 9, 8, 0, 1, 5};
		double arr2[9] = {1, 4, 6, 8, 0, 2, 5, 7, 9};
		double arr3[9] = {1, 5, 8, 3, 5, 7, 9, 3, 2};

		A = Matrix(3, 3, arr);
		B = Matrix(3, 3, arr2);
		C = Matrix(3, 3, arr3);

		std::cout << "Матрица А:" << std::endl;
		A.print_matrix();
		std::cout << "Матрица B:" << std::endl;
		B.print_matrix();
		std::cout << "Матрица C:" << std::endl;
		B.print_matrix();

		C = A + B;
		std::cout << "C=A+B:" << std::endl;
		C.print_matrix();

		A *= B;
		std::cout << "A*=B:" << std::endl;
		A.print_matrix();

		det = B.determinant_matrix();
		std::cout << "Определитель матрицы B:" << std::endl;
		printf("%.3f\n", det);
		std::cout << std::endl;

		A = A.exp(3);
		std::cout << "Экспонента матрицы А:" << std::endl;
		A.print_matrix();

		C.transp_matrix();
		std::cout << "Транспонированная C:" << std::endl;
		C.print_matrix();

		N.unit_matrix();
		std::cout << "Единичная матрица N:" << std::endl;
		N.print_matrix();
	}
	catch (MyException err)
	{
		std::cerr << err.what() << std::endl; // сервисный поток
	}
}
