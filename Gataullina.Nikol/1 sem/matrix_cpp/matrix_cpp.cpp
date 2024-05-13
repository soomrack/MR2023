#include "lib_matrix.h"
#include <iostream>
int main()
{

	double data[9] = {1, 7, 4, 0, 9, 4, 8, 8, 2};
	double data1[9] = {1, 2, 3,4 ,5, 6, 7, 8, 9};

	Matrix A = Matrix(3, 3, data);
	Matrix B = Matrix(3, 3, data1);
	std::cout << "First Matrix\n"
				<< A;
	std::cout << "Second Matrix\n"
			  << B;
	Matrix C = A + B + B;
	std::cout << C;
	try
	{
		std::cout << "Addiction of two matrix\n"
				  << A + B;
		std::cout << "Subtraction of two matrix\n"
				  << A - B;
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
		Matrix A = Matrix(3,3, data1);
	}

	try
	{
		std::cout << "Minor\n"
				  << B.matrix_minor(0, 0);
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
	}
	try
	{
		std::cout << "Multiplication of two matrix\n"
				  << A * B;
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try
	{
		std::cout << "Determinant\n"
				  << A.matrix_determinant(&A) << std::endl;
		std::cout << "Reverse Matrix\n"
				  << A.matrix_reverse(&A) << std::endl;
		std::cout << "Exponent Matrix\n"
				  << A.matrix_exponent();
	}
	catch (Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
}