#include "minirt.h"

t_ray	new_ray(t_tuple origin, t_tuple direction)
{
	t_ray	new;

	new.origin = origin;
	new.direction = direction;
	return (new);
}

// returns a point at given distance along the ray
t_tuple	position(t_ray ray, double distance)
{
	t_tuple	new_position;

	new_position.x = ray.origin.x + ray.direction.x * distance;
	new_position.y = ray.origin.y + ray.direction.y * distance;
	new_position.z = ray.origin.z + ray.direction.z * distance;
	new_position.w = ray.origin.w + ray.direction.w * distance;
	return (new_position);
}

t_ray	rotate_ray_to_local_space(t_ray ray, t_object *shape)
{
	t_tuple	diff;
	t_tuple	rotated_origin;
	t_tuple	rotated_direction;
	t_local	basis;

	basis = shape->basis;
	diff = subtract_tuple(ray.origin, shape->position);

	// rotate ray origin to local space
	rotated_origin.x = dot_tuple(diff, basis.right);
	rotated_origin.y = dot_tuple(diff, basis.up);
	rotated_origin.z = dot_tuple(diff, basis.forward);

	// rotate ray direction to local space
	rotated_direction.x = dot_tuple(ray.direction, basis.right);
	rotated_direction.y = dot_tuple(ray.direction, basis.up);
	rotated_direction.z = dot_tuple(ray.direction, basis.forward);

	ray.origin = rotated_origin;
	ray.direction = rotated_direction;
	return (ray);
}
