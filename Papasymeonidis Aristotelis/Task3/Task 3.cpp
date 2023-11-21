#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include<iostream>
#include<vector>
#include<string>



typedef double MatrixItem;

class MatrixException : public std::exception {
private:
    const char* message;

public:
    MatrixException(std::string msg) : message(msg.c_str()) {}
    const char* what () { return message; }
};

MatrixException ERRONEOUS_MESSAGE("erroneous message");
MatrixException WRONG_CONDITIONS("wrong_conditions");
MatrixException NO_MEMORY_ALLOCATED("no_memory_allocated");


class Matrix_Calculator
{
    private:
        size_t cols;
        size_t rows;
        MatrixItem* data;

        void matrix_error_message() 
        {
            std::cout << "Error! Check your actions!" << std::endl;
        }

        Matrix_Calculator matrix_init(const size_t rows, const size_t cols) //p
        {
            if (rows == 0 || cols == 0) {
            throw"The matrix is not initialized";
            }
            // rows * cols < MAX_SIZE / sizeof(MatrixItem)
            if (rows >= SIZE_MAX / sizeof(MatrixItem) / cols) throw"The matrix is not initialized";  

            Matrix_Calculator A = { cols, rows, nullptr};
            A.data = new double[A.cols * A.rows * sizeof(double)];

            if (A.data == nullptr) {
                throw"The matrix is not initialized";
                matrix_error_message();
            }

            return A;
        }

        Matrix_Calculator sum_for_e(const size_t deg_acc, const Matrix_Calculator& A) //p
        {
        // matrix_print(A);
        Matrix_Calculator E = matrix_init(A.rows, A.cols);

        if (E.data == nullptr) {
        throw"Initialisation error";
        }

        if (deg_acc == 1) {
            Matrix_Calculator E = matrix_make_ident(A.cols, A.rows);
            return E;
        }

        if (deg_acc == 2) {
            return A;
        }   

        if (deg_acc > 2) {
            E = matrix_clone(A); // цикл for для ( функция копиии матрицчы) 
            for (size_t id = 2; id < deg_acc; ++id) {
                Matrix_Calculator buf = E;
                E = buf.matrix_mult(A);
                for (size_t idx = 0; idx < E.rows * E.cols; ++idx) {
                E.data[idx] /= (id);
            }
            // matrix_print(E);
            //matrix_free(&buf);
            }
        }
        return E;
        }



    
    public:

        Matrix_Calculator();
        Matrix_Calculator(size_t cols, size_t rows, MatrixItem* data);
        ~Matrix_Calculator();

        void matrix_create(const size_t rows, const size_t cols, const double* values) //public
        {
        Matrix_Calculator A = matrix_init(rows, cols);
        if (data == nullptr) Matrix_Calculator();
        memcpy(A.data, values, rows * cols * sizeof(double));
        }

        Matrix_Calculator matrix_make_ident(size_t rows, size_t cols) //public
        {
        Matrix_Calculator I = matrix_init(rows, cols);
        if (I.data == nullptr) {
            throw"The matrix is not initialized";
        }
        for (size_t idx = 0; idx < rows * cols; idx++) {
            if (idx % (rows + 1) == 0) {
                I.data[idx] = 1.;
            }
            else {
                I.data[idx] = 0;
            }
        }
        return I;
        }

        Matrix_Calculator matrix_sum(const Matrix_Calculator& A, const Matrix_Calculator& B) //public
        {
        if (A.cols != B.cols || A.rows != B.rows) throw"The matrices do not match in size";
        Matrix_Calculator C = matrix_init(A.cols, A.rows);
        for (size_t idx = 0; idx < C.cols * C.rows; ++idx) {
            C.data[idx] = A.data[idx] + B.data[idx];
        }
        return C;
        }

        void matrix_print(){
            if(data != nullptr || cols != 0 || rows != 0){
            for(size_t row = 0; row < rows; ++row) {
            printf("[ ");
            for(size_t col = 0; col < cols; ++col) {
            printf("%4.2f ", data[cols * row + col]);
            }
            printf("]\n");
            }
            printf("\n");
            } else{
            matrix_error_message();
            }
        }

        void matrix_add(const Matrix_Calculator& B) //public
        {
            if (cols != B.cols || rows != B.rows) throw"The matrices do not match in size";
            for (size_t idx = 0; idx < cols * rows; ++idx) {
                data[idx] += B.data[idx];
            }
        }

        Matrix_Calculator matrix_clone(const Matrix_Calculator& A){
        Matrix_Calculator C = matrix_init(A.cols, A.rows);
        for(size_t idx = 0; idx < A.cols * A.rows; ++idx){
            C.data[idx] = A.data[idx];
        }
            return C;
        }

        Matrix_Calculator matrix_mult(const Matrix_Calculator& A) //public
        {
            if (A.cols != rows) throw"Size mismatch for multiplication";
            Matrix_Calculator C = matrix_init(A.cols, rows);

            if (C.data == nullptr) {
                throw"The matrix is not initialized";
            }

            for (size_t rowA = 0; rowA < A.rows; ++rowA) {
            for (size_t colsB = 0; colsB < cols; ++colsB) {
                C.data[rowA * (A.cols) + colsB] = 0;
                for (size_t idx = 0; idx < A.cols; ++idx) {
                    C.data[rowA * (A.cols) + colsB] += (A.data[(rowA * A.cols) + idx]) * (data[(idx * cols) + colsB]);
                }
            }
        }

        return C;
        }

        Matrix_Calculator matrix_transp()
        {
            Matrix_Calculator C = matrix_init(rows, cols);

            if (C.data == nullptr) {
                throw"Initialization error";
            }

            for (size_t rowA = 0; rowA < rows; ++rowA) {
                for (size_t colsA = 0; colsA < cols; ++colsA) {
                    C.data[(rows) * colsA + rowA] = data[colsA + rowA * cols];
                }
            }
            return C;
        }

        double matrix_det() 
        { 
            if (cols != rows) {
            matrix_error_message();
            return NAN;
            }

            if (cols == 1) {
            return data[0];
            }

            if (cols == 2) {
            double matr_det = (data[0]) * (data[3]) - (data[1]) * (data[2]);
            return matr_det;
            }

            if (cols == 3) {
                double matr_det = (data[0]) * (data[4]) * (data[8]) + (data[1]) * (data[5]) * (data[6]) + (data[3]) * (data[7]) * (data[2]);
                matr_det -= ((data[2]) * (data[4]) * (data[6]) + (data[1]) * (data[3]) * (data[8]) + (data[0]) * (data[5]) * (data[7]));
                return matr_det;
            }
            matrix_error_message();
            return NAN;
        }

    Matrix_Calculator matrix_exp(Matrix_Calculator& A, const size_t accuracy)
        {
        if (A.cols != A.rows) {
            throw"Error! The matrix is not square!";
        }

        Matrix_Calculator E = matrix_init(A.rows, A.cols);

        if (E.data == nullptr) {
            throw"The matrix is empty";
        }
        Matrix_Calculator matrix_transfer;

        for (size_t deg_acc = 1; deg_acc <= accuracy; ++deg_acc) {
            A.matrix_print();
            matrix_transfer = A.sum_for_e(deg_acc, A);
            Matrix_Calculator buf1 = E;
            E = matrix_sum(buf1, matrix_transfer);
            //matrix_free(&buf1);
            //matrix_free(&matrix_transfer);
        }
        return E;
    }

    

};



Matrix_Calculator::Matrix_Calculator()
{
    cols = 0;
    rows = 0;
    data = nullptr ;
}

Matrix_Calculator::Matrix_Calculator(size_t cols, size_t rows, MatrixItem* data)
{
    cols = cols;
    rows = rows;
    data = data;
}

Matrix_Calculator::~Matrix_Calculator()
{
    if (data != nullptr || cols != 0 || rows != 0) {

        cols = 0;
        rows = 0;
        delete[]data;
        data = nullptr;
    }
}


int main()
{
Matrix_Calculator A, B, C, E, N;
    double deter;

   try
   {

    //error_message();

    double array[9] { 3., 2., 1., 1., 6., 7., 2., 6., 8. };
    double array2 [9] { 1., 0., 0., 1., 7., 2., 6., 6., 8. };
    double array3 [4] { 3., 2., 1., 1. };

    A.matrix_create(3, 3, array);
    B.matrix_create(3, 3, array2);
    E.matrix_create(2, 2, array3);

    A.matrix_print();
    B.matrix_print();
    B.matrix_add(A);
    B.matrix_print();

    // C = matrix_sum(A, B);
    C = A.matrix_mult(B);
    C.matrix_print();

    C = C.matrix_transp();
    C.matrix_print();

    deter =C.matrix_det();
    printf("%f \n", deter);

    //N = matrix_init(3,3);
    N = A.matrix_make_ident(3, 3);
    N.matrix_print();

    A.matrix_print();
    A = A.matrix_exp(A, 3);
    A.matrix_print();

   }
    catch (const char* error)
    {
        std::cerr << error << std::endl;
    }

   
}

