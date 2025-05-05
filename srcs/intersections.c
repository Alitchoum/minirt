#include "minirt.h"

t_intersection	intersect(t_object *shape, t_ray ray);
t_intersection	finalize_hit_data(t_ray ray, t_intersection intersection);

t_intersection	intersect(t_object *shape, t_ray ray)
{
	t_ray	ray2;
	t_quadratic	q;
	t_intersection	xs;

	//set_transform(shape, translation(2, 0, 0));
	ray2 = transform(ray, inverse(&shape->transform_matrix));
	prep_quadratic(&q, ray, shape);
	if (q.discriminant < 0)
	{
		xs.hit_distance = -1;
		return (xs);
	}
	q.t[0] = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	q.t[1] = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (q.t[0] >= 0)
		xs.hit_distance = q.t[0];
	else
		xs.hit_distance = q.t[1];
	return (xs);
}

t_intersection	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects)
{
	t_intersection	current_intersection;
	t_intersection	closest_intersection;
	t_object	*closest_shape = NULL;
	
	int	i = 0;

	closest_intersection.hit_distance = INT_MAX;

	while(i < scene->obj_count)
	{
		current_intersection = intersect(&objects[i], ray);
		if ((current_intersection.hit_distance < closest_intersection.hit_distance) && (current_intersection.hit_distance >= 0))
		{
			closest_intersection = current_intersection;
			closest_shape = &objects[i];
		}
		i++;
	}
	if (closest_shape == NULL)
	{
		closest_intersection.hit_distance = -1;
		return (closest_intersection);
	}
	closest_intersection.object = closest_shape;
	return (closest_intersection);
	//return (finalize_hit_data(ray, closest_intersection));
}

t_intersection	finalize_hit_data(t_ray ray, t_intersection intersection)
{
	//t_tuple centre = intersection.object->position;
	//t_matrix m = translation(centre.x, centre.y, centre.z);
	//t_ray r2 = transform(ray, m);
	//ray.origin = mat4_multiply_tuple(m, ray.origin);
	intersection.world_position = position(ray, intersection.hit_distance);
	if (intersection.object->type == PLANE)
	{
		intersection.world_normal = intersection.object->normal;
		ray.origin = subtract_tuple(ray.origin, intersection.object->point);

	}
	else
	{
		ray.origin = subtract_tuple(ray.origin, intersection.object->position);
		intersection.world_normal = normalize_tuple(subtract_tuple(intersection.world_position, intersection.object->position));
		intersection.world_position = add_tuple(intersection.world_position, intersection.object->position);

	}
	//intersection.world_normal = normalize_tuple(intersection.world_position);
	return (intersection);
}
