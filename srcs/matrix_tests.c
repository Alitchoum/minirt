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
	t_matrix d = new_matrix(4);
	t_matrix e = new_matrix(4);

	create_matrix(&a, 4, values);
	create_matrix(&b, 4, values2);
	mat4_multiply(&c, a, b);
	print_matrix(&c);

	inverse(&d, &b);
	mat4_multiply(&e, c, d);
	print_matrix(&e);
	exit(1);
}

