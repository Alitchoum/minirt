/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:40:35 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/12 18:31:00 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersection_plane(t_ray ray, t_object *plane)
{
	t_tuple	diff;
	double	denominator;
	double	numerator;
	double	dist;
	t_intersection xs;

	xs.hit_distance = -1;

	denominator = dot_tuple(plane->normal, ray.direction);
	if (is_equal(denominator, 0.0))
		return	(xs);
	diff = subtract_tuple(plane->position, ray.origin);
	numerator = dot_tuple(plane->normal, diff);
	dist = numerator / denominator;
	if (dist < EPSILON)
		return (xs);
	xs.hit_distance = dist;
	return (xs);
}

