#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
	double *data;
	int rows, columns;
} Matrix;

// create
int matrix_init(Matrix *m, int rows, int columns);

// compute_idx
int matrix_compute_idx(Matrix *m, int row, int column);

// set index (takes two ints, x and y)
int matrix_set_index(Matrix *m, int row, int column, double data);

/*
NOTE: for the set functions below, consider adding a check to see 
if the provided data array matches the matrix row / column length
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

// add
// add const

// subtract
// subtract const

// invert

// determinat

// rotate

// transpose

// identity
int matrix_set_identity(Matrix *m);

// clone
int matrix_copy(Matrix *m, Matrix *dest);

// map
void matrix_map(Matrix *m, double (*func)(double, int, int));

// randomize

// free
void matrix_free(Matrix *m);

#endif