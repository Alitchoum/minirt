/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:20:04 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:27:08 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_mode(int keysym, t_scene *scene)
{
	if (keysym == 'v')
		scene->mode = MODE_VIEW;
	else if (keysym == 'l')
		scene->mode = MODE_LIGHT;
	else if (keysym == 's')
		scene->mode = MODE_SPHERE;
	else if (keysym == 'c')
		scene->mode = MODE_CYLINDER;
	else if (keysym == 'p')
		scene->mode = MODE_PLANE;
}

void	transform_objs_group(t_scene *scene, int object_type, int keysym)
{
	int	i;

	i = 0;
	while (i < scene->obj_count)
	{
		if (scene->objects[i].type == object_type)
		{
			translation(&scene->objects[i].position, keysym);
			if (object_type == MODE_CYLINDER)
				rotation(&scene->objects[i].orientation, keysym);
			else if (object_type == MODE_PLANE)
				rotation(&scene->objects[i].normal, keysym);
			scaling_radius(&scene->objects[i].radius_squared, keysym);
			if (object_type == MODE_CYLINDER)
			{
				scaling_height(&scene->objects[i].half_height, keysym);
				recomp_basis(&scene->objects[i], keysym);
			}
		}
		i++;
	}
}

void	handle_action(int keysym, t_scene *scene)
{
	if (scene->mode == MODE_VIEW)
	{
		translation(&scene->camera.position, keysym);
		rotation(&scene->camera.orientation, keysym);
	}
	else if (scene->mode == MODE_LIGHT)
		translation(&scene->light.position, keysym);
	else if (scene->mode == MODE_SPHERE
		||scene->mode == MODE_CYLINDER
		|| scene->mode == MODE_PLANE)
		transform_objs_group(scene, scene->mode, keysym);
}

int	do_keypress(int keysym, t_scene *scene)
{
	if (keysym == XK_Escape)
		shut_down(scene, EXIT_SUCCESS);
	else
	{
		handle_mode(keysym, scene);
		handle_action(keysym, scene);
	}
	render_image(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img, 0, 0);
	return (0);
}
