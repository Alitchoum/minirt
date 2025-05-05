#include "minirt.h"

void	prep_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder)
{
	t_tuple	diff;

	diff = subtract_tuple(ray.origin, cylinder->position);
	q->a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	q->b = 2.0f * ((diff.x * ray.direction.x) + (diff.y * ray.direction.y));
	q->c = (diff.x * diff.x) + (diff.y * diff.y) - 1;
	q->discriminant = get_discriminant(q->a, q->b, q->c);
}
