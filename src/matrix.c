#include <stdlib.h>
#include <string.h>
#include "matrix.h"

/*
initializes the matrix, returns -1 if the rows or columns specified are invalid, or if allocation fails
all members of the matrix will be initialized to 0 if initiation failed
returns 0 if initiation was successful
*/
int matrix_init(Matrix *m, int rows, int columns) {
	memset(m, 0, sizeof(Matrix));

	if (rows < 0 || columns < 0) return -1;

	m->data = malloc(sizeof(double) * rows * columns);

	if (m->data == NULL) return -1;

	m->rows = rows;
	m->columns = rows;

	return 0;
}

// computes the 1d index from a 2d coordinate (column, row)
int matrix_compute_idx(Matrix *m, int column, int row) {
	return row * m->columns + column;
}

// copies the contents of a 2d array to the matrix (data array must be the same size as [m->rows][m->columns])
void matrix_set_data(Matrix *m, double data[m->rows][m->columns]) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			m->data[matrix_compute_idx(m, c, r)] = data[r][c];
		}
	}
}

// int matrix_set_row(Matrix *m, int row, double *data) {

// }

// int matrix_set_column(Matrix *m, int column, double *data) {

// }

// int matrix_set_index(Matrix *m, int row, int column) {

// }


// double matrix_get_index(Matrix *m, int row, int column) {

// }

// void matrix_free(Matrix *m) {

// }