#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "MatrixHandler.h"


#define DEBUG



void init_data(Matrix * this)
{
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
#ifdef DEBUG
        size_t rowsize = this->data[1] - this->data[0];  // вычисляем размер одной строки
        printf("[DEBUG] SIZE OF ONE ROW: %lx\n\n", rowsize);
#endif
    }
    else error_handler(MALLOC_ERROR, "init_data");
}


Matrix init_matrix(uint16_t rows, uint16_t cols) {
    Matrix matrix = {
        .rows = rows,
        .cols = cols
    };
    init_data(&matrix);
    return matrix;
}

void delete_data(Matrix *this)
{
    free(this->data);
}


void fill_with_data(Matrix * this, double * filling_array, const bool print_option, const bool dynamical_array) {
    uint32_t size = matrix_size(this);
    uint16_t row_counter = 0;
    for (uint32_t counter = 0; counter < size; counter++) {
        uint16_t col_index = counter % this->cols;
        double value = filling_array[counter];
        this->data[row_counter][col_index] = value;
#ifdef DEBUG
        printf("[DEBUG] ADRESS OF ELEMENT: %p\n", &this->data[row_counter][col_index]);
#endif
        if (print_option) __print_single_val(value, counter, this->cols);
        if(col_index == this->cols -1) 
            row_counter++; 
    }
#ifdef DEBUG
    printf("\n");
#endif
    if (dynamical_array) free(filling_array);
}


void fill_matrix(Matrix * this, enum InfillPattern pattern, const bool print_option) {
    uint32_t size = matrix_size(this);
    double * fill_data = (double *)malloc(size * sizeof(double));
    if (!fill_data) error_handler(MALLOC_ERROR, "fill_matrix");
    switch (pattern) {
        case RANDOM: {
            srand(time(NULL));
            for (uint32_t i = 0; i < size; i++) {
                double val = (((double)rand() * pow(-1, rand()%2)) / (RAND_MAX - rand() + (double)rand()));
                fill_data[i] = val;
            }
            break;
        }

        case UNIT: {
            if (this->rows != this->cols) {
                free(fill_data);
                error_handler(MATH_DOMAIN_ERROR, "fill_matrix");
            }
            else {
                for (uint32_t i = 0; i < size; i++) 
                    fill_data[i] = i % (this->rows + 1) == 0 ? 1 : 0;
            }
            break;
        }

        case RAISING: {
            for (uint32_t i = 0; i < size; i++)
                fill_data[i] = i;
        }

        case BLANK: {   
            memset(fill_data, 0, size);
            break;
        }
        default:
            break;
    }  
    fill_with_data(this, fill_data, print_option, true);
}


void __print_single_val(const double val, const  uint8_t counter, const int16_t cols) {
    printf("%0.3f\t", val);
    if ((counter + 1) % cols == 0)
    printf("\n");    

}


void print_matrix(const Matrix * this) {
    printf("Matrix at : %p\n", this);
    for (uint16_t row = 0; row < this->rows; row++) {

        for (uint16_t col = 0; col < this->cols; col++)
            __print_single_val(this->data[row][col], col, this->cols);
    }
    printf("\n"); 
}


Matrix  matrix_sum(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols | matrix_1->rows != matrix_2->rows)
        error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
    else {
        Matrix new_matrix = {
            .rows = matrix_1->rows,
            .cols = matrix_2->cols
        };
        uint32_t size = matrix_size(&new_matrix);
        init_data(&new_matrix);
        double * fill_data = (double*)malloc(sizeof(double)*size);
        memcpy(fill_data, matrix_1->data[0], sizeof(double)*size);  // now it seems to work
        for (uint16_t element = 0; element < size; element++) {
            fill_data[element] += *(matrix_2->data[0]+element);
        }
        fill_with_data(&new_matrix, fill_data, false, true);
        return new_matrix;
    }   

}


Matrix  matrix_sub(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols | matrix_1->rows != matrix_2->rows) {
        error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
    }
    else {
        Matrix  new_matrix = {
            .rows = matrix_1->rows,
            .cols = matrix_2->cols
        };
        uint32_t size = matrix_size(&new_matrix);
        init_data(&new_matrix);
        double * fill_data = (double*)malloc(sizeof(double)*size);
        memcpy(fill_data, matrix_1->data[0], sizeof(double)*size);  // now it seems to work
        for (uint16_t element = 0; element < size; element++) {
            fill_data[element] -= *(matrix_2->data[0]+element);
        }
        fill_with_data(&new_matrix, fill_data, false, true);
        return new_matrix;
    }   

}


void matrix_transposition(Matrix * this) {
    uint32_t size = matrix_size(this);
    double * fill_data = (double*)malloc(size*sizeof(double));
    if (!fill_data) error_handler(MALLOC_ERROR, "matrix_transposition");
    for (uint16_t col = 0; col < this->cols; col++) {
        for (uint16_t row = 0; row < this->rows; row++) {
            double value = this->data[row][col];
            fill_data[col*this->rows + row] = value;
#ifdef DEBUG
            printf("%.3f\t", value);
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
    }
    delete_data(this);
    uint16_t new_rows = this->cols;
    this->cols = this->rows;
    this->rows = new_rows;
    init_data(this);
    fill_with_data(this, fill_data, false, true);
}


Matrix __get_submatrix(const Matrix * this, uint16_t row_to_delete, uint16_t col_to_delete) {

    uint16_t new_rows = this->rows - 1;
    uint16_t new_cols = this->cols - 1;
    uint32_t size = matrix_size(this);
    Matrix new_matrix = {
        .cols = new_cols,
        .rows = new_rows
    };
    init_data(&new_matrix);
    uint32_t new_size = matrix_size(&new_matrix);
    double * fill_data = (double*)malloc(new_size*sizeof(double));
    if (!fill_data) error_handler(MALLOC_ERROR, "__get_submatrix");
    uint32_t new_data_counter = 0;
    uint16_t row_index = 0;
    for (uint32_t count = 0; count < size; count++) {
        uint16_t col_index = count % this->cols;
        if (row_index != row_to_delete & col_index != col_to_delete) {
            fill_data[new_data_counter] = this->data[row_index][col_index];
            new_data_counter++;
        }
        if (col_index + 1 == this->cols) {
            row_index++;
        }
    }
    fill_with_data(&new_matrix, fill_data, false, true);
    return new_matrix;
}


double matrix_determinant(const Matrix * this) {
    if (this->rows != this->cols) error_handler(MATH_DOMAIN_ERROR, "martix_determinant");
    switch (this->rows)
    {
    case 1:
        return this->data[0][0];
        break;
    
    case 2:
        return this->data[0][0] * this->data[1][1] - 
                this->data[0][1] * this->data[1][0];
            break;
    default:
        double determinant = 0;
        for (uint16_t col_counter = 0; col_counter < this->cols; col_counter++) {
            Matrix submatrix = __get_submatrix(this, 0, col_counter);
            determinant += this->data[0][col_counter] * pow(-1, col_counter) * matrix_determinant(&submatrix);
        }
#ifdef DEBUG
        printf("[DEBUG] MATRIX AT %p. DETERMINANT: %0.3f\n", this, determinant);
#endif
        return determinant;
        break;
    }
}

// Matrix matrix_multiplication(const Matrix * )


void error_handler(enum Errors error, const char * func_name) {
    printf("Error occured in function: %s : %i\n", func_name, error);
    exit(error);
}


