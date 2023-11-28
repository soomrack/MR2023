#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вывода сообщения об ошибке
void errorMsg(const char *errorMessage) {
    fprintf(stderr, "%s\n", errorMessage);
}

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix; 

// Функция для создания матрицы
Matrix create_matrix(int rows, int cols) {
    Matrix A;
    A.rows = rows;
    A.cols = cols;
    
    A.data = (double **)malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (!A.data) {
        return errorMsg("Ошибка выделения памяти для матрицы.");
    }
    
    return A;
}

// Функция для освобождения памяти, выделенной под матрицу
void free_matrix(Matrix A) {
    for (int row = 0; row < A.rows; row++) {
        free(A.data[row]);
    }
    free(A.data);
}

// Функция для вывода матрицы на экран
void print_matrix(Matrix A) {
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            printf("%lf\t", A.data[row][col]);
        }
        printf("\n");
    }
}

// Функция для сложения двух матриц
Matrix sum(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("Ошибка: Размеры матриц не совпадают\n");
        return NAN;
    } // функция нулл матрикс
    
    int matrix_is_null(int **matrix, int rows, int cols) {
    if (matrix == NULL) {
        return 0; // Матрица не существует
    }
 
    Matrix result = create_matrix(A.rows, B.cols);
    // проверять существование тут
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] + B.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычитания двух матриц
Matrix sub(Matrix A, Matrix B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        printf("Ошибка: Размеры матриц не совпадают\n");
        return NAN;
    }
    
    Matrix result = create_matrix(A.rows, A.cols);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = A.data[row][col] - B.data[row][col];
        }
    }
    
    return result;
}

// Функция для умножения двух матриц
Matrix mult(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        printf("Ошибка: Невозможно умножить матрицы\n");
        return NAN;
    }
    
    Matrix result = create_matrix(A.rows, B.cols);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < B.cols; col++) {
            result.data[row][col] = 0;
            for (int k = 0; k < A.cols; k++) {
                result.data[row][col] += A.data[row][k] * B.data[k][col];
            }
        }
    }
    
    return result;
}

// Функция для транспонирования матрицы
Matrix tr(Matrix A) {
    Matrix result = create_matrix(A.cols, A.rows);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {
            result.data[col][row] = A.data[row][col];
        }
    }
    
    return result;
}

// Функция для вычисления детерминанта матрицы (простой метод для квадратных матриц)
double det(Matrix A) {
    if (A.rows != A.cols) {
        printf("Ошибка: Матрица не является квадратной\n");
        return NAN;
    }
    
    if (A.rows == 1) {
        return A.data[0][0];
    }
    
    if (A.rows == 2) {
        return A.data[0][0] * A.data[1][1] - A.data[0][1] * A.data[1][0];
    }
    
    double determinant = 0;
    for (int col = 0; col < A.cols; col++) {
        Matrix submat = create_matrix(A.rows - 1, A.cols - 1);
        for (int row = 1; row < A.rows; row++) {
            for (int k = 0; k < A.cols; k++) {
                if (k < col) {
                    submat.data[row - 1][k] = A.data[row][k];
                } else if (k > col) {
                    submat.data[row - 1][k - 1] = A.data[row][k];
                }
            }
        }
        determinant += A.data[0][col] * det(submat) * (col % 2 == 0 ? 1 : -1);
        free_matrix(submat);
    }
    
    return determinant;
}

// Функция для вычисления экспоненты матрицы (простой метод для квадратных матриц)
Matrix A_exp(Matrix A, int n) {
    if (A.rows != A.cols) {
        printf("Ошибка: Матрица не является квадратной\n");
        return NAN;
    }
    
    Matrix result = create_matrix(A.rows, A.cols);
    Matrix temp = create_matrix(A.rows, A.cols);
    
    for (int row = 0; row < A.rows; row++) {
        for (int col = 0; col < A.cols; col++) {             
            if (row == col) {
                result.data[row][col] = 1;
                temp.data[row][col] = A.data[row][col];
            } else {
                result.data[row][col] = 0;
                temp.data[row][col] = 0;
            }
        }
    }
    
   for (int k = 1; k <= n; k++) {
        for (int row = 0; row < A.rows; row++) {
            for (int col = 0; col < A.cols; col++) {
                for (int p = 0; p < A.cols; p++) {
                    temp->data[row][col] += (A.data[row][p] * result->data[p][col]);
                }
            }
        }
        Matrix temp2 = result;
        result = temp;
        temp = temp2;
    }
    
    free_matrix(temp);
    
    return result;
}
