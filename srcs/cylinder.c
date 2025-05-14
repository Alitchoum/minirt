#include "minirt.h"

t_intersection	intersect_cap(t_object *cylinder, t_ray ray, double hit_z)
{
	t_intersection	xs;
	double	t;

	xs.hit_distance = -1;

	// check if ray parallel to caps (no intersection possible)
	if (fabs(ray.direction.z) < EPSILON)
		return (xs);

	// get the distance along the ray that it hits
	t = (hit_z - ray.origin.z) / ray.direction.z;

	// check is positive && inside the circle
	if (t >= 0)
	{
		xs.point = position(ray, t);
		if (pow(xs.point.x, 2) + pow(xs.point.y, 2) <= cylinder->radius_squared)
			xs.hit_distance = t;
	}
	return (xs);
}

t_intersection	intersect_barrel(t_object *cylinder, t_ray ray)
{
	t_quadratic	q;
	double	hit_z;
	t_intersection	xs;
	int	i;

	xs.hit_distance = -1;
	if (!solve_cylinder_quadratic(&q, ray, cylinder))
		return (xs);
	i = 0;
	while (i < 2)
	{
		if (q.t[i] >= 0)
		{
			hit_z = ray.origin.z + q.t[i] * ray.direction.z;
			if (hit_z >= -cylinder->half_height && hit_z <= cylinder->half_height)
			{
				if (xs.hit_distance < 0 || q.t[i] < xs.hit_distance)
				{
					xs.hit_distance = q.t[i];
					xs.world_position = position(ray, xs.hit_distance);
					xs.local_normal = normalize_tuple(vector(xs.world_position.x, xs.world_position.y, 0));
					xs.world_normal = transform_normal(xs.local_normal, cylinder->basis);
				}
			}
		}
		i++;
	}
	return (xs);
}

t_intersection	intersect_cylinder(t_object *cylinder, t_ray ray)
{
	t_intersection	barrel;
	t_intersection	top_cap;
	t_intersection	bottom_cap;
	t_intersection closest;

	ray = rotate_ray_to_local_space(ray, cylinder);

	barrel = intersect_barrel(cylinder, ray);
	closest = barrel;

	// check the top cap
	top_cap = intersect_cap(cylinder, ray, cylinder->half_height);
	if (top_cap.hit_distance >= 0)
		top_cap.world_normal = cylinder->basis.forward;

	// check the bottom cap
	bottom_cap = intersect_cap(cylinder, ray, -cylinder->half_height);
	if (bottom_cap.hit_distance >= 0)
		bottom_cap.world_normal = scale_tuple(cylinder->basis.forward, -1);

	// get the closest valid intersection between xs, topcap, bottom cap
	if (top_cap.hit_distance >= 0 && (closest.hit_distance < 0 || top_cap.hit_distance < closest.hit_distance))
		closest = top_cap;
	if (bottom_cap.hit_distance >= 0 && (closest.hit_distance < 0 || bottom_cap.hit_distance < closest.hit_distance))
		closest = bottom_cap;
	return (closest);
}

int	solve_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder)
{

	q->a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	q->b = 2.0f * ((ray.origin.x * ray.direction.x) + (ray.origin.y * ray.direction.y));
	q->c = (ray.origin.x * ray.origin.x) + (ray.origin.y * ray.origin.y) - cylinder->radius_squared;
	q->discriminant = get_discriminant(q->a, q->b, q->c);
	if (q->discriminant < 0)
		return (0);
	q->root_discriminant = sqrt(q->discriminant);
	q->two_a = 2 * q->a;
	q->t[0] = (-q->b - q->root_discriminant) / q->two_a;
	q->t[1] = (-q->b + q->root_discriminant) / (q->two_a);
	return (1);
}
