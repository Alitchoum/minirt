/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:48:04 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:05 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_xs	finalize_hit_data(t_ray ray, t_xs xs);

t_xs	intersect(t_object *shape, t_ray ray)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray));
	else if (shape->type == CYLINDER)
		return (intersect_cylinder(shape, ray));
	else
		return (intersection_plane(ray, shape));
}

void	set_closest_intersection(t_xs *closest, t_xs *cur, t_object *cur_shape)
{
	if ((cur->hit_distance < closest->hit_distance) && (cur->hit_distance >= 0))
	{
		*closest = *cur;
		closest->object = cur_shape;
	}
}

t_xs	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects)
{
	t_xs	xs;
	t_xs	closest_xs;
	int		i;

	closest_xs.object = NULL;
	closest_xs.hit_distance = INT_MAX;
	i = 0;
	while (i < scene->obj_count)
	{
		xs = intersect(&objects[i], ray);
		set_closest_intersection(&closest_xs, &xs, &objects[i]);
		i++;
	}
	if (!closest_xs.object)
	{
		closest_xs.hit_distance = -1;
		return (closest_xs);
	}
	return (finalize_hit_data(ray, closest_xs));
}

// translates the hit (intersection) data back to world space
t_xs	finalize_hit_data(t_ray ray, t_xs x)
{
	x.world_position = position(ray, x.hit_distance);
	if (x.object->type == PLANE)
		x.world_normal = x.object->normal;
	else if (x.object->type == SPHERE)
	{
		ray.origin = subtract(ray.origin, x.object->position);
		x.world_normal = subtract(x.world_position, x.object->position);
		x.world_normal = normalize(x.world_normal);
	}
	return (x);
}
