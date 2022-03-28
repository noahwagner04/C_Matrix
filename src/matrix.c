#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define DATA_AT(m, r, c) m->data[matrix_compute_idx(m, r, c)]

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

// returns 0 if the matrix is not square, returns 1 if it is
int matrix_check_square(Matrix *m) {
	if (m->rows != m->columns) return 0;
	return 1;
}

// returns 0 if the matrix is not null, returns 1 if it is
int matrix_check_null(Matrix *m) {
	if (m->data != NULL) return 0;
	return 1;
}

// returns 0 if rows and columns do not match m's dimentions, returns 1 if they do
int matrix_check_dim(Matrix *m, int rows, int columns) {
	if (m->rows != rows || m->columns != columns) return 0;
	return 1;
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
	if (!matrix_check_square(m)) return -1;

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

// multiply
int matrix_multiply(Matrix *m1, Matrix *m2, Matrix *dest) {
	if (m2->rows != m1->columns) return -1;

	if (matrix_check_null(dest)) {
		int result = matrix_init(dest, m1->rows, m2->columns);

		if (result == -1) return -1;
	} else if (!matrix_check_dim(dest, m1->rows, m2->columns)) {
		return -1;
	}

	for (int r = 0; r < m1->rows; ++r) {
		for (int c = 0; c < m2->columns; ++c) {
			double result = 0;
			for (int i = 0; i < m1->columns; ++i) {
				result += DATA_AT(m1, r, i) * DATA_AT(m2, i, c);
			}
			matrix_set_index(dest, r, c, result);
		}
	}

	return 0;
}

// multiply scalar
void matrix_multiply_scalar(Matrix *m, double scalar) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			DATA_AT(m, r, c) *= scalar;
		}
	}
}

// add
int matrix_add(Matrix *m1, Matrix *m2) {
	if (!matrix_check_dim(m1, m2->rows, m2->columns)) return -1;
	for (int r = 0; r < m1->rows; ++r) {
		for (int c = 0; c < m1->columns; ++c) {
			DATA_AT(m1, r, c) += DATA_AT(m2, r, c);
		}
	}
	return 0;
}

// add const
void matrix_add_const(Matrix *m, double c) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			DATA_AT(m, r, c) += c;
		}
	}
}

// subtract
int matrix_subtract(Matrix *m1, Matrix *m2) {
	if (!matrix_check_dim(m1, m2->rows, m2->columns)) return -1;
	for (int r = 0; r < m1->rows; ++r) {
		for (int c = 0; c < m1->columns; ++c) {
			DATA_AT(m1, r, c) -= DATA_AT(m2, r, c);
		}
	}
	return 0;
}

// subtract const
void matrix_subtract_const(Matrix *m, double c) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			DATA_AT(m, r, c) -= c;
		}
	}
}

/*
copies the contents of the first matrix to a desitination matrix
destination matrix can be uninitialized or already initialized
if dest is not initialized, initialize it and return -1 if initialization fails
if dest is initialized, return -1 if its dimentions do not match m's
return 0 on success
*/
int matrix_copy(Matrix *m, Matrix *dest) {
	if (matrix_check_null(dest)) {
		int init_result = matrix_init(dest, m->rows, m->columns);

		if (init_result == -1) return -1;
	} else if (!matrix_check_dim(dest, m->rows, m->columns)) {
		return -1;
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
			matrix_set_index(m, r, c, func(DATA_AT(m, r, c), r, c));
		}
	}
}

// frees the memory allocated by the matrix
void matrix_free(Matrix *m) {
	memset(m, 0, sizeof(Matrix));
	free(m->data);
}