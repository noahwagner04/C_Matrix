#include <stdlib.h>
#include <string.h>
#include "matrix.h"

/*
initializes the matrix, returns -1 if the rows or columns specified are invalid, or if allocation fails
all members of the matrix will be initialized to 0 if initialization failed
returns 0 if initialization was successful
*/
int matrix_init(Matrix *m, int rows, int columns) {
	memset(m, 0, sizeof(Matrix));

	if (rows < 0 || columns < 0) return -1;

	m->data = malloc(sizeof(double) * rows * columns);

	if (m->data == NULL) return -1;

	m->rows = rows;
	m->columns = columns;

	return 0;
}

/*
computes the 1d index from a 2d coordinate (column, row)
if the provided row or column is out of the matrix range, return -1
*/
int matrix_compute_idx(Matrix *m, int row, int column) {
	if (row > m->rows - 1 || row < 0) return -1;

	if (column > m->columns - 1 || column < 0) return -1;

	return row * m->columns + column;
}

/*
sets the data at (row, column) to the specified number
returns -1 if row or column is out of range, and 0 on success
*/
int matrix_set_index(Matrix *m, int row, int column, double data) {
	int index = matrix_compute_idx(m, row, column);

	if (index == -1) return -1;

	m->data[index] = data;

	return 0;
}

// copies the contents of a 2d array to the matrix (data array must be the same size as [m->rows][m->columns])
void matrix_set_data(Matrix *m, double data[m->rows][m->columns]) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			matrix_set_index(m, r, c, data[r][c]);
		}
	}
}

/*
sets the data at row to the specified array
returns -1 if row is out of range, and 0 on success
*/
int matrix_set_row(Matrix *m, int row, double *data) {
	for (int c = 0; c < m->columns; ++c) {
		int set_result = matrix_set_index(m, row, c, data[c]);

		if (set_result == -1) return -1;
	}

	return 0;
}

/*
sets the data at column to the specified array
returns -1 if column is out of range, and 0 on success
*/
int matrix_set_column(Matrix *m, int column, double *data) {
	for (int r = 0; r < m->rows; ++r) {
		int set_result = matrix_set_index(m, r, column, data[r]);

		if (set_result == -1) return -1;
	}

	return 0;
}

/*
sets the provided square matrix to an identity matrix
returns -1 if the provided matrix isn't square
returns 0 otherwise
*/
int matrix_set_identity(Matrix *m) {
	if (m->rows != m->columns) return -1;

	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			if (c == r) {
				matrix_set_index(m, r, c, 1);
			} else {
				matrix_set_index(m, r, c, 0);
			}
		}
	}

	return 0;
}

/*
copies the contents of the first matrix to a desitination matrix
destination matrix can be uninitialized or already initialized
if dest is not initialized, initialize it and return -1 if initialization fails
if dest is initialized, return -1 if its dimentions do not match m's
return 0 on success
*/
int matrix_copy(Matrix *m, Matrix *dest) {
	if (dest->data == NULL) {
		int init_result = matrix_init(dest, m->rows, m->columns);

		if (init_result == -1) return -1;
	} else {
		if (m->rows != dest->rows || m->columns != dest->columns) return -1;
	}

	memcpy(dest->data, m->data, m->rows * m->columns * sizeof(double));

	return 0;
}

/*
run a function on every index of the matrix, the function takes three arguments, 
the data at the current index, and the current row and column being evaluated
*/
void matrix_map(Matrix *m, double (*func)(double, int, int)) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			matrix_set_index(m, r, c, func(m->data[matrix_compute_idx(m, r, c)], r, c));
		}
	}
}

// frees the memory allocated by the matrix
void matrix_free(Matrix *m) {
	memset(m, 0, sizeof(Matrix));
	free(m->data);
}