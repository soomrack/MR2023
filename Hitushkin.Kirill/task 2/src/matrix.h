

typedef double MatrixItem;

typedef struct
{
    size_t rows;
    size_t cols;
    MatrixItem* items;
} Matrix;


Matrix matrix_allocate(const size_t rows, const size_t cols);

void matrix_set_items(const Matrix mat, const double *values);

void matrix_set_null(const Matrix mat);

void matrix_set_one(const Matrix mat);

double* matrix_get_element(const Matrix mat, const size_t row, const size_t col);

void matrix_del(Matrix *mat);

Matrix matrix_sum(const Matrix a, const Matrix b);

void matrix_add_to(const Matrix a, const  Matrix b);

void matrix_sub_from(const Matrix a, const  Matrix b);

Matrix matrix_sub(const Matrix a, const  Matrix b);

void matrix_mult_to(const Matrix target_mat, const Matrix a, const Matrix b);

Matrix matrix_mult(const Matrix a, const Matrix b);

Matrix tran_matrix(const Matrix a);

double matrix_det(const Matrix mat_one);

void matrix_scalar_mult(const Matrix mat, const double factor);

Matrix matrix_expm(const Matrix a, const double accuracy);

int compare_matrix(const Matrix one, const Matrix two);

void print_matrix(const Matrix mat);
