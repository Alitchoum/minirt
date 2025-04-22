#include "minirt.h"

int	matrix_are_equal(double **a, double **b, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (!is_equal(a[i][j], b[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	mat4_multiply(double result[4][4], double a[4][4], double b[4][4])
{
	int	row;
	int	col;
	int	k;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result[row][col] = 0;
			k = 0;
			while (k < 4)
			{
				result[row][col] += a[row][k] * b[k][col];
				k++;
			}
			col++;
		}
		row++;
	}

}

t_tuple	mat4_multiply_tuple(double mat[4][4], t_tuple tup)
{
	t_tuple	result;

	result.x = mat[0][0] * tup.x + mat[0][1] * tup.y + mat[0][2] * tup.z + mat[0][3] * tup.w;
	result.y = mat[1][0] * tup.x + mat[1][1] * tup.y + mat[1][2] * tup.z + mat[1][3] * tup.w;
	result.z = mat[2][0] * tup.x + mat[2][1] * tup.y + mat[2][2] * tup.z + mat[2][3] * tup.w;
	result.w = mat[3][0] * tup.x + mat[3][1] * tup.y + mat[3][2] * tup.z + mat[3][3] * tup.w;
	return (result);
}

// IDENTITY MATRIX -- WHERE SHOULD I STORE?
// matrixA * identity matrix == matrixA
// identity matrix * tupleA == tupleA
void	set_identity_matrix(double matrix[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				matrix[i][j] = 1.0;
			else
				matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

// TRANSPPOSE MATRIX --> columns become rows
void	transpose_matrix(double matrix[4][4], double result[4][4])
{
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result[col][row] = matrix[row][col];
			col++;
		}
		row++;
	}
}


// If determinant is 0, no solution
double	determinant_mat2(double matrix[2][2])
{
	return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
}

void	submatrix_4_3(double from[4][4], double to[3][3], int row_del, int col_del)
{
	int	r;
	int	c;
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if (i == row_del)
			continue;
		c = 0;
		j = 0;
		while (j < 4)
		{
			if (j == col_del)
				continue;
			to[r][c] = from[i][j];
			c++;
			j++;
		}
		r++;
		i++;

	}
}

void	submatrix_3_2(double from[3][3], double to[2][2], int row_del, int col_del)
{
	int	r;
	int	c;
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (i == row_del)
			continue;
		c = 0;
		j = 0;
		while (j < 3)
		{
			if (j == col_del)
				continue;
			to[r][c] = from[i][j];
			c++;
			j++;
		}
		r++;
		i++;

	}
}

double	minor_mat3(double old[3][3], int row, int col)
{
	double new[2][2];

	submatrix_3_2(old, new, row, col);
	return (determinant_mat2(new));
}

// COFACTOR CALCULATIONS, 3 X 3
// +  -  +
// -  +  -
// +  -  +
double	cofactor_mat3(double matrix[3][3], int row, int col)
{
	if ((row + col) % 2 != 0) // if row + column is odd, change the sign of the minor
		return (-minor_mat3(matrix, row, col));
	else
		return (minor_mat3(matrix, row, col));
}

//double	determinant_generic(double matrix[3][3])
