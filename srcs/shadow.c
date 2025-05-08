#include "minirt.h"

int	is_in_shadow(t_scene *scene, t_tuple hit_position, t_tuple light_position, t_object *shape, t_tuple hit_normal)
{
//	t_ray shadow_ray;
//	t_intersection shadow_intersection;
//	double	light_distance;
//
//	shadow_ray.origin = hit_position;
//	shadow_ray.origin = add_tuple(shadow_ray.origin, scale_tuple(hit_position, EPSILON));
//	shadow_ray.direction = normalize_tuple(subtract_tuple(light_position, hit_position));
//	light_distance = distance(hit_position, light_position);
//	shadow_intersection = get_closest_intersection(scene, shadow_ray, scene->objects, shape);
//	if (shadow_intersection.hit_distance >= 0 && (shadow_intersection.hit_distance < light_distance - EPSILON))
//		return (1);
//	return (0);
	t_ray shadow_ray;
    t_intersection shadow_intersection;
    double light_distance;

    // Offset along the surface normal instead of using hit_position.
    shadow_ray.origin = add_tuple(hit_position, scale_tuple(hit_normal, EPSILON));
    shadow_ray.direction = normalize_tuple(subtract_tuple(light_position, hit_position));
    light_distance = distance(hit_position, light_position);

    shadow_intersection = get_closest_intersection(scene, shadow_ray, scene->objects, shape);
    if (shadow_intersection.hit_distance >= 0 && (shadow_intersection.hit_distance < light_distance - EPSILON))
        return (1);
    return (0);

}
