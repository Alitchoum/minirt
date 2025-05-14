
#include "minirt.h"

t_intersection	intersect_sphere(t_object *shape, t_ray ray)
{
	t_quadratic	q;
	t_intersection	xs;

	prep_sphere_quadratic(&q, ray, shape);
	if (q.discriminant < 0)
	{
		xs.hit_distance = -1;
		return (xs);
	}
	q.root_discriminant = sqrt(q.discriminant);
	q.two_a = 2 * q.a;
	q.t[0] = (-q.b - q.root_discriminant) / (q.two_a);
	q.t[1] = (-q.b + q.root_discriminant) / (q.two_a);
	if (q.t[0] >= 0 && q.t[0] < q.t[1])
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
	quadratic->c = dot_tuple(diff_sphere_camera, diff_sphere_camera) - sphere->radius_squared;
	quadratic->discriminant = get_discriminant(quadratic->a, quadratic->b, quadratic->c);
}
