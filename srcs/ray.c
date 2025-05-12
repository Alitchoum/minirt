#include "minirt.h"

t_ray	new_ray(t_tuple origin, t_tuple direction)
{
	t_ray	new;

	//ft_bzero(&new, sizeof(t_ray));
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
