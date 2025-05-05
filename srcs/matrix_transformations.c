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

// ROTATION
// will rotate that tuple around an axis
double	radians(double degrees)
{
	return ((degrees / 180) * M_PI);
}

t_matrix	rotation_x(double radians)
{
	t_matrix new;

	new = get_identity_matrix();
	new.m[1][1] = cos(radians);
	new.m[1][2] = -sin(radians);
	new.m[2][1] = sin(radians);
	new.m[2][2] = cos(radians);
	return (new);
}

t_matrix	rotation_y(double radians)
{
	t_matrix new;

	new = get_identity_matrix();
	new.m[0][0] = cos(radians);
	new.m[0][2] = sin(radians);
	new.m[2][0] = -sin(radians);
	new.m[2][2] = cos(radians);
	return (new);
}

t_matrix	rotation_z(double radians)
{
	t_matrix new;

	new = get_identity_matrix();
	new.m[0][0] = cos(radians);
	new.m[0][1] = -sin(radians);
	new.m[1][0] = sin(radians);
	new.m[1][1] = cos(radians);
	return (new);
}

// CHAINING TRANSFORMATIONS
// A: rotation
// B: scale
// C: translation
// must do it in reverse order
// point = (C * (B * (A * point)));
// multiply all the transformation matrices together, than multiply it by the point to get the final transformed point
// matrices must be done in reverse order. (translation, scaling, rotation)
t_ray	transform(t_ray ray, t_matrix matrix)
{
	t_ray	new_ray;

	new_ray.origin = mat4_multiply_tuple(matrix, ray.origin);
	new_ray.direction = mat4_multiply_tuple(matrix, ray.direction);
	return (new_ray);
}

void	set_transform(t_object *shape, t_matrix matrix)
{
	shape->transform_matrix = matrix;
}
