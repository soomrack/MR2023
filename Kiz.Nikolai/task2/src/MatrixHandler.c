#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "MatrixHandler.h"


// #define DEBUG

const Matrix NULL_MATRIX = {.rows = 0, .cols = 0, .data = NULL};

Matrix create_matrix(const size_t rows, const size_t cols)
{
    if (SIZE_MAX / sizeof(matrix_element) / cols < rows) {
        matrix_error_handler(SIZE_ERROR, "create_matrix");
        return NULL_MATRIX;
    }
    Matrix A = {.rows = rows, .cols = cols, .data = NULL};
    if (rows == 0 || cols == 0) return A;
    size_t len = rows * sizeof(matrix_element *) + rows * cols * sizeof(matrix_element);  //  выделяем память одним маллоком
    A.data = (matrix_element**)malloc(len);
    if (!A.data) {
        matrix_error_handler(MALLOC_ERROR, "create_matrix");
        return NULL_MATRIX;
    }   
#ifdef DEBUG
    printf("[DEBUG] 2D ARRAY POINTER: %p\n", this->data);
#endif
    matrix_element * first_element = (matrix_element*)A.data +A.rows;  // создаем указатель на первый элемент массива
    for (size_t row = 0; row < A.rows; row++) {
            A.data[row] = first_element + row * A.cols;  //  помещаем в указатели на строки первый их элемент
#ifdef DEBUG
            printf("[DEBUG] ADRESS OF ROW: %p\n", &this->data[row]);
#endif
        }
#ifdef DEBUG
    size_t rowsize = A.data[1] - A.data[0];  // вычисляем размер одной строки
    printf("[DEBUG] SIZE OF ONE ROW: %lx\n\n", rowsize);
#endif
    return A;
}


void delete_matrix(Matrix *this)
{
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "delete_matrix");
        return;
    }
    free(this->data);
    this->cols = 0;
    this->rows = 0;
    this->data = NULL;
#ifdef DEBUG
    printf("[DEBUG] [FREE] RELEASED POINTER: %p\n", this->data);
#endif
}


void fill_with_data(Matrix * this, matrix_element * filling_array) {
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "fill_with_data");
        return;
    }
    size_t size = matrix_size(this);
    memcpy(this->data[0], filling_array, size * sizeof(matrix_element));
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
    switch (pattern) {
        case RANDOM: {
            random_pattern(this, size, fill_data);
            break;
        }
        case UNIT: {
            if (this->rows != this->cols) {
                matrix_error_handler(MATH_DOMAIN_ERROR, "fill_matrix");
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
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "print_matrix");
        return;
    }
    printf("Matrix data at : %p\n", this->data);
    for (size_t row = 0; row < this->rows; row++) {
        for (size_t col = 0; col < this->cols; col++)
            print_matrix_element(this->data[row][col], col, this->cols);
    }
    printf("\n"); 
}


Matrix  matrix_sum(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols || matrix_1->rows != matrix_2->rows) {
        matrix_error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
        return NULL_MATRIX;
    }
        Matrix new_matrix = create_matrix(matrix_1->rows, matrix_1->cols);
        if (NULL == new_matrix.data) {
            matrix_error_handler(NULL_MATRIX_ERROR, "matrix_sum");
            return NULL_MATRIX; 
        }
        size_t size = matrix_size(&new_matrix);
        memcpy(new_matrix.data[0], matrix_1->data[0], sizeof(matrix_element) * size);
        for (size_t counter = 0; counter < size; counter++) {
            *(new_matrix.data[0]+counter) += *(matrix_2->data[0]+counter);
        }
        return new_matrix;
}


Matrix  matrix_sub(const Matrix * matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->cols || matrix_1->rows != matrix_2->rows) {
        matrix_error_handler(MATH_DOMAIN_ERROR, "matrix_sum");
        return NULL_MATRIX;
    }
    Matrix new_matrix = create_matrix(matrix_1->rows, matrix_1->cols);
    if (NULL == new_matrix.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_sub");
        return NULL_MATRIX;
    }
    size_t size = matrix_size(&new_matrix);
    memcpy(new_matrix.data[0], matrix_1->data[0], sizeof(matrix_element) * size);
    for (size_t counter = 0; counter < size; counter++) {
        *(new_matrix.data[0]+counter) -= *(matrix_2->data[0]+counter);
    }
    return new_matrix;
}


void matrix_transposition(Matrix * this) {
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_transposition");
        return;
    }
    Matrix buff = create_matrix(this->cols, this->rows);
    if (NULL == buff.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_transposition");
        return;
    }
    size_t size = matrix_size(this);
    for (size_t row = 0; row < this->rows; row++) {
        for (size_t col = 0; col < this->cols; col++) {
            buff.data[col][row] = this->data[row][col];
        }
    }
    free(this->data);
    this->data = buff.data;
    this->rows = buff.rows;
    this->cols = buff.cols;
}


Matrix get_submatrix(const Matrix * this, const size_t row_to_delete, const size_t col_to_delete) {
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "get_submatrix");
        return NULL_MATRIX;
    }
    size_t new_rows = this->rows - 1;
    size_t new_cols = this->cols - 1;
    size_t size = matrix_size(this);
    Matrix new_matrix  = create_matrix(new_rows, new_cols);

    if (NULL == new_matrix.data) return NULL_MATRIX;

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
        matrix_error_handler(MATH_DOMAIN_ERROR, "martix_determinant");
        return;
    }
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_determinant");
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

Matrix matrix_multiplication(const Matrix* matrix_1, const Matrix * matrix_2) {
    if (matrix_1->cols != matrix_2->rows) {
        matrix_error_handler(MATH_DOMAIN_ERROR, "matrix_multiplication");
        return NULL_MATRIX;
    }
    if (NULL == matrix_1->data || NULL == matrix_2->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_multiplication");
        return NULL_MATRIX;
    }
    size_t dimension = matrix_1->cols;
    Matrix new_matrix = create_matrix(matrix_1->rows, matrix_2->cols);
    if (NULL == new_matrix.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_multiplication");
        return NULL_MATRIX;
    }
    fill_matrix(&new_matrix, BLANK);
    for (size_t row = 0; row < new_matrix.rows; row++) 
        for (size_t col = 0; col < new_matrix.cols; col++)
            for (size_t idx = 0; idx < dimension; idx++)
                new_matrix.data[row][col] += matrix_1->data[row][idx] * matrix_2->data[idx][col];
            
    return new_matrix;
}

void constant_division(Matrix this, double constant) {
    if (NULL == this.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "constant_division");
        return;
    }
    size_t size = matrix_size(&this);
    for (size_t idx = 0; idx < size; idx++) {
        *(this.data[0] + idx) /= constant;
    }
}


uint64_t factorial(const uint16_t number) {
    if (number == 1 || number == 0) return 1;
    return number * factorial(number - 1);
}


Matrix matrix_exponent(const Matrix* this, const uint8_t degree) {
    if (NULL == this->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent");
        return NULL_MATRIX;
    }
    Matrix A = create_matrix(this->rows, this->cols);
    if (NULL == A.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent");
        return NULL_MATRIX;
    }
    fill_matrix(&A, UNIT);
    if (degree == 1) return A;
    if (degree == 2) {
            matrix_increasing(&A, this);
            return A;
    }
    matrix_increasing(&A, this);
    Matrix buf_summand = create_matrix(this->rows, this->cols);
    if (NULL == buf_summand.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent");
        delete_matrix(&A);
        return NULL_MATRIX;
    }
    fill_with_data(&buf_summand, this->data[0]);
    for (uint8_t idx = 2; idx < degree; idx++) {
            Matrix summand = matrix_exponent_summand(&buf_summand, this, idx);
                if (NULL == summand.data) {
                    matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent");
                    delete_matrix(&A);
                    delete_matrix(&summand);
                    return NULL_MATRIX;
                }
            fill_with_data(&buf_summand, summand.data[0]);
            matrix_increasing(&A, &buf_summand);
            delete_matrix(&summand);
    }
    delete_matrix(&buf_summand);
    return A;

}


Matrix matrix_exponent_summand(const Matrix* left_operand, const Matrix* right_operand, const uint8_t degree) {
    if (NULL == left_operand->data || NULL == right_operand->data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent_summand");
        return NULL_MATRIX;
    }
    Matrix summand = matrix_multiplication(left_operand, right_operand);
    if (NULL == summand.data) {
        matrix_error_handler(NULL_MATRIX_ERROR, "matrix_exponent_summand");
        return NULL_MATRIX;
    }
    constant_division(summand, degree);
    return summand;
}


void matrix_increasing(Matrix* to_increase, const Matrix* increasing) {
    if (to_increase->rows != increasing->rows || to_increase->cols != increasing->cols) {
        matrix_error_handler(MATH_DOMAIN_ERROR, "matrix_self_sum");
        return;
    }
    size_t size = matrix_size(to_increase);
    for (size_t idx = 0; idx < size; idx++) {
        *(to_increase->data[0] + idx) += *(increasing->data[0] + idx);
    }
}


void matrix_error_handler(const enum MatrixErrors error, const char * func_name) {
    printf("Error occured in function: %s : %i\n", func_name, error);
}


