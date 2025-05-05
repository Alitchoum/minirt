#include "minirt.h"

t_matrix	new_matrix(int size)
{
	t_matrix	new;

	ft_bzero(&new, sizeof(t_matrix));
	new.size = size;
	return (new);
}

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

t_matrix	mat4_multiply(t_matrix *result, t_matrix a, t_matrix b)
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
	return (*result);
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

t_matrix	get_identity_matrix(void)
{
	t_matrix	new;
	int	i;
	int	j;

	new.size = 4;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				new.m[i][j] = 1.0;
			else
				new.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (new);
}

// TRANSPPOSE MATRIX --> columns become rows
t_matrix	transpose_matrix(t_matrix *matrix)
{
	int	row;
	int	col;
	t_matrix	new;

	new.size = 4;
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			new.m[col][row] = matrix->m[row][col];
			col++;
		}
		row++;
	}
	return (new);
}


// If determinant is 0, no solution
double	determinant_mat2(t_matrix *matrix)
{
	return ((matrix->m[0][0] * matrix->m[1][1]) - (matrix->m[0][1] * matrix->m[1][0]));
}

t_matrix	submatrix(t_matrix *from, int row_del, int col_del)
{
	int	r;
	int	c;
	int	i;
	int	j;
	t_matrix	to;

	r = 0;
	i = 0;
	to.size = from->size - 1;
	while (i < from->size)
	{
		if (i == row_del)
		{
			i++;
			continue;
		}	
		c = 0;
		j = 0;
		while (j < from->size)
		{
			if (j == col_del)
			{
				j++;
				continue;
			}
			to.m[r][c] = from->m[i][j];
			c++;
			j++;
		}
		r++;
		i++;
	}
	return (to);
}

// Generic works for all up to 4x4 ?
double	minor(t_matrix *old, int row, int col)
{
	t_matrix	new;

	new = submatrix(old, row, col);
	return (determinant(&new));
}


// COFACTOR CALCULATIONS, 3 X 3
// +  -  +
// -  +  -
// +  -  +
double	cofactor(t_matrix *matrix, int row, int col)
{
	if ((row + col) % 2 != 0) // if row + column is odd, change the sign of the minor
		return (-minor(matrix, row, col));
	else
		return (minor(matrix, row, col));
}

double	determinant(t_matrix *matrix)
{
	double result;
	int	col;

	col = 0;
	result = 0;
	if (matrix->size == 2)
		return (determinant_mat2(matrix));
	while (col < matrix->size)
	{
		result = result + (matrix->m[0][col] * cofactor(matrix, 0, col));
		col++;
	}
	return (result);
}

// INVERSIONS: IF DETERMINANT IS 0, THE MATRIX IS NOT INVERTIBLE
t_matrix	inverse(t_matrix *matrix)
{
	int	row;
	int	col;
	double	det;
	double	c;
	t_matrix	result;

	result = new_matrix(4);
	det = determinant(matrix);
	c = 0;
	// if the matrix is not invertible, return fail
	if (is_equal(det, 0))
	{
		//printf("not intertaible\n");
		return (get_identity_matrix());

	}
	row = 0;
	while (row < matrix->size)
	{
		col = 0;
		while (col < matrix->size)
		{
			c = cofactor(matrix, row, col);
			result.m[col][row] = c / det;
			col++;
		}
		row++;
	}
	//result->size = matrix->size;
	return (result);
}
