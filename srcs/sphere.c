/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:26:57 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/13 17:34:38 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersect_sphere(t_object *shape, t_ray ray)
{
	//t_ray	ray2;
	t_quadratic		q;
	t_intersection	xs;

	//set_transform(shape, translation(2, 0, 0));
	//ray2 = transform(ray, inverse(&shape->transform_matrix));
	prep_sphere_quadratic(&q, ray, shape);
	if (q.discriminant < 0)
	{
		xs.hit_distance = -1;
		return (xs);
	}
	q.t[0] = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	q.t[1] = (-q.b + sqrt(q.discriminant)) /
		(2.0 * q.a);
	if (q.t[0] >= 0)
		xs.hit_distance = q.t[0];
	else
		xs.hit_distance = q.t[1];
	return (xs);
}

void	prep_sphere_quadratic(t_quadratic *quadratic, t_ray ray, t_object *sphere)
{
	t_tuple	diff_sphere_camera;

	diff_sphere_camera = subtract_tuple(ray.origin, sphere->position);
	quadratic->a = dot_tuple(ray.direction, ray.direction);
	quadratic->b = 2.0f * dot_tuple(diff_sphere_camera, ray.direction);
	quadratic->c = dot_tuple(diff_sphere_camera, diff_sphere_camera) - pow((sphere->diametre * 0.5), 2);
	quadratic->discriminant = get_discriminant(quadratic->a, quadratic->b, quadratic->c);
}

void	prep_quadratic(t_quadratic *quadratic, t_ray ray, t_object *object)
{
	if (object->type == SPHERE)
		prep_sphere_quadratic(quadratic, ray, object);
	else if (object->type == CYLINDER)
		prep_cylinder_quadratic(quadratic, ray, object);
	//else if (object->type == PLANE)
	//	prep_plane_quadratic(quadratic, ray, object);
	return ;
}
