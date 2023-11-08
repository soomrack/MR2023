#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "MatrixHandler.h"


// #define DEBUG



void init_data(Matrix * this)
{
    if (SIZE_MAX / 8 < this->rows + this->rows * this->cols ||
     (this->rows + this->cols) < 2) {
        error_handler(SIZE_ERROR, "init_data");
        return;
     } 
    size_t len = this->rows * sizeof(matrix_element *) + this->rows * this->cols * sizeof(matrix_element);  //  выделяем память одним маллоком
    this->data = (matrix_element **)malloc(len);
    if (!this->data) {
        error_handler(MALLOC_ERROR, "init_data");
        return;
    }
#ifdef DEBUG
    printf("[DEBUG] 2D ARRAY POINTER: %p\n", this->data);
#endif
    matrix_element * first_element = (matrix_element*)this->data + this->rows;  // создаем указатель на первый элемент массива
    for (size_t row = 0; row < this->rows; row++) {
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


Matrix init_matrix(const size_t rows, const size_t cols) {
    Matrix matrix = {
        .rows = rows,
        .cols = cols
    };
    init_data(&matrix);
    return matrix;
}

void delete_matrix(Matrix *this)
{
    free(this->data);
#ifdef DEBUG
    printf("[DEBUG] [FREE] RELEASED POINTER: %p\n", this->data);
#endif
    this->cols = 0;
    this->rows = 0;
}


void fill_with_data(Matrix * this, matrix_element * filling_array) {
    size_t size = matrix_size(this);
    matrix_element * first_element = this->data[0];
    memcpy(first_element, filling_array, size * sizeof(matrix_element));
#ifdef DEBUG
        for (size_t row = 0; row < this->rows; row++)
            for (size_t col = 0; col < this->cols; col++) 
                printf("ADRESS OF THE ELEMENT : %p\n", &this->data[row][col]);
        printf("\n");
#endif
}


void random_pattern(Matrix * this, size_t size, matrix_element * fill_data) {
    srand(time(NULL));
    for (size_t idx = 0; idx < size; idx++) {
        matrix_element val = (((matrix_element)rand() * pow(-1, rand()%2)) / (RAND_MAX - rand() + (matrix_element)rand()));
        fill_data[idx] = val;
    }
}


void unit_pattern(Matrix * this, size_t size, matrix_element * fill_data) {
    for (size_t idx = 0; idx < size; idx++) 
        fill_data[idx] = idx % (this->rows + 1) == 0 ? 1 : 0;
}


void blank_pattern(Matrix * this, size_t size, matrix_element * fill_data) {
    memset(fill_data, 0, size);
}


void raising_pattern(Matrix * this, size_t size, matrix_element * fill_data) {
    for (size_t idx = 0; idx < size; idx++)
        fill_data[idx] = idx + 1;
}


void fill_matrix(Matrix * this, const enum InfillPattern pattern) {
    size_t size = matrix_size(this);
    matrix_element fill_data[size];
    if (!fill_data) {
        error_handler(MALLOC_ERROR, "fill_matrix");
        return;
    } 
    switch (pattern) {
        case RANDOM: {
            random_pattern(this, size, fill_data);
            break;
        }
        case UNIT: {
            if (this->rows != this->cols) {
                error_handler(MATH_DOMAIN_ERROR, "fill_matrix");
                return;
            }
            unit_pattern(this, size, fill_data);
            break;
        }
        case BLANK: {  
            blank_pattern(this, size, fill_data); 
            break;
        }
        case RAISING: {
            raising_pattern(this, size, fill_data);
            break;
        }
        default:
            break;
    }  
    fill_with_data(this, fill_data);
}


void print_matrix_element(const matrix_element val, const  size_t counter, const size_t cols) {
    printf("%0.3f\t", val);
    if ((counter + 1) % cols == 0)
    printf("\n");    

}


void print_matrix(const Matrix * this) {
    printf("Matrix data at : %p\n", this->data);
    for (size_t row = 0; row < this->rows; row++) {
        for (size_t col = 0; col < this->cols; col++)
            print_matrix_element(this->data[row][col], col, this->cols);
    }
    printf("\n"); 
}


Matrix  matrix_sum(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols || matrix_1->rows != matrix_2->rows) {
        error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
        return;
    }
    else {
        Matrix new_matrix = {
            .rows = matrix_1->rows,
            .cols = matrix_2->cols
        };
        size_t size = matrix_size(&new_matrix);
        init_data(&new_matrix);
        matrix_element fill_data[size];
        memcpy(fill_data, matrix_1->data[0], sizeof(matrix_element) * size);  // now it seems to work
        for (size_t counter = 0; counter < size; counter++) {
            fill_data[counter] += *(matrix_2->data[0]+counter);
        }
        fill_with_data(&new_matrix, fill_data);
        return new_matrix;
    }   
}


Matrix  matrix_sub(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols || matrix_1->rows != matrix_2->rows) {
        error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
        return;
    }
    Matrix  new_matrix = {
        .rows = matrix_1->rows,
        .cols = matrix_2->cols
    };
    size_t size = matrix_size(&new_matrix);
    init_data(&new_matrix);
    matrix_element fill_data[size];
    memcpy(fill_data, matrix_1->data[0], sizeof(matrix_element) * size);  // now it seems to work
    for (size_t counter = 0; counter < size; counter++)
        fill_data[counter] -= *(matrix_2->data[0]+counter);
    fill_with_data(&new_matrix, fill_data);
    return new_matrix;
}


void matrix_transposition(Matrix * this) {
    size_t size = matrix_size(this);
    matrix_element fill_data[size];
    for (size_t col = 0; col < this->cols; col++) {
        for (size_t row = 0; row < this->rows; row++) {
            matrix_element value = this->data[row][col];
            fill_data[col*this->rows + row] = value;
#ifdef DEBUG
            printf("%.3f\t", value);
#endif
        }
#ifdef DEBUG
        printf("\n");
#endif
    }
    size_t new_rows = this->cols;
    this->cols = this->rows;
    this->rows = new_rows;
    init_data(this);
    fill_with_data(this, fill_data);
}


Matrix get_submatrix(const Matrix * this, const size_t row_to_delete, const size_t col_to_delete) {
    size_t new_rows = this->rows - 1;
    size_t new_cols = this->cols - 1;
    size_t size = matrix_size(this);
    Matrix new_matrix = {
        .cols = new_cols,
        .rows = new_rows
    };
    init_data(&new_matrix);
    size_t new_size = matrix_size(&new_matrix);
    matrix_element fill_data[new_size];
    size_t new_data_counter = 0;
    size_t row_index = 0;
    for (size_t count = 0; count < size; count++) {
        size_t col_index = count % this->cols;
        if (row_index != row_to_delete & col_index != col_to_delete) {
            fill_data[new_data_counter] = this->data[row_index][col_index];
            new_data_counter++;
        }
        if (col_index + 1 == this->cols) {
            row_index++;
        }
    }
    fill_with_data(&new_matrix, fill_data);
    return new_matrix;
}


double matrix_determinant(const Matrix * this) {
    if (this->rows != this->cols) {
        error_handler(MATH_DOMAIN_ERROR, "martix_determinant");
        return;
    } 
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
        for (size_t col_counter = 0; col_counter < this->cols; col_counter++) {
            Matrix submatrix = get_submatrix(this, 0, col_counter);
            Matrix * temp = &submatrix;
            determinant += this->data[0][col_counter] * pow(-1, col_counter) * matrix_determinant(temp);
            delete_matrix(&submatrix);
        }
#ifdef DEBUG
        printf("[DEBUG] MATRIX AT %p. DETERMINANT: %0.3f\n", this->data, determinant);
#endif
        return determinant;
        break;
    }
}

Matrix matrix_multiplication(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->rows) {
    error_handler(MATH_DOMAIN_ERROR, "matrix_multiplication");
    return;
    }
    size_t dimension = matrix_1->cols;
    Matrix new_matrix = init_matrix(matrix_1->rows, matrix_2->cols);
    fill_matrix(&new_matrix, BLANK);
    for (size_t row = 0; row < new_matrix.rows; row++) 
        for (size_t col = 0; col < new_matrix.cols; col++)
            for (size_t idx = 0; idx < dimension; idx++)
                new_matrix.data[row][col] += matrix_1->data[row][idx] * matrix_2->data[idx][col];
            
    return new_matrix;
}


void constant_division(Matrix * this, double constant) {
    size_t size = matrix_size(this);
    for (size_t idx = 0; idx < size; idx++) {
        *(this->data[0] + idx) /= constant;
    }

}


uint64_t factorial(const uint16_t number) {
    if (number == 1 || number == 0) return 1;
    return number * factorial(number - 1);
}


Matrix matrix_exponent(const Matrix * this, const int8_t degree) {
    if (this->rows != this->cols) {
        error_handler(MATH_DOMAIN_ERROR, "matrix_exponent");
        return;
    }
    size_t dimension = this->rows;
    Matrix exponent = init_matrix(dimension, dimension);
    fill_matrix(&exponent, UNIT);
    exponent = matrix_sum(&exponent, this);
    Matrix powered_matrix = *this;
    for (uint8_t idx = 2; idx < degree; idx++) {
        print_matrix(&exponent);
        powered_matrix = matrix_multiplication(&powered_matrix, this);
#ifdef DEBUG
        printf("Powered matrix:\n");
        print_matrix(&powered_matrix);
#endif
        double dividor = factorial(idx); 
        constant_division(&powered_matrix, dividor);
        exponent = matrix_sum(&exponent, &powered_matrix);
#ifdef DEBUG
        printf("Dividor is: %f\n", dividor);
        printf("Sum with matrix:\n");
        print_matrix(&powered_matrix);
        printf("Result is:\n");
        print_matrix(&exponent);
#endif
    }
    delete_matrix(&powered_matrix);
    return exponent;
}


void error_handler(const enum MatrixErrors error, const char * func_name) {
    printf("Error occured in function: %s : %i\n", func_name, error);
}


