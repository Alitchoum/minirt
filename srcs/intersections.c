#include "minirt.h"

t_intersect	*intersect(t_object *sphere, t_ray ray)
{
	t_intersect	*values;
	t_tuple		sphere_to_ray;
	t_quadractic	equation;

	values = ft_calloc(1, sizeof(t_intersect));
	if (!values)
		return (NULL);
	equation.a = dot_tuple(ray.direction, ray.direction);
	equation.b = 2.0 * dot_tuple(sphere_to_ray, ray.direction);
	equation.c = dot_tuple(sphere_to_ray, sphere_to_ray) - 1;
	equation.discriminant = get_discriminant(equation);
	if (equation.discriminant < 0)
	{
		values.distance[0] = -1;
		values.distance[1] = -1;
		return (values);
	}
	
	
}
