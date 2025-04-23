/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:56:05 by caburges          #+#    #+#             */
/*   Updated: 2025/04/21 18:56:07 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	t_tuple	new;

	new.x = x;
	new.y = y;
	new.z = z;
	new.w = w;
	return (new);
}

// create a new point (w is 1)
t_tuple	point(double x, double y, double z)
{
	t_tuple new;

	new = tuple(x, y, z, 1);
	return (new);
}

// create a new vector (w is 0)
t_tuple vector(double x, double y, double z)
{
	t_tuple new;

	new = tuple(x, y, z, 0);
	return (new);
}

int	tuple_is_equal(t_tuple a, t_tuple b)
{
	if (!is_equal(a.x, b.x))
		return (0);
	if (!is_equal(a.y, b.y))
		return (0);
	if (!is_equal(a.z, b.z))
		return (0);
	if (!is_equal(a.w, b.w))
		return (0);
	return (1);
}

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	new.w = a.w + b.w;
	return (new);
}

t_tuple	subtract_tuple(t_tuple a, t_tuple b)
{
	t_tuple new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	new.w = a.w - b.w;
	return (new);
}

t_tuple	negate_tuple(t_tuple a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	a.w = -a.w;
	return (a);
}

t_tuple	scale_tuple(t_tuple a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	a.w *= scale;
	return (a);
}

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
double dot_tuple(t_tuple a, t_tuple b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

// returns a vector that is perpendicular to both of the original vectors
t_tuple	cross_tuple(t_tuple a, t_tuple b)
{
	double x;
	double y;
	double z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return (vector(x, y, z));
}
