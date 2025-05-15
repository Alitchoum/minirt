/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:47:34 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:47:36 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// check if ray parallel to caps (no intersection possible)
// get the distance along the ray that it hits
// check is positive && inside the circle
t_xs	intersect_cap(t_object *cylinder, t_ray ray, double hit_z)
{
	t_xs	xs;
	double	hit_dist;
	double	pow_x;
	double	pow_y;

	xs.hit_distance = -1;
	if (fabs(ray.direction.z) < EPSILON)
		return (xs);
	hit_dist = (hit_z - ray.origin.z) / ray.direction.z;
	if (hit_dist >= 0)
	{
		xs.point = position(ray, hit_dist);
		pow_x = xs.point.x * xs.point.x;
		pow_y = xs.point.y * xs.point.y;
		if (pow_x + pow_y <= cylinder->radius_squared)
			xs.hit_distance = hit_dist;
	}
	return (xs);
}

//to change world_position to world_pos
void	update_barrel_hit(t_ray ray, t_xs *xs, double new_dist, t_object *cy)
{
	if (xs->hit_distance < 0 || new_dist < xs->hit_distance)
	{
		xs->hit_distance = new_dist;
		xs->world_position = position(ray, xs->hit_distance);
		xs->local_normal = xs->world_position;
		xs->local_normal.z = 0;
		xs->local_normal.w = 0;
		xs->local_normal = normalize(xs->local_normal);
		xs->world_normal = transform_normal(xs->local_normal, cy->basis);
	}
}

t_xs	intersect_barrel(t_object *cy, t_ray ray)
{
	t_quadratic	q;
	double		hit_z;
	t_xs		xs;
	int			i;

	hit_z = 0;
	xs.hit_distance = -1;
	if (!solve_cylinder_quadratic(&q, ray, cy))
		return (xs);
	i = 0;
	while (i < 2)
	{
		if (q.t[i] >= 0)
		{
			hit_z = ray.origin.z + q.t[i] * ray.direction.z;
			if (hit_z >= -cy->half_height && hit_z <= cy->half_height)
				update_barrel_hit(ray, &xs, q.t[i], cy);
		}
		i++;
	}
	return (xs);
}

t_xs	intersect_cylinder(t_object *cylinder, t_ray ray)
{
	t_xs	barrel;
	t_xs	top_cap;
	t_xs	bottom_cap;
	t_xs	closest;

	ray = rotate_ray_to_local_space(ray, cylinder);
	barrel = intersect_barrel(cylinder, ray);
	closest = barrel;
	top_cap = intersect_cap(cylinder, ray, cylinder->half_height);
	if (top_cap.hit_distance >= 0)
		top_cap.world_normal = cylinder->basis.forward;
	bottom_cap = intersect_cap(cylinder, ray, -cylinder->half_height);
	if (bottom_cap.hit_distance >= 0)
		bottom_cap.world_normal = scale(cylinder->basis.forward, -1);
	if (top_cap.hit_distance >= 0 && (closest.hit_distance < 0 || top_cap.hit_distance < closest.hit_distance))
		closest = top_cap;
	if (bottom_cap.hit_distance >= 0 && (closest.hit_distance < 0 || bottom_cap.hit_distance < closest.hit_distance))
		closest = bottom_cap;
	return (closest);
}

int	solve_cylinder_quadratic(t_quadratic *q, t_ray r, t_object *cy)
{
	double	pw_x;
	double	pw_y;

	pw_x = r.direction.x * r.direction.x;
	pw_y = r.direction.y * r.direction.y;
	q->a = pw_x + pw_y;
	q->b = 2.0f * ((r.origin.x * r.direction.x) + (r.origin.y * r.direction.y));
	pw_x = r.origin.x * r.origin.x;
	pw_y = r.origin.y * r.origin.y;
	q->c = pw_x + pw_y - cy->radius_squared;
	q->discriminant = get_discriminant(q->a, q->b, q->c);
	if (q->discriminant < 0)
		return (0);
	q->root_discriminant = sqrt(q->discriminant);
	q->two_a = 2 * q->a;
	q->t[0] = (-q->b - q->root_discriminant) / q->two_a;
	q->t[1] = (-q->b + q->root_discriminant) / (q->two_a);
	return (1);
}
