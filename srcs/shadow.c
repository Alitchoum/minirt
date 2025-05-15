#include "minirt.h"
// MERGE OK
// Returns the first intersection it finds between object and light source, or returns hit distance of -1 if there's none
// It doesn't care about finding the closest as it's hard shadows
t_intersection	find_intersection_before_light_source(t_scene *scene, t_ray ray, t_object *objects, t_object *hit_shape, double light_distance)
{
	t_intersection	current_intersection;
	int	i;

	i = 0;
	current_intersection.hit_distance = INT_MAX;
	while(i < scene->obj_count)
	{
		// Ignore if it's an intersection with itself for speed
		if (hit_shape == &objects[i])
		{
			i++;
			continue;
		}
		current_intersection = intersect(&objects[i], ray);
		// If it's a valid intersection, return because we dont need the closest, just if it's blocked or not
		if ((current_intersection.hit_distance >= EPSILON) && (current_intersection.hit_distance < light_distance))
		{
			current_intersection.object = &objects[i];
			return (current_intersection);
		}
		i++;
	}
	current_intersection.hit_distance = -1;
	return (current_intersection);
}

// Boolean to determine if an intersected object is in shadow or not
int	is_in_shadow(t_scene *scene, t_tuple hit_position, t_tuple light_position, t_object *shape, t_tuple hit_normal)
{
	t_ray shadow_ray;
	t_intersection shadow_intersection;
	double light_distance;

    	// Offset along the surface normal instead of using hit_position.
	shadow_ray.origin = add_tuple(hit_position, scale_tuple(hit_normal, EPSILON));
    	shadow_ray.direction = normalize_tuple(subtract_tuple(light_position, hit_position));
    	light_distance = distance(hit_position, light_position);

	// if an intersection is found at a distance closer than the position of the light, it is in a shadow
    	shadow_intersection = find_intersection_before_light_source(scene, shadow_ray, scene->objects, shape, light_distance);
    	if (shadow_intersection.hit_distance >= 0)
        	return (1);
    	return (0);
}
