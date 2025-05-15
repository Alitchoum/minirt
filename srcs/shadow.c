/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:48:52 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:55 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// Returns the first intersection it finds between object and light source, 
// or returns hit distance of -1 if there's none
t_xs	intersect_light(t_scene *scene, t_ray r, t_object *shape, double light)
{
	t_xs	xs;
	int		i;

	i = 0;
	xs.hit_distance = INT_MAX;
	while (i < scene->obj_count)
	{
		if (shape == &scene->objects[i])
		{
			i++;
			continue ;
		}
		xs = intersect(&scene->objects[i], r);
		if ((xs.hit_distance >= EPSILON) && (xs.hit_distance < light))
		{
			xs.object = &scene->objects[i];
			return (xs);
		}
		i++;
	}
	xs.hit_distance = -1;
	return (xs);
}

// Boolean to determine if an intersected object is in shadow or not
int	is_in_shadow(t_scene *scene, t_object *shape, t_xs *hit)
{
	t_ray		ray;
	t_xs		xs;
	double		light_distance;

	ray.origin = scale(hit->world_normal, EPSILON);
	ray.origin = add(hit->world_position, ray.origin);
	ray.direction = subtract(scene->light.position, hit->world_position);
	ray.direction = normalize(ray.direction);
	light_distance = distance(hit->world_position, scene->light.position);
	xs = intersect_light(scene, ray, shape, light_distance);
	if (xs.hit_distance >= 0)
		return (1);
	return (0);
}
