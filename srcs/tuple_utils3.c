/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:07 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:22:07 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	magnitude(t_tuple a)
{
	double	result;

	result = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
	return (result);
}

t_tuple	normalize_tuple(t_tuple a)
{
	double	mag;

	mag = magnitude(a);
	a.x /= mag;
	a.y /= mag;
	a.z /= mag;
	a.w /= mag;
	return (a);
}

// smaller the dot product, the larger the angle between the vectors
// 1 means the vectors are identical
// -1 means they point in opposite directions
// to be used on VECTORS only, not POINTS
double	dot_tuple(t_tuple a, t_tuple b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

// returns a vector that is perpendicular to both of the original vectors
t_tuple	cross_tuple(t_tuple a, t_tuple b)
{
	double	x;
	double	y;
	double	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return (vector(x, y, z));
}

t_tuple	rotate_tuple(t_tuple a, int axe, double angle)
{
	t_tuple	rotate;

	rotate = a;
	if (axe == X)
	{
		rotate.y = a.y * cos(angle) - a.z * sin(angle);
		rotate.z = a.y * sin(angle) + a.z * cos(angle);
	}
	else if (axe == Y)
	{
		rotate.x = a.x * cos(angle) + a.z * sin(angle);
		rotate.z = -a.x * sin(angle) + a.z * cos(angle);
	}
	else if (axe == Z)
	{
		rotate.x = a.x * cos(angle) - a.y * sin(angle);
		rotate.y = a.x * sin(angle) + a.y * cos(angle);
	}
	return (normalize_tuple(rotate));
}
