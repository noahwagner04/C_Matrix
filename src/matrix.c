#include <stdio.h> // only used for matrix_print function, remove when done with library
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

#define DATA_AT(m, r, c) ( (m)->data[matrix_compute_idx(m, r, c)] )

/*
initializes the matrix, returns -1 if the rows or columns specified are invalid, or if allocation fails
all members of the matrix will be initialized to 0 if initialization failed
returns 0 if initialization was successful

NOTE: maybe disallow matricies to have 0 rows or columns
(although free(NULL) doesn't do anything so..., AND every function works with 0x0 matricies)
*/
int matrix_init(Matrix *m, int rows, int columns) {
	// incase allocation fails, the contents of the matrix will be all 0's
	memset(m, 0, sizeof(Matrix));

	if (rows < 0 || columns < 0) return -1;

	m->data = malloc(sizeof(double) * rows * columns);

	if (m->data == NULL) return -1;

	m->rows = rows;
	m->columns = columns;

	return 0;
}

/*
frees the current memory taken by the matrix, and
reinitializes the matrix with new amount of rows and columns
*/
int matrix_reset(Matrix *m, int rows, int columns) {
	matrix_free(m);

	int init_result = matrix_init(m, rows, columns);

	if (init_result == -1) return -1;

	return 0;
}

// returns 0 if the matrix is not square, returns 1 if it is
int matrix_check_square(Matrix *m) {
	if (m->rows != m->columns) return 0;
	return 1;
}

// returns 0 if the matrix is not null, returns 1 if it is
// NOTE: maybe remove, i don't use this
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

int matrix_set_rotation_3d(Matrix *m, double roll, double pitch, double yaw) {
	if (!matrix_check_dim(m, 3, 3)) return -1;

	double s_r = sin(roll);
	double c_r = cos(roll);

	double s_p = sin(pitch);
	double c_p = cos(pitch);

	double s_y = sin(yaw);
	double c_y = cos(yaw);

	double data[3][3] = {
		{c_p * c_y, s_r * s_p * c_y - c_r * s_y, c_r * s_p * c_y + s_r * s_y},
		{c_p * s_y, s_r * s_p * s_y + c_r * c_y, c_r * s_p * s_y - s_r * c_y},
		{ -s_p, s_r * c_p, c_r * c_p}
	};

	matrix_set_data(m, data);

	return 0;
}

int matrix_set_rotation_2d(Matrix *m, double angle) {
	if (!matrix_check_dim(m, 2, 2)) return -1;

	double s = sin(angle);
	double c = cos(angle);

	double data[2][2] = {
		{c, -s},
		{s, c}
	};

	matrix_set_data(m, data);

	return 0;
}

int matrix_set_roll(Matrix *m, double roll) {
	if (!matrix_check_dim(m, 3, 3)) return -1;

	double s = sin(roll);
	double c = cos(roll);

	double data[3][3] = {
		{1, 0, 0},
		{0, c, -s},
		{0, s, c}
	};

	matrix_set_data(m, data);

	return 0;
}

int matrix_set_pitch(Matrix *m, double pitch) {
	if (!matrix_check_dim(m, 3, 3)) return -1;

	double s = sin(pitch);
	double c = cos(pitch);

	double data[3][3] = {
		{c, 0, s},
		{0, 1, 0},
		{ -s, 0, c}
	};

	matrix_set_data(m, data);

	return 0;
}

int matrix_set_yaw(Matrix *m, double yaw) {
	if (!matrix_check_dim(m, 3, 3)) return -1;

	double s = sin(yaw);
	double c = cos(yaw);

	double data[3][3] = {
		{c, -s, 0},
		{s, c, 0},
		{0, 0, 1}
	};

	matrix_set_data(m, data);

	return 0;
}

// multiply
int matrix_multiply(Matrix *m1, Matrix *m2, Matrix *dest) {
	if (m2->rows != m1->columns) return -1;

	Matrix temp;

	matrix_init(&temp, m1->rows, m2->columns);

	for (int r = 0; r < m1->rows; ++r) {
		for (int c = 0; c < m2->columns; ++c) {
			double result = 0;
			for (int i = 0; i < m1->columns; ++i) {
				result += DATA_AT(m1, r, i) * DATA_AT(m2, i, c);
			}
			matrix_set_index(&temp, r, c, result);
		}
	}

	int copy_result = matrix_copy(&temp, dest);

	matrix_free(&temp);

	if (copy_result == -1) return -1;

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
void matrix_add_const(Matrix *m, double n) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			DATA_AT(m, r, c) += n;
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
void matrix_subtract_const(Matrix *m, double n) {
	for (int r = 0; r < m->rows; ++r) {
		for (int c = 0; c < m->columns; ++c) {
			DATA_AT(m, r, c) -= n;
		}
	}
}

int matrix_calc_determinant(Matrix *m, double *dest) {
	if (!matrix_check_square(m)) return -1;

	// if the matrix is 2x2, run calc_determinant_2x2 and return
	if (matrix_check_dim(m, 2, 2)) return matrix_calc_determinant_2x2(m, dest);

	double terms_array[m->rows];

	// for every element in the first row of the matrix...
	for (int i = 0; i < m->rows; ++i) {
		// make a temp matrix whose dimentions are m->rows - 1 and m-> columns - 1
		Matrix temp;
		double data[m->rows - 1][m->columns - 1];
		int add_one = 0;

		// initialize the temp matrix, ignoring the rows and columns that the element at index (0, i) is in
		for (int r = 0; r < m->rows - 1; ++r) {
			for (int c = 0; c < m->columns - 1; ++c)
			{
				if (c == i) add_one = 1;

				if (add_one) {
					data[r][c] = DATA_AT(m, r + 1, c + 1);
				} else {
					data[r][c] = DATA_AT(m, r + 1, c);
				}
			}
			add_one = 0;
		}

		// finish initializing the temp matrix
		matrix_init(&temp, m->rows - 1, m->columns - 1);
		matrix_set_data(&temp, data);

		// calculate the determinant of the temp matrix
		matrix_calc_determinant(&temp, dest);

		// multiply the calculated determinant above with the element at m, index (0, i), add it to an array of algebraic terms
		terms_array[i] = DATA_AT(m, 0, i) * *dest;

		// free the temporary matrix
		matrix_free(&temp);
	}

	// the final calculated determanent
	double det = 0;

	// for every element added to the array of terms...
	for (int i = 0; i < m->rows; ++i) {
		// add or subtract them in an alternating fashion
		if (i % 2 == 0) {
			det += terms_array[i];
		} else {
			det -= terms_array[i];
		}
	}

	*dest = det;

	return 0;
}

// determinant of a 2d matrix
int matrix_calc_determinant_2x2(Matrix *m, double *dest) {
	if (!matrix_check_dim(m, 2, 2)) return -1;

	*dest = DATA_AT(m, 0, 0) * DATA_AT(m, 1, 1) - DATA_AT(m, 0, 1) * DATA_AT(m, 1, 0);

	return 0;
}

// determinant of a 3d matrix
int matrix_calc_determinant_3x3(Matrix *m, double *dest) {
	if (!matrix_check_dim(m, 3, 3)) return -1;

	*dest = DATA_AT(m, 0, 0) * (DATA_AT(m, 1, 1) * DATA_AT(m, 2, 2) - DATA_AT(m, 1, 2) * DATA_AT(m, 2, 1)) -
	        DATA_AT(m, 0, 1) * (DATA_AT(m, 1, 0) * DATA_AT(m, 2, 2) - DATA_AT(m, 1, 2) * DATA_AT(m, 2, 0)) +
	        DATA_AT(m, 0, 2) * (DATA_AT(m, 1, 0) * DATA_AT(m, 2, 1) - DATA_AT(m, 1, 1) * DATA_AT(m, 2, 0));

	return 0;
}

int matrix_transpose(Matrix *m, Matrix *dest) {
	Matrix temp;

	matrix_init(&temp, m->columns, m->rows);

	for (int r = 0; r < temp.rows; ++r) {
		for (int c = 0; c < temp.columns; ++c) {
			DATA_AT(&temp, r, c) = DATA_AT(m, c, r);
		}
	}

	int copy_result = matrix_copy(&temp, dest);

	matrix_free(&temp);

	if (copy_result == -1) return -1;

	return 0;
}

/*
copies the contents of the first matrix to a desitination matrix
if the desitnation matrix doesn't have the same dimentions as the source matrix,
reset the matrix to have the correct dimentions, and return -1 if the reset fails
return 0 on success
*/
int matrix_copy(Matrix *m, Matrix *dest) {
	if (!matrix_check_dim(dest, m->rows, m->columns)) {
		int reset_result = matrix_reset(dest, m->rows, m->columns);

		if (reset_result == -1) return -1;
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
	free(m->data);
	memset(m, 0, sizeof(Matrix));
}

// print the matrix to the terminal, maybe remove after done with library
void matrix_print(Matrix *m) {
	printf("{\n");
	for (int r = 0; r < m->rows; ++r) {
		printf("{");
		for (int c = 0; c < m->columns; ++c) {
			if (c == m->columns - 1) {
				printf("%f ", DATA_AT(m, r, c));
				continue;
			}
			printf("%f, ", DATA_AT(m, r, c));
		}
		printf("}\n");
	}
	printf("}\n");
}