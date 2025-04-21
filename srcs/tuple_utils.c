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

t_tuple	point(double x, double y, double z)
{
	t_tuple new;

	new = tuple(x, y, z, 1);
	return (new);
}

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

