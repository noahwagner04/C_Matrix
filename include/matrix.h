#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
	double *data;
	int rows, columns;
} Matrix;

// create
int matrix_init(Matrix *m, int rows, int columns);

// compute_idx
int matrix_compute_idx(Matrix *m, int column, int row);

// set data (takes 2d array)
void matrix_set_data(Matrix *m, double data[m->rows][m->columns]);

// set row (takes 1d array and index)
int matrix_set_row(Matrix *m, int row, double *data);

// set column (takes 1d array and index)
int matrix_set_column(Matrix *m, int column, double *data);

// set index (takes two ints, x and y)
int matrix_set_index(Matrix *m, int row, int column, double data);


// get index
double matrix_get_index(Matrix *m, int row, int column);

// MAYBE ADD THESE
// add row
// add column
// remove row
// remove column

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

// clone

// map

// randomize

// free
void matrix_free(Matrix *m);

#endif