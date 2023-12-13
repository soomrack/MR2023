#include <Matrix.h>

const struct Matrix MATRIX_NULL = {0, 0, NULL};
const matrix_item RANDOM_LOW = -10., RANDOM_HIGH = 10.;


void matrix_error(enum ErrorType error) {
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
        default:
            printf("Undefined error\n");
            break;
    }
}

/*
   Функция matrix_allocate выделяет память для матрицы с заданным числом строк и столбцов.
   Возвращает выделенную матрицу или MATRIX_NULL в случае ошибки.
   Параметры:
       - rows: количество строк в матрице
       - cols: количество столбцов в матрице
*/

struct Matrix matrix_allocate(const size_t rows, const size_t cols) {
    // Проверка на случай, если переданы нулевые значения для rows и cols
    if (rows == 0 && cols == 0) return MATRIX_NULL;

    // Проверка на переполнение памяти при выделении
    if (rows >= SIZE_MAX / sizeof(matrix_item) / cols) {
        matrix_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    // Создание структуры матрицы M с указанным числом строк и столбцов
    struct Matrix M = {cols, rows, NULL};

    // Выделение памяти под массив элементов матрицы
    M.data = (matrix_item *) malloc(M.cols * M.rows * sizeof(matrix_item));

    // Проверка на успешное выделение памяти
    if (M.data == NULL) {
        // Вывод ошибки и возврат MATRIX_NULL в случае неудачи
        matrix_error(MEMORY_ERROR);
        return MATRIX_NULL;
    }

    // Возврат выделенной матрицы M
    return M;
}

/*
   Функция matrix_fill заполняет матрицу M указанного типа значениями в соответствии с параметром matrix_type.
   Параметры:
       - M: указатель на структуру матрицы, которую нужно заполнить
       - matrix_type: тип заполнения матрицы (ZEROS, ONES, RANDOM, IDENTITY)
*/

void matrix_fill(struct Matrix *M, enum MatrixType matrix_type) {
    switch (matrix_type) {
        // Заполнение матрицы нулями
        case (ZEROS):
            memset(M->data, 0, M->cols * M->rows * sizeof(matrix_item));
            break;

        // Заполнение матрицы единицами
        case (ONES):
            for (size_t idx = 0; idx < M->cols * M->rows; idx++) M->data[idx] = 1.;
            break;

        // Заполнение матрицы случайными значениями
        case (RANDOM):
            for (size_t idx = 0; idx < M->cols * M->rows; idx++)
                M->data[idx] = ((matrix_item) rand() * (RANDOM_HIGH - RANDOM_LOW))
                               / (matrix_item) RAND_MAX + RANDOM_LOW;
            break;

        // Заполнение матрицы в соответствии с единичной матрицей
        case (IDENTITY):
            memset(M->data, 0, M->rows * M->cols * sizeof(matrix_item));
            // Установка диагональных элементов в 1, если матрица квадратная
            if (M->cols == M->rows)
                for (size_t row = 0; row < M->rows; row++)
                    for (size_t col = 0; col < M->cols; col++) {
                        if (row == col) M->data[row * M->cols + col] = 1.;
                    }
            // Вывод ошибки, если матрица не квадратная
            else matrix_error(COLS_ROWS_ERROR);
            break;
    }
}

/*
   Функция matrix_print выводит содержимое матрицы M в консоль.
   Параметры:
       - M: структура матрицы, которую нужно вывести
*/

void matrix_print(const struct Matrix M) {
    if (M.data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(BAD_MATRIX_ERROR);
    } else {
        for (size_t idx = 1; idx <= M.cols * M.rows; ++idx) {
            printf("%.2f \t", M.data[idx - 1]);
            if (idx % M.cols == 0 && idx >= M.cols) printf("\n");
        }
        printf("\n");
    }
}

/*
   Функция matrix_create создает новую матрицу заданного типа с указанным числом строк и столбцов.
   Возвращает созданную матрицу или MATRIX_NULL в случае ошибки.
   Параметры:
       - rows: количество строк в новой матрице
       - cols: количество столбцов в новой матрице
       - mat_type: тип заполнения матрицы (ZEROS, ONES, RANDOM, IDENTITY)
*/

struct Matrix matrix_create(const size_t rows, const size_t cols, enum MatrixType mat_type) {
    if (rows == 0 && cols == 0) return MATRIX_NULL;

    // Выделение памяти под новую матрицу и заполнение ее значениями
    struct Matrix M = matrix_allocate(rows, cols);

    if (M.data == NULL) return MATRIX_NULL;

    if (rows == 0 || cols == 0) {
        M.rows = rows;
        M.cols = cols;
        M.data = NULL;
        return M;
    }

    matrix_fill(&M, mat_type);

    return M;
}

/*
   Функция matrix_free освобождает память, занятую матрицей M.
   Параметры:
       - M: указатель на структуру матрицы, которую нужно освободить
*/

void matrix_free(struct Matrix *M) {
    if (M->data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(FREE_ERROR);
    } else {
        free(M->data);
        *M = MATRIX_NULL;
    }
}

/*
   Функция matrix_copy копирует содержимое матрицы A в матрицу B.
   Возвращает матрицу B с скопированными данными или MATRIX_NULL в случае ошибки.
   Параметры:
       - A: матрица, из которой нужно скопировать данные
       - B: матрица, в которую нужно скопировать данные
*/

struct Matrix matrix_copy(const struct Matrix A, struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        // Вывод ошибки, если матрицы пустые
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    // Освобождение памяти, занятой матрицей B
    matrix_free(&B);

    // Выделение памяти под матрицу B и копирование данных из матрицы A
    B = matrix_allocate(A.rows, A.cols);
    memcpy(B.data, A.data, B.cols * B.rows * sizeof(matrix_item));

    if (B.data == NULL) {
        // Вывод ошибки, если произошла ошибка при копировании
        matrix_error(COPY_ERROR);
        return MATRIX_NULL;
    }

    return B;
}

/*
   Функция matrix_sum складывает две матрицы A и B и возвращает результат в новой матрице C.
   Если одна из матриц или обе матрицы пустые, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Если размеры матриц A и B не совпадают, функция возвращает MATRIX_NULL и выводит ошибку COLS_ROWS_ERROR.
   Параметры:
       - A: первая матрица
       - B: вторая матрица
   Возвращаемое значение:
       - C: матрица, являющаяся результатом сложения A и B (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_sum(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        // Вывод ошибки, если одна или обе матрицы пустые
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.cols || A.rows != B.rows) {
        // Вывод ошибки, если размеры матриц A и B не совпадают
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    // Создание новой матрицы C для хранения результата
    struct Matrix C = matrix_allocate(A.rows, A.cols);

    if (C.data == NULL) {
        // Вывод ошибки, если не удалось выделить память под матрицу C
        return MATRIX_NULL;
    }

    // Сложение соответствующих элементов матриц A и B и сохранение результата в матрице C
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        C.data[idx] = A.data[idx] + B.data[idx];
    }

    return C;
}

/*
   Функция matrix_subtract вычитает одну матрицу B из другой матрицы A и возвращает результат в новой матрице C.
   Если одна из матриц или обе матрицы пустые, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Если размеры матриц A и B не совпадают, функция возвращает MATRIX_NULL и выводит ошибку COLS_ROWS_ERROR.
   Параметры:
       - A: первая матрица
       - B: вторая матрица
   Возвращаемое значение:
       - C: матрица, являющаяся результатом вычитания B из A (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_subtract(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        // Вывод ошибки, если одна или обе матрицы пустые
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.cols || A.rows != B.rows) {
        // Вывод ошибки, если размеры матриц A и B не совпадают
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    // Создание новой матрицы C для хранения результата
    struct Matrix C = matrix_allocate(A.rows, A.cols);

    if (C.data == NULL) {
        // Вывод ошибки, если не удалось выделить память под матрицу C
        return MATRIX_NULL;
    }

    // Вычитание соответствующих элементов матрицы B из матрицы A и сохранение результата в матрице C
    for (size_t idx = 0; idx < A.cols * A.rows; ++idx) {
        C.data[idx] = A.data[idx] - B.data[idx];
    }

    return C;
}

/*
   Функция matrix_multiply умножает каждый элемент матрицы A на скаляр и возвращает результат в новой матрице B.
   Если матрица A пустая, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Параметры:
       - A: матрица, которую нужно умножить на скаляр
       - scalar: скалярное значение, на которое нужно умножить каждый элемент матрицы
   Возвращаемое значение:
       - B: матрица, являющаяся результатом умножения матрицы A на скаляр (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_multiply(const struct Matrix A, const double scalar) {
    if (A.data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    // Создание новой матрицы B для хранения результата
    struct Matrix B = matrix_allocate(A.rows, A.cols);

    if (B.data == NULL) {
        // Вывод ошибки, если не удалось выделить память под матрицу B
        return MATRIX_NULL;
    }

    // Умножение каждого элемента матрицы A на скаляр и сохранение результата в матрице B
    for (size_t idx = 0; idx < A.rows * A.cols; idx++) {
        B.data[idx] = (matrix_item) scalar * A.data[idx];
    }

    return B;
}

/*
   Функция matrix_product умножает две матрицы A и B и возвращает результат в новой матрице C.
   Если одна из матриц или обе матрицы пустые, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Если количество столбцов матрицы A не равно количеству строк матрицы B, функция возвращает MATRIX_NULL и выводит ошибку COLS_ROWS_ERROR.
   Параметры:
       - A: первая матрица
       - B: вторая матрица
   Возвращаемое значение:
       - C: матрица, являющаяся результатом умножения матрицы A на матрицу B (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_product(const struct Matrix A, const struct Matrix B) {
    if (A.data == NULL || B.data == NULL) {
        // Вывод ошибки, если одна или обе матрицы пустые
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.cols != B.rows) {
        // Вывод ошибки, если количество столбцов матрицы A не равно количеству строк матрицы B
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    // Создание новой матрицы C для хранения результата умножения
    struct Matrix C = matrix_create(A.rows, B.cols, ZEROS);

    if (C.data == NULL) {
        // Вывод ошибки, если не удалось создать матрицу C
        return MATRIX_NULL;
    }

    // Вычисление элементов матрицы C - результат произведения матриц A и B
    for (size_t row_A = 0; row_A < A.rows; row_A++) {
        for (size_t col_B = 0; col_B < B.cols; col_B++) {
            for (size_t idx = 0; idx < A.cols; idx++) {
                C.data[row_A * A.cols + col_B] += A.data[row_A * A.cols + idx] * B.data[idx * B.cols + col_B];
            }
        }
    }

    return C;
}

/*
   Функция matrix_transpose выполняет операцию транспонирования матрицы A и возвращает результат в новой матрице B.
   Если матрица A пустая, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Параметры:
       - A: исходная матрица, которую необходимо транспонировать
   Возвращаемое значение:
       - B: матрица, являющаяся результатом транспонирования матрицы A (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_transpose(const struct Matrix A) {
    if (A.data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    // Создание новой матрицы B для хранения результата транспонирования
    struct Matrix B = matrix_allocate(A.cols, A.rows);

    if (B.data == NULL) {
        // Вывод ошибки, если не удалось выделить память под матрицу B
        return MATRIX_NULL;
    }

    // Выполнение операции транспонирования матрицы A и сохранение результата в матрице B
    for (size_t row = 0; row < A.rows; row++) {
        for (size_t col = 0; col < A.cols; col++) {
            B.data[col * A.rows + row] = A.data[row * A.cols + col];
        }
    }

    return B;
}

/*
   Функция matrix_det вычисляет определитель квадратной матрицы A.
   Если матрица A пустая, функция возвращает NAN и выводит ошибку BAD_MATRIX_ERROR.
   Если количество столбцов не равно количеству строк, функция возвращает NAN и выводит ошибку COLS_ROWS_ERROR.
   Параметры:
       - A: квадратная матрица, для которой необходимо вычислить определитель
   Возвращаемое значение:
       - Определитель матрицы A, если размерность не превышает 3 (для больших размерностей необходимо использовать другой метод),
       - NAN в случае ошибки
*/

double matrix_det(const struct Matrix A) {
    if (A.data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(BAD_MATRIX_ERROR);
        return NAN;
    }

    if (A.cols != A.rows) {
        // Вывод ошибки, если количество столбцов не равно количеству строк
        matrix_error(COLS_ROWS_ERROR);
        return NAN;
    }

    if (A.cols == 1) {
        // Определитель матрицы 1x1 равен единственному элементу матрицы
        return (double) A.data[0];
    } else if (A.cols == 2) {
        // Определитель матрицы 2x2 рассчитывается по формуле ad - bc
        return (double) (A.data[0] * A.data[3] - A.data[1] * A.data[2]);
    } else if (A.cols == 3) {
        // Определитель матрицы 3x3 рассчитывается по формуле Sarrus' rule
        return (double) (A.data[0] * A.data[4] * A.data[8]) +
            (A.data[1] * A.data[5] * A.data[6]) +
            (A.data[2] * A.data[3] * A.data[7]) -
            (A.data[2] * A.data[4] * A.data[6]) -
            (A.data[0] * A.data[5] * A.data[7]) -
            (A.data[1] * A.data[3] * A.data[8]);
    }

    // Вывод ошибки, если размерность матрицы превышает 3
    matrix_error(DET_ERROR);
    return NAN;
}

/*
   Функция matrix_exp вычисляет экспоненту матрицы A в степени n и возвращает результат в новой матрице.
   Если матрица A пустая, функция возвращает MATRIX_NULL и выводит ошибку BAD_MATRIX_ERROR.
   Если матрица A не является квадратной, функция возвращает MATRIX_NULL и выводит ошибку COLS_ROWS_ERROR.
   Параметры:
       - A: исходная матрица
       - n: степень, в которую необходимо возвести матрицу
   Возвращаемое значение:
       - Результат экспоненциации матрицы A в степени n (или MATRIX_NULL в случае ошибки)
*/

struct Matrix matrix_exp(const struct Matrix A, const unsigned int n) {
    if (A.data == NULL) {
        // Вывод ошибки, если матрица пустая
        matrix_error(BAD_MATRIX_ERROR);
        return MATRIX_NULL;
    }

    if (A.rows != A.cols) {
        // Вывод ошибки, если матрица не квадратная
        matrix_error(COLS_ROWS_ERROR);
        return MATRIX_NULL;
    }

    // Создание матрицы-экспоненты и матрицы-слагаемого, и выделение памяти под временную матрицу
    struct Matrix exponent = matrix_create(A.rows, A.cols, IDENTITY);
    struct Matrix summand = matrix_create(A.rows, A.cols, IDENTITY);
    struct Matrix temp = matrix_allocate(A.rows, A.cols);
    if (exponent.data == NULL || summand.data == NULL || temp.data == NULL) {
        // Освобождение памяти и возврат ошибки, если не удалось выделить память
        matrix_free(&exponent);
        matrix_free(&summand);
        matrix_free(&temp);
        return MATRIX_NULL;
    }

    if (n == 0) {
        // Возврат единичной матрицы, если степень равна 0
        return exponent;
    }

    if (n == 1) {
        // Вычисление экспоненты матрицы A и возврат результата
        temp = matrix_sum(exponent, A);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, exponent);
        matrix_free(&summand);
        matrix_free(&temp);
        return exponent;
    }

    // Вычисление экспоненты матрицы A в степени n
    for (unsigned int idx = 1; idx <= n; idx++) {
        temp = matrix_product(summand, A);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, summand);
        matrix_free(&temp);

        temp = matrix_multiply(summand, 1. / idx);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, summand);
        matrix_free(&temp);

        temp = matrix_sum(exponent, summand);
        if (temp.data == NULL) {
            matrix_free(&exponent);
            matrix_free(&summand);
            matrix_free(&temp);
            return MATRIX_NULL;
        }
        matrix_copy(temp, exponent);
        matrix_free(&temp);
    }

    matrix_free(&summand);

    return exponent;
}