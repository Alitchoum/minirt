#include "minirt.h"

void	prep_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder)
{
	t_tuple	diff_cylinder_ray = subtract_tuple(ray.origin, cylinder->position);
	double	projection = dot_tuple(diff_cylinder_ray, cylinder->orientation);
	t_tuple parallel_component = scale_tuple(cylinder->orientation, projection);
	t_tuple diff_perp = subtract_tuple(diff_cylinder_ray, parallel_component);
	
	q->a = dot_tuple(diff_perp, diff_perp);
	q->b = 2 * dot_tuple(diff_perp, parallel_component);
	q->c = dot_tuple(parallel_component, parallel_component) - (pow(cylinder->diametre * 0.5, 2));
	q->discriminant = get_discriminant(q->a, q->b, q->c);
}
