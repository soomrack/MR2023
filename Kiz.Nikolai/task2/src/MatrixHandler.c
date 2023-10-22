#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MatrixHandler.h"


// #define DEBUG


void initMatrix(Matrix * this)
{
    uint16_t rows = this->rows;
    uint16_t cols = this->cols;
    int16_t len = this->rows * sizeof(double *) + this->rows * this->cols * sizeof(double);  //  выделяем память одним маллоком
    this->data = (double **)malloc(len);
#ifdef DEBUG
    printf("[DEBUG] 2D ARRAY POINTER: %p\n", this->data);
#endif
    if (this->data) {
        double * first_element = (double*)this->data + this->rows;  // создаем указатель на первый элемент массива
        for (uint8_t row = 0; row < this->rows; row++) {
            this->data[row] = first_element + row * this->cols;  //  помещаем в указатели на строки первый их элемент
#ifdef DEBUG
            printf("[DEBUG] ADRESS OF ROW: %p\n", &this->data[row]);
#endif
        }
        size_t rowsize = this->data[1] - this->data[0];  // вычисляем размер одной строки
#ifdef DEBUG
        printf("[DEBUG] SIZE OF ONE ROW: %lx\n\n", rowsize);

#endif
    }
    else errorHandler(MALLOC_ERROR, "initMatrix");
}


void deleteData(Matrix *this)
{

    for (uint8_t rCounter = 0; rCounter < this->rows; rCounter++)
    {
        free(this->data[rCounter]);
    }
    free(this->data);

}


void fillWithData(Matrix * this, const double * filling_array, const bool printOption) {
    uint32_t size = this->rows * this->cols;
    // size_t fill_arr_size = sizeof(filling_array);
    // if (fill_arr_size != size) {
    //     errorHandler(OPERATION_ERROR, "fillWithData");
    //     return;
    // }
    double * row_poiner = this->data[0];

    for (uint8_t counter = 0; counter < size; counter++) {
        uint8_t col_index = counter % this->cols;
        double value = filling_array[counter];
        row_poiner[col_index] = value;
#ifdef DEBUG
        printf("[DEBUG] ADRESS OF ELEMENT: %p\n", &row_poiner[col_index]);
#endif
        if (printOption) __printSingleVal(value, counter, this->cols);
        if(col_index == this->cols -1) {
            row_poiner+=this->rows; 
            }
        }
}


void fillMatrix(Matrix * this, enum InfillPattern pattern, const bool printOption) {
    int32_t size = this->rows * this->cols;
    double * fillData = (double *)malloc(size * sizeof(double));
    switch (pattern) {
        case RANDOM: {
            srand(time(NULL));
            for (uint8_t i = 0; i < size; i++) {
                double val = (((double)rand() * pow(-1, rand()%2)) / (RAND_MAX - rand() + 1));
                fillData[i] = val; // then add precision of values 
            }
            break;
        }

        case UNIT: {
            if (this->rows != this->cols) printf("UNIT PARAMETER IS ONLY POSSIBLE FOR SQUARE MATRIX\n");
            else {
                for (uint8_t i = 0; i < size; i++) 
                    fillData[i] = i % (this->rows + 1) == 0 ? 1 : 0;
            }
            break;
        }

        case BLANK: {   
            memset(fillData, 0, size);
            break;
        }
        default:
            return;
            break;
    }  
    fillWithData(this, fillData, printOption);
    free(fillData);
}


void __printSingleVal(const double val, const  uint8_t counter, const int16_t cols) {
    printf("%0.3f\t", val);
    if ((counter + 1) % cols == 0)
    printf("\n");    

}


void printMatrix(const Matrix * this) {
        for (uint8_t row = 0; row < this->rows; row++) {

        for (uint8_t col = 0; col < this->cols; col++)
         __printSingleVal(this->data[row][col], col, this->cols);

    } 
}


Matrix  matrixSum(Matrix * matrix_1, Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols | matrix_1->rows != matrix_2->rows) {
        errorHandler(OPERATION_ERROR, "matrixSum");

    }
    else {
        Matrix  new_matrix = {
            .rows = matrix_1->rows,
            .cols = matrix_2->cols
        };
        uint32_t size = new_matrix.cols * new_matrix.rows;
        initMatrix(&new_matrix);
        double * fillData = (double*)malloc(sizeof(double)*size);
        memcpy(fillData, matrix_1->data[0], sizeof(double)*size);  // now it seems to work
        for (uint16_t element = 0; element < size; element++) {
            fillData[element] += *(matrix_2->data[0]+element);
        }
        fillWithData(&new_matrix, fillData, false);
        free(fillData);
        return new_matrix;
    }   

}


void errorHandler(enum Errors error, const char * func_name) {
    return;
}


Matrix  matrixSub(Matrix * matrix_1, Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols | matrix_1->rows != matrix_2->rows) {
        errorHandler(OPERATION_ERROR, "matrixSum");
    }
    else {
        Matrix  new_matrix = {
            .rows = matrix_1->rows,
            .cols = matrix_2->cols
        };
        uint32_t size = new_matrix.cols * new_matrix.rows;
        initMatrix(&new_matrix);
        double * fillData = (double*)malloc(sizeof(double)*size);
        memcpy(fillData, matrix_1->data[0], sizeof(double)*size);  // now it seems to work
        for (uint16_t element = 0; element < size; element++) {
            fillData[element] -= *(matrix_2->data[0]+element);
        }
        printf("after concat: %f\n", fillData[0]);
        fillWithData(&new_matrix, fillData, false);
        free(fillData);
        return new_matrix;
    }   

}


