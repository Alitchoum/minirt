#include "minirt.h"

int	matrix_are_equal(t_matrix a, t_matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (!is_equal(a.m[i][j], b.m[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	mat4_multiply(t_matrix *result, t_matrix a, t_matrix b)
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
			result->m[row][col] = 0;
			k = 0;
			while (k < 4)
			{
				result->m[row][col] += a.m[row][k] * b.m[k][col];
				k++;
			}
			col++;
		}
		row++;
	}

}

t_tuple	mat4_multiply_tuple(t_matrix matrix, t_tuple tup)
{
	t_tuple	result;

	result.x = matrix.m[0][0] * tup.x + matrix.m[0][1] * tup.y + matrix.m[0][2] * tup.z + matrix.m[0][3] * tup.w;
	result.y = matrix.m[1][0] * tup.x + matrix.m[1][1] * tup.y + matrix.m[1][2] * tup.z + matrix.m[1][3] * tup.w;
	result.z = matrix.m[2][0] * tup.x + matrix.m[2][1] * tup.y + matrix.m[2][2] * tup.z + matrix.m[2][3] * tup.w;
	result.w = matrix.m[3][0] * tup.x + matrix.m[3][1] * tup.y + matrix.m[3][2] * tup.z + matrix.m[3][3] * tup.w;
	return (result);
}

// IDENTITY MATRIX -- WHERE SHOULD I STORE?
// matrixA * identity matrix == matrixA
// identity matrix * tupleA == tupleA
void	set_identity_matrix(t_matrix *matrix)
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
				matrix->m[i][j] = 1.0;
			else
				matrix->m[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

// TRANSPPOSE MATRIX --> columns become rows
void	transpose_matrix(t_matrix *matrix, t_matrix *result)
{
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			result->m[col][row] = matrix->m[row][col];
			col++;
		}
		row++;
	}
}


// If determinant is 0, no solution
double	determinant_mat2(t_matrix *matrix)
{
	return ((matrix->m[0][0] * matrix->m[1][1]) - (matrix->m[0][1] * matrix->m[1][0]));
}

void	submatrix(t_matrix *from, t_matrix *to, int row_del, int col_del)
{
	int	r;
	int	c;
	int	i;
	int	j;

	r = 0;
	i = 0;
	while (i < from->size)
	{
		if (i == row_del)
			continue;
		c = 0;
		j = 0;
		while (j < from->size)
		{
			if (j == col_del)
			{
				j++;
				continue;
			}
			to->m[r][c] = from->m[i][j];
			c++;
			j++;
		}
		r++;
		i++;
	}
	to->size = from->size - 1;
}

double	minor_mat3(t_matrix *old, int row, int col)
{
	t_matrix	new;

	submatrix(old, &new, row, col);
	return (determinant_mat2(&new));
}

// COFACTOR CALCULATIONS, 3 X 3
// +  -  +
// -  +  -
// +  -  +
double	cofactor_mat3(t_matrix *matrix, int row, int col)
{
	if ((row + col) % 2 != 0) // if row + column is odd, change the sign of the minor
		return (-minor_mat3(matrix, row, col));
	else
		return (minor_mat3(matrix, row, col));
}

//double	determinant_generic(double matrix[3][3])