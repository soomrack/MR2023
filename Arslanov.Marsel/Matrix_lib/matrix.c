
#include "matrix.h"

// TODO: Заменить размер на static inline size
//! Матрица может вывестись, хотя после превращения ее в единчную, выдалась ошибка. \
// указатель спокойно заходит за пределы матрицы 

matrix* matrix_new(size_t rows, size_t cols)
{
    if (rows == 0 || cols == 0)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NULL;
    }
    if (rows >= SIZE_MAX / sizeof(matrix_element) / cols)
    {
        matrix_error(MEMORY_ERROR);
        return NULL;
    }

    matrix *m = (matrix*)malloc(sizeof(matrix*));
    m->rows = rows;
    m->cols = cols;
    //! Matrix storage in one continious piece
    m->data = (matrix_element*)malloc(m->rows * m->cols * sizeof(matrix_element));

    if (!m->data)
    {
        matrix_error(MEMORY_ERROR);
        return NULL;
    }

    return m;
}

void matrix_free(matrix* m)
{
    if (m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return;
    }

    free(m->data);
    free(m);
}

void matrix_print(matrix* m)
{
    if (m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return;
    }

    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            printf("%.2f \t", m->data[m->cols * i + j]);
        }
        printf("\n");
    }
}

void matrix_error(ERROR_TYPE error)
{
    switch (error) {
        case MEMORY_ERROR:
            printf("Memory allocation error\n");
            break;
        case BAD_MATRIX_ERROR:
            printf("Incalculable or empty matrix error\n");
            break;
        case COLS_ROWS_ERROR:
            printf("Wrong number of columns or rows\n");
            break;
        case COPY_ERROR:
            printf("Memory copy error\n");
            break;
        case DET_ERROR:
            printf("Determinant can be only calculated for 1x1, 2x2 or 3x3 matrix\n");
            break;
        case ZERO_DIV:
            printf("ZERO DIVISION!!\n");
            break;
        default:
            printf("Undefined error\n");
            break;
    }
}

void matrix_fill(matrix* m, MATRIX_TYPE type)
{
    if(m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return;
    }

    switch (type)
    {
    case ZERO:
        memset(m->data, '0', m->cols * m->rows);
        break;
    
    case INCREASING:
        for (size_t i = 0; i < m->rows * m->cols; i++) m->data[i] = i;
        break;
    
    case UNIT:

        if (m->cols == m->rows)
        {
            for (size_t i = 0; i < m->cols * m->rows; i++)
            {
                m->data[i] = i % (m->rows + 1) == 0 ? 1 : 0;
            }
        }
        else
        {
            matrix_error(COLS_ROWS_ERROR);
            return;
        }
        break;

    case RANDOM:
        srand(time(NULL));
        for (size_t i = 0; i < m->cols * m->rows; i++)
        {
            double random_value = (double)(rand() % (100 + 100 + 1)) - 100;    // rand() % (max - min + 1)) + min
            m->data[i] = random_value;
        }
    }

}

uint8_t matrices_sizes_equal(const matrix* a, const matrix* b)
{
    if (a->cols == b->cols && a->rows == b->rows)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}

matrix* matrix_sum(matrix* a, matrix* b)
{
    if (matrices_sizes_equal(a, b))
    {
        matrix* sum = matrix_new(a->rows, a->cols);
        memcpy(sum->data, a->data, a->cols * a->rows * sizeof(matrix_element));

        for (size_t i = 0; i < a->rows * a->cols; i++)
        {
            sum->data[i] += b->data[i];
        }
        return sum;
    }
    else
    {
        matrix_error(COLS_ROWS_ERROR);
        return NULL;
    }
}

// a - b
matrix* matrix_sub(matrix* a, matrix* b)
{
    if (matrices_sizes_equal(a, b))
    {
        matrix* sum = matrix_new(a->rows, a->cols);
        memcpy(sum->data, a->data, a->cols * a->rows * sizeof(matrix_element));

        for (size_t i = 0; i < a->rows * a->cols; i++)
        {
            sum->data[i] -= b->data[i];
        }
        return sum;
    }
    else
    {
        matrix_error(COLS_ROWS_ERROR);
        return NULL;
    }
}

matrix* matrix_transposition(matrix *m)
{
    if(m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NULL;
    }

    // Создаем новую матрицу с поменяными строками и столбцами (транспонированную)
    matrix* result = matrix_new(m->cols, m->rows);

    for (size_t i = 0; i < m->rows; i++)
    {
        for (size_t j = 0; j < m->cols; j++)
        {
            result->data[i * m->cols + j] = m->data[j * m->cols + i];
        }
    }

    m->rows = result->rows;
    m->cols = result->cols;
    memcpy(m->data, result->data, sizeof(matrix_element) * m->cols * m->rows);
    // memcpy(m, result, sizeof(matrix));      // Почему нельзя просто скопироовать матрицу?

    matrix_free(result); 

    return m;
}

double matrix_determinant(const matrix* m)
{
    if(m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NAN;
    }

    if (m->rows != m->cols)
    {
        matrix_error(DET_ERROR);
        return NAN;
    }

    // m->data[i][j] == m->data[i * m->rows + j]
    switch (m->rows)
    {
    case 1:
        return m->data[0];
        
    case 2:
        return m->data[0] * m->data[3] - 
               m->data[1] * m->data[2];
    
    case 3:
        return  (m->data[0] * m->data[4] * m->data[8]) +
                (m->data[1] * m->data[5] * m->data[6]) +
                (m->data[2] * m->data[3] * m->data[7]) -
                (m->data[2] * m->data[4] * m->data[6]) -
                (m->data[0] * m->data[5] * m->data[7]) -
                (m->data[1] * m->data[3] * m->data[8]);

    default:
        matrix_error(DET_ERROR);
        return NAN;
    }
}

matrix* matrix_mult(matrix* a, const matrix* b)
{
    if (a == NULL || a->data == NULL ||
        b == NULL || b->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NULL;
    }

    if (a->cols != b->rows) return NULL;

    matrix* product = matrix_new(a->cols, b->rows);

    for(size_t row = 0; row < a->rows; row++)
    {
        for(size_t col = 0; col < b->cols; col++)
        {
            product->data[row * (a->cols) + col] = 0;

            for(size_t idx = 0; idx < a->cols; idx++)
            {
                product->data[row * (a->cols) + col] += (a->data[(row * a->cols) + idx]) * (b->data[(idx * b->cols)+ col]);
            }
        }
    }

    matrix_copy(a, product);
    matrix_free(product);

    return a;
}

void matrix_copy(matrix* dest, const matrix* src)
{
    if (src  == NULL || src->data  == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return;
    }

    // if (dest != NULL) matrix_free(dest);

    // dest = matrix_new(src->rows, src->cols);
    free(dest->data);
    dest->data = (double*)malloc(sizeof(matrix_element) * src->cols * src->rows);
    dest->cols = src->cols;
    dest->rows = src->rows;
    memcpy(dest->data, src->data, dest->cols * dest->rows * sizeof(matrix_element));

    if (dest->data == NULL)
    {
        matrix_error(COPY_ERROR);
        return;
    }
}

matrix* matrix_exp(const matrix* m, const uint8_t accuracy)
{
    if (m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NULL;
    }

    matrix* result = matrix_new(m->rows, m->rows);

    matrix_fill(result, UNIT);
    if (accuracy == 1) return result;
    if (accuracy == 2)
    {
        matrix_increase(result, m);
        return result;    
    }
    matrix_increase(result, m);

    // Переменная, которая последовательно хранит матрицу в виде m^1, m^2, m^3 и тд.
    matrix* m_exp_buf = matrix_new(m->rows, m->cols);
    if (m_exp_buf == NULL)
    {
        matrix_error(MEMORY_ERROR);
        matrix_free(result);
        return NULL;
    }
    matrix_copy(m_exp_buf, m);

    for (uint8_t cnt = 2; cnt < accuracy; cnt++)
    {
        m_exp_buf = matrix_mult(m_exp_buf, m);

        matrix* buf_m = matrix_new(m->rows, m->cols); 
        matrix_copy(buf_m, m_exp_buf);
        if (buf_m == NULL || buf_m->data == NULL) 
        {
            matrix_error(MEMORY_ERROR);
            matrix_free(m_exp_buf);
            matrix_free(result);
            return NULL;
        }

        double divider = factorial(cnt);
        buf_m = matrix_scalar_division(buf_m, divider);
        matrix_increase(result, buf_m);
        matrix_free(buf_m);
    }    

    matrix_free(m_exp_buf);

    return result;
}

matrix* matrix_increase(matrix* m, const matrix* increase_matrix)
{
    if (matrices_sizes_equal(m, increase_matrix))
    {
        for (size_t i = 0; i < m->cols * m->rows; i++)
            m->data[i] += increase_matrix->data[i];
    }
    else
    {
        matrix_error(COLS_ROWS_ERROR);
        return NULL;
    }

    return m;
}

uint64_t factorial(const uint16_t value)
{
    if (value == 1 || value == 0) return 1;
    return value * factorial(value - 1);
}

matrix* matrix_scalar_division(matrix* m, const double value)
{
    if (value == 0)
    {
        matrix_error(ZERO_DIV);
        return NULL;
    } 

    if (m == NULL || m->data == NULL)
    {
        matrix_error(BAD_MATRIX_ERROR);
        return NULL;
    }

    for (size_t i = 0; i < m->cols * m->rows; i++)
    {
        m->data[i] /= value;
    }

    return m;
}
