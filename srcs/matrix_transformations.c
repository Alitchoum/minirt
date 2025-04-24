/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:15:12 by caburges          #+#    #+#             */
/*   Updated: 2025/04/24 17:15:13 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TRANSLATION
// translation(x, y, z)
// 1 0 0 x
// 0 1 0 y
// 0 0 1 z
// 0 0 0 1
// start with an identity matrix, add desired x y z elements
// translation moves a point by adding to it
t_matrix	translation(double x, double y, double z)
{
	t_matrix	new;

	new = get_identity_matrix();

	new.m[0][3] = x;
	new.m[1][3] = y;
	new.m[2][3] = z;
	return (new);
}

// SCALING
// scaling moves a point by multiplication
// x 0 0 0
// 0 y 0 0 
// 0 0 z 0
// 0 0 0 w
t_matrix	scaling(double x, double y, double z)
{
	t_matrix	new;

	new = get_identity_matrix();

	new.m[0][0] = x;
	new.m[1][1] = y;
	new.m[2][2] = z;
	return (new);
}
