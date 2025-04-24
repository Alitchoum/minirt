/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:30:30 by alize             #+#    #+#             */
/*   Updated: 2025/04/24 17:42:34 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// int	check_intersection(t_ray ray, t_object *obj, t_scene *scene)
// {
// 	if (obj->type == SPHERE)
// 		sphere_intersection(ray, &scene->spheres[obj->index_sp], scene);
// 	if (obj->type == PLANE)
// 		plane_intersection(ray, &scene->planes[obj->index_pl], scene);
// 	return (1);
// }

// int	render_image_sphere(t_scene *scene)
// {
// 	double aspect_ratio;
// 	t_ray	ray;
// 	t_tuple ray_direction;
// 	//t_vector camera_orientation;
// 	double	normalised_row;
// 	double	normalised_col;
// 	double	fov_scale;
// 	int	col = 0;
// 	int	row = 0;
// 	int	i;
// 	int	color;
	
// 	aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distorting
// 	fov_scale = tan((scene->camera.fov * 0.5) * M_PI / 180.0);
// 	// PUT A COLOUR ON EACH PIXEL OF THE SCREEN
// 	while (row < W_HEIGHT)
// 	{
// 		col = 0;
// 		while (col < W_WIDTH)
// 		{
// 			// NORMALIZE THE PIXEL BETWEEN -1 AND 1
// 			normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);
// 			normalised_row = (double)row / (double)W_HEIGHT * 2 - 1;

// 			// CALCULATE RAY DIRECTION
// 			ray_direction = vector(normalised_col * aspect_ratio * fov_scale, normalised_row * fov_scale, 1);

// 			// CREATE A NEW RAY (ORIGIN, DIRECTION)
// 			ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
// 			//FIND THE COLOUR THE PIXEL SHOULD BE
// 			i = 0;
// 			color = 0;
// 			while (i < scene->nb_sp)
// 			{
// 				color = get_color(ray, &scene->objects[i], scene);
// 				if (color != 0)
// 				{
// 					//printf("color is : %i\n", color);
// 					my_mlx_pixel_put(scene, col, row, color);
// 					break ;
// 				}
// 				i++;
// 			}
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (0);
// }