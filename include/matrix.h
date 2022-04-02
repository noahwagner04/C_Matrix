#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
	double *data;
	int rows, columns;
} Matrix;

// matrix check fucntions
int matrix_check_square(Matrix *m);
int matrix_check_null(Matrix *m);
int matrix_check_dim(Matrix *m, int rows, int columns);

// create
int matrix_init(Matrix *m, int rows, int columns);

// reset a matrix
int matrix_reset(Matrix *m, int rows, int columns);

// compute_idx
int matrix_compute_idx(Matrix *m, int row, int column);

// set index (takes two ints, x and y)
int matrix_set_index(Matrix *m, int row, int column, double data);

/*
NOTE: for the set functions below, consider adding a check to see 
if the provided data array matches the matrix row / column length
use sizeof
*/

// set data (takes 2d array)
void matrix_set_data(Matrix *m, double data[m->rows][m->columns]);

// set row (takes 1d array and index)
int matrix_set_row(Matrix *m, int row, double *data);

// set column (takes 1d array and index)
int matrix_set_column(Matrix *m, int column, double *data);

/*
MAYBE ADD THESE
NOTE: each function copies the data at the specified location to a desitination pointer
get index(matrix, dest, row, column)
get row(matrix, dest array, row)
get colum(matrix, dest array, column)
get data(matrix, dest 2d array)

MAYBE ADD THESE
add row
add column
remove row
remove column
*/

// NOTE: add these when adding invert funcs
// muliply row by const
// add multiple of row

// multiply
int matrix_multiply(Matrix *m1, Matrix *m2, Matrix *dest);

// multiply scalar
void matrix_multiply_scalar(Matrix *m, double scalar);

// add
int matrix_add(Matrix *m1, Matrix *m2);

// add const
void matrix_add_const(Matrix *m, double n);

// subtract
int matrix_subtract(Matrix *m1, Matrix *m2);

// subtract const
void matrix_subtract_const(Matrix *m, double n);

// NOTE: make invert take a destination matrix, just like matrix_multiply 
// also, make it possible to make the input matrix the destination
// invert

// determinat

// rotation matricies
int matrix_set_rotation_3d(Matrix *m, double pitch, double yaw, double roll);

int matrix_set_rotation_2d(Matrix *m, double angle);

int matrix_set_yaw(Matrix *m, double yaw);

int matrix_set_pitch(Matrix *m, double pitch);

int matrix_set_roll(Matrix *m, double roll);

// transpose
int matrix_transpose(Matrix *m, Matrix *dest);

// identity
int matrix_set_identity(Matrix *m);

// clone
int matrix_copy(Matrix *m, Matrix *dest);

// map
void matrix_map(Matrix *m, double (*func)(double, int, int));

// free
void matrix_free(Matrix *m);

// write a temporary show function (for debuging purposes), maybe keep it?
void matrix_print(Matrix *m);

#endif