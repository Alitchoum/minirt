#include "minirt.h"

// Doesn't take into account colour of the light
void	apply_lighting(t_scene *scene, t_intersection *hit, int *final_color)
{
	t_tuple	light_direction;
	double	dot;
	double	light_scalar;

	light_direction = subtract_tuple(scene->light.position, hit->world_position);
	light_direction = normalize_tuple(light_direction);

	if (is_in_shadow(scene, hit->world_position, scene->light.position))
	{
		light_scalar = scene->ambient.ratio;
	}
	else
	{
		dot = dot_tuple(hit->world_normal, light_direction);
		if (dot < 0)
			dot = 0;
		light_scalar = dot * scene->light.ratio;
		light_scalar += scene->ambient.ratio;
		light_scalar += specular_reflect(hit->world_position, hit->world_normal, light_direction, scene);
		if (light_scalar > 1.0)
			light_scalar = 1;
	}
	*final_color = rgb_to_int(hit->object->color, light_scalar);
}

double	specular_reflect(t_tuple hit_point, t_tuple normal, t_tuple light_dir, t_scene *scene)
{
	t_tuple		cam_dir;
	t_tuple		reflect_dir;
	double		dot_reflect_cam; // multi entre direction reflection et direction de la camera
	double		specular;
	double		coeff = 0.7;
	double		shininess = 100;

	cam_dir = normalize_tuple(subtract_tuple(scene->camera.position, hit_point));
	reflect_dir = subtract_tuple(scale_tuple(normal, 2.0 * dot_tuple(normal, light_dir)),light_dir);
	reflect_dir = normalize_tuple(reflect_dir);
	dot_reflect_cam = dot_tuple(reflect_dir, cam_dir);
	if (dot_reflect_cam < 0)
		dot_reflect_cam = 0;
	specular = coeff * scene->light.ratio * pow(dot_reflect_cam, shininess);
	return (specular);
}
