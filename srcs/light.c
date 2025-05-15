/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:48:11 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:12 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	apply_lighting(t_scene *scene, t_xs *hit, int *final_color)
{
	t_tuple	light_direction;
	double	cos_angle;
	double	scalar;

	light_direction = subtract(scene->light.position, hit->world_position);
	light_direction = normalize(light_direction);
	if (is_in_shadow(scene, hit->object, hit))
		scalar = scene->ambient.ratio;
	else
	{
		cos_angle = dot(hit->world_normal, light_direction);
		if (cos_angle < 0)
			cos_angle = 0;
		scalar = cos_angle * scene->light.ratio;
		scalar += scene->ambient.ratio;
		scalar += specular_reflect(hit->world_position, hit->world_normal, light_direction, scene);
		if (scalar > 1.0)
			scalar = 1;
	}
	*final_color = rgb_to_int(hit->object->color, scalar);
}

double	specular_reflect(t_tuple hit_point, t_tuple normal, t_tuple light_dir, t_scene *scene)
{
	t_tuple		cam_dir;
	t_tuple		reflect_dir;
	double		dot_reflect_cam;
	double		specular;
	double		coeff;
	double		shininess;

	coeff = 0.7;
	shininess = 100.0;
	cam_dir = normalize(subtract(scene->camera.position, hit_point));
	reflect_dir = subtract(scale(normal, 2.0 * dot(normal, light_dir)),light_dir);
	reflect_dir = normalize(reflect_dir);
	dot_reflect_cam = dot(reflect_dir, cam_dir);
	if (dot_reflect_cam < 0)
		dot_reflect_cam = 0;
	specular = coeff * scene->light.ratio * pow(dot_reflect_cam, shininess);
	return (specular);
}