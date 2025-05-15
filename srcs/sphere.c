/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:57 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/14 17:21:40 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// NORM OK EXCEPT MISALIGNED VARIABLES
t_xs	intersect_sphere(t_object *shape, t_ray ray)
{
	t_quadratic	q;
	t_xs		xs;

	prep_sphere_quadratic(&q, ray, shape);
	if (q.discriminant < 0)
	{
		xs.hit_distance = -1;
		return (xs);
	}
	q.root_discriminant = sqrt(q.discriminant);
	q.two_a = 2 * q.a;
	q.t[0] = (-q.b - q.root_discriminant) / (q.two_a);
	q.t[1] = (-q.b + q.root_discriminant) / (q.two_a);
	if (q.t[0] >= 0)
		xs.hit_distance = q.t[0];
	else
		xs.hit_distance = q.t[1];
	return (xs);
}

void	prep_sphere_quadratic(t_quadratic *q, t_ray ray, t_object *sphere)
{
	t_tuple	diff_cam;

	diff_cam = subtract(ray.origin, sphere->position);
	q->a = dot(ray.direction, ray.direction);
	q->b = 2.0f * dot(diff_cam, ray.direction);
	q->c = dot(diff_cam, diff_cam) - sphere->radius_squared;
	q->discriminant = get_discriminant(q->a, q->b, q->c);
}
