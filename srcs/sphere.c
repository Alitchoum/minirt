
#include "minirt.h"

void	prep_sphere_quadratic(t_quadratic *quadratic, t_ray ray, t_object *sphere)
{
	t_tuple	diff_sphere_camera;

	diff_sphere_camera = subtract_tuple(ray.origin, sphere->position);
	quadratic->a = dot_tuple(ray.direction, ray.direction);
	quadratic->b = 2.0f * dot_tuple(diff_sphere_camera, ray.direction);
	quadratic->c = dot_tuple(diff_sphere_camera, diff_sphere_camera) - 1;//(pow((sphere->diametre * 0.5), 2));
	quadratic->discriminant = get_discriminant(quadratic->a, quadratic->b, quadratic->c);
}

void	prep_quadratic(t_quadratic *quadratic, t_ray ray, t_object *object)
{
	if (object->type == SPHERE)
		prep_sphere_quadratic(quadratic, ray, object);
	else if (object->type == CYLINDER)
		prep_cylinder_quadratic(quadratic, ray, object);
	//else if (object->type == PLANE)
	//	prep_plane_quadratic(quadratic, ray, object);
	return ;
}



