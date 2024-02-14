

typedef double MatrixItem;

typedef struct
{
    size_t rows;
    size_t cols;
    MatrixItem* items;
} Matrix;


Matrix matrix_allocate(const size_t rows, const size_t cols);

void matrix_set_items(const Matrix mat, const double *values);

void matrix_set_zero(const Matrix mat);

void matrix_set_one(const Matrix mat);

double* matrix_get_element(const Matrix mat, const size_t row, const size_t col);

void matrix_del(Matrix *mat);

Matrix matrix_sum(const Matrix a, const Matrix b);

void matrix_add_to(const Matrix a, const  Matrix b);

void matrix_sub_from(const Matrix a, const  Matrix b);

Matrix matrix_sub(const Matrix a, const  Matrix b);

void matrix_mult_to(const Matrix target_mat, const Matrix a, const Matrix b);

Matrix matrix_mult(const Matrix a, const Matrix b);

Matrix matrix_tran(const Matrix a);

double matrix_det(const Matrix mat_one);

void matrix_scalar_mult(const Matrix mat, const double factor);

double max_matrix(const Matrix mat);

Matrix matrix_expm(const Matrix a, const double accuracy);

int matrix_compare(const Matrix one, const Matrix two);

void matrix_print(const Matrix mat);
