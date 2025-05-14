#include "minirt.h"

t_intersection	finalize_hit_data(t_ray ray, t_intersection intersection);

t_intersection	intersect(t_object *shape, t_ray ray)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(shape, ray));
	else if (shape->type == CYLINDER)
		return (intersect_cylinder(shape, ray));
	else
		return (intersection_plane(ray, shape));
}

t_intersection	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects)
{
	t_intersection	current_intersection;
	t_intersection	closest_intersection;
	t_object	*closest_shape;
	int	i;
	
	closest_shape = NULL;
	closest_intersection.hit_distance = INT_MAX;
	i = 0;
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
	return (finalize_hit_data(ray, closest_intersection));
}

// translates the hit (intersection) data back to world space
t_intersection	finalize_hit_data(t_ray ray, t_intersection intersection)
{
	intersection.world_position = position(ray, intersection.hit_distance);
	if (intersection.object->type == PLANE)
		intersection.world_normal = intersection.object->normal;
	else if (intersection.object->type == SPHERE)
	{
		ray.origin = subtract_tuple(ray.origin, intersection.object->position);
		intersection.world_normal = normalize_tuple(subtract_tuple(intersection.world_position, intersection.object->position));
	}
	return (intersection);
}
