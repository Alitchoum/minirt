/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:31 by caburges          #+#    #+#             */
/*   Updated: 2025/05/13 13:15:12 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

float	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

//will rotate that tuple around an axis
double	radians(double degrees)
{
	return ((degrees / 180) * M_PI);
}

// t_tuple	normal_at(t_object *shape, t_tuple world_point)
// {
// 	t_tuple	object_normal;
// 	t_tuple	object_point;
// 	t_tuple	world_normal;
// 	t_matrix	inversed;

// 	object_point = mat4_multiply_tuple(inverse(&shape->transform_matrix), world_point);
// 	object_normal = subtract_tuple(object_point, point(0, 0, 0));
// 	inversed = inverse(&shape->transform_matrix);
// 	world_normal = mat4_multiply_tuple(transpose_matrix(&inversed), object_normal);
// 	world_normal.w = 0;
// 	return (normalize_tuple(world_normal));
// }
