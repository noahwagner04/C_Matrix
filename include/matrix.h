#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
	double *data;
	int rows, columns;
} Matrix;

// create

// set data (takes 2d array)
// set row (takes 1d array and index)
// set column (takes 1d array and index)
// set index (takes two ints, x and y)

// (MAYBE HAVE THESE) 
// NOTE: return pointers to newly allocated space of the row / column
// NOTE: the user would have to free the space allocated by these functions, maybe add column_free() and row_free() funcs
// get row
// get column
// get index

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
#endif