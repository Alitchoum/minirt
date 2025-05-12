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
		if (pow(xs.point.x, 2) + pow(xs.point.y, 2) <= pow(cylinder->radius, 2))
			xs.hit_distance = t;
	}
	return (xs);
}

t_intersection	intersect_cylinder(t_object *cylinder, t_ray ray)
{
	t_quadratic	q;
	t_intersection	xs;
	t_intersection	top_cap;
	t_intersection	bottom_cap;
	t_tuple w = cylinder->orientation;
	t_tuple u;
	t_tuple v;
	t_tuple rotated_direction;
	t_tuple rotated_origin;
	t_tuple diff;
	double	hit_z;
	double	height = cylinder->height / 2;

	// local basis
	if (fabs(w.x) < 0.9)
		u = normalize_tuple(cross_tuple(vector(1, 0, 0), w));
	else
		u = normalize_tuple(cross_tuple(vector(0, 1, 0), w));
	v = cross_tuple(w, u);

	// rotate ray origin to local space
	diff = subtract_tuple(ray.origin, cylinder->position);
	rotated_origin.x = dot_tuple(diff, u);
	rotated_origin.y = dot_tuple(diff, v);
	rotated_origin.z = dot_tuple(diff, w);

	// rotate ray direction to local space
	rotated_direction.x = dot_tuple(ray.direction, u);
	rotated_direction.y = dot_tuple(ray.direction, v);
	rotated_direction.z = dot_tuple(ray.direction, w);

	// new ray
	ray.origin = rotated_origin;
	ray.direction = rotated_direction;

	xs.hit_distance = -1;

	// rest as per sphere -> check if intersection with curved surface
	prep_cylinder_quadratic(&q, ray, cylinder);
	if (q.discriminant < 0)
		return (xs);
	q.root_discriminant = sqrt(q.discriminant);
	q.two_a = 2 * q.a;
	q.t[0] = (-q.b - q.root_discriminant) / q.two_a;
	q.t[1] = (-q.b + q.root_discriminant) / (q.two_a);

	// check if the point is within the height of the cylinder
	if (q.t[0] >= 0)
	{
		hit_z = ray.origin.z + q.t[0] * ray.direction.z;
		if (hit_z >= -height && hit_z <= height)
		{
			xs.hit_distance = q.t[0];
			t_tuple local_point = position(ray, xs.hit_distance);
			t_tuple local_normal = normalize_tuple(vector(local_point.x, local_point.y, 0));

			xs.world_normal.x = local_normal.x * u.x + local_normal.y * v.x + local_normal.z * w.x;
			xs.world_normal.y = local_normal.x * u.y + local_normal.y * v.y + local_normal.z * w.y;
			xs.world_normal.z = local_normal.x * u.z + local_normal.y * v.z + local_normal.z * w.z;

		}

	}
	if (xs.hit_distance < 0 && q.t[1] >= 0)
	{
		hit_z = ray.origin.z + q.t[1] * ray.direction.z;
		if (hit_z >= -height && hit_z <= height)
		{
			xs.hit_distance = q.t[1];
			t_tuple local_point = position(ray, xs.hit_distance);
			t_tuple local_normal = normalize_tuple(vector(local_point.x, local_point.y, 0));

			xs.world_normal.x = local_normal.x * u.x + local_normal.y * v.x + local_normal.z * w.x;
			xs.world_normal.y = local_normal.x * u.y + local_normal.y * v.y + local_normal.z * w.y;
			xs.world_normal.z = local_normal.x * u.z + local_normal.y * v.z + local_normal.z * w.z;

		}

	}
	//check for intersect with caps
	// check the top cap
	top_cap = intersect_cap(cylinder, ray, cylinder->height / 2.0);
	if (top_cap.hit_distance >= 0)
		top_cap.world_normal = w;
	// check the bottom cap
	bottom_cap = intersect_cap(cylinder, ray, -cylinder->height / 2.0);
	if (bottom_cap.hit_distance >= 0)
		bottom_cap.world_normal = scale_tuple(w, -1);

	// get the closest valid intersection between xs, topcap, bottom cap
	t_intersection closest;
	
	closest = xs;
	if (top_cap.hit_distance >= 0 && (closest.hit_distance < 0 || top_cap.hit_distance < closest.hit_distance))
		closest = top_cap;
	if (bottom_cap.hit_distance >= 0 && (closest.hit_distance < 0 || bottom_cap.hit_distance < closest.hit_distance))
		closest = bottom_cap;

	return (closest);
}

void	prep_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder)
{

	q->a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	q->b = 2.0f * ((ray.origin.x * ray.direction.x) + (ray.origin.y * ray.direction.y));
	q->c = (ray.origin.x * ray.origin.x) + (ray.origin.y * ray.origin.y) - cylinder->radius_squared;
	q->discriminant = get_discriminant(q->a, q->b, q->c);
}
