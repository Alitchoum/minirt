/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:31:29 by caburges          #+#    #+#             */
/*   Updated: 2025/04/23 17:32:05 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_matrix(t_matrix *m)
{
	int i = 0;
	int j = 0;
	printf("-----MATRIX-----\n");
	while (i < m->size)
	{
		j = 0;
		while (j < m->size)
		{
			printf("[%f]", m->m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void	create_matrix(t_matrix *m, int size, double values[4][4])
{
	int i = 0;
	while (i < size)
	{
		int j = 0;
		while (j < size)
		{
			m->m[i][j] = values[i][j];
			j++;
		}
		i++;
	}
}

void	print_tuple(t_tuple tup)
{
	printf("%f, %f, %f, %f\n", tup.x, tup.y, tup.z, tup.w);
}

void	run_transformation_tests(void)
{
//	t_matrix transform = translation(5, -3, 2);
//
//	// MULT A POINT BY A TRANSLATION, MOVES IT
//	t_tuple p = point(-3, 4, 5);
//	t_tuple final = mat4_multiply_tuple(transform, p);
//	print_tuple(final);
//	
//	// MULT A VECTOR BY A TRANSLATION, DOESNT CHANGE IT
//	t_tuple v = vector(-3, 4, 5);
//	final = mat4_multiply_tuple(transform, v);
//	print_tuple(final);

	//t_matrix transform = scaling(2, 3, 4);
	//t_tuple p = point(-4, 6, 8);
	//t_tuple final = mat4_multiply_tuple(transform, p);
	//print_tuple(final);

//	t_matrix transform = scaling(2, 3, 4);
//	t_tuple v = vector(-4, 6, 8);
//	t_tuple final = mat4_multiply_tuple(transform, v);
//	print_tuple(final);

//	t_matrix transform = scaling(-1, 1, 1);
//	t_tuple p = point(2, 3, 4);
//	t_tuple final = mat4_multiply_tuple(transform, p);
//
//	print_tuple(final);
//
//	t_tuple p = point(0, 1, 0);
//	t_matrix half_quarter = rotation_x(M_PI / 4);
//	t_matrix inv = new_matrix(4);
//	inverse(&half_quarter, &inv);
//	t_tuple final = mat4_multiply_tuple(inv, p);
//	print_tuple(final);
	
	t_tuple p = point(1, 0, 1);
	t_matrix a = rotation_x(M_PI / 2);
	t_matrix b = scaling(5, 5, 5);
	t_matrix c = translation(10, 5, 7);

	t_matrix t = new_matrix(4);
	mat4_multiply(&t, c, b);
	mat4_multiply(&t, t, a);
	t_tuple final = mat4_multiply_tuple(t, p);
	print_tuple(final);
}
void	run_matrix_tests(void)
{

	double values[4][4] = {
		{3, -9, 7, 3},
		{3, -8, 2, -9},
		{-4, 4, 4, 1},
		{-6, 5, -1, 1}
	};

	double values2[4][4] = {
		{8, 2, 2, 2},
		{3, -1, 7, 0},
		{7, 0, 5, 4},
		{6, -2, 0, 5}
	};

	t_matrix a = new_matrix(4);
	t_matrix b = new_matrix(4);
	t_matrix c = new_matrix(4);
	t_matrix inv_b = new_matrix(4);
	t_matrix final = new_matrix(4);

	create_matrix(&a, 4, values);
	printf("A\n");
	print_matrix(&a);
	create_matrix(&b, 4, values2);
	printf("B\n");
	print_matrix(&b);
	mat4_multiply(&c, a, b);
	printf("C = A * B\n");
	print_matrix(&c);

	inverse(&b, &inv_b);
	printf("inv of b\n");
	print_matrix(&inv_b);
	
	mat4_multiply(&final, c, inv_b);
	printf("C * inverse(B) = A\n");
	print_matrix(&final);

	t_ray r = new_ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix m = translation(3, 4, 5);
	
	t_ray r2 = transform(r, m);
	print_tuple(r2.origin);
	print_tuple(r2.direction);
	exit(1);
}

