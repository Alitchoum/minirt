/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:14 by caburges          #+#    #+#             */
/*   Updated: 2025/04/15 17:51:52 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pixel_color(t_scene *scene, t_ray ray, t_object *objects);
void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour);

int	render_image(t_scene *scene)
{
	double aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distorting
	t_ray	ray;

	t_tuple ray_direction;
	//t_vector camera_orientation;
	//double	normalised_row;
	//double	normalised_col;
	double	fov_scale = tan(radians((scene->camera.fov * 0.5)));

	int	col = 0;
	int	row = 0;
	int	color;
	// PUT A COLOUR ON EACH PIXEL OF THE SCREEN
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			// NORMALIZE THE PIXEL BETWEEN -1 AND 1
			double u = (2.0 * (col + 0.5) / (double)W_WIDTH - 1.0) * aspect_ratio * fov_scale;
        		double v = (1.0 - 2.0 * (row + 0.5) / (double)W_HEIGHT) * fov_scale;

        		ray_direction = vector(u, v, 1);
        		ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
			//normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);
			//normalised_row = -((double)row / (double)W_HEIGHT * 2 - 1);
			//ray_direction = vector(normalised_col * fov_scale_x, normalised_row * fov_scale_y, 1);
			//ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
			color = get_pixel_color(scene, ray, scene->objects);
			my_mlx_pixel_put(scene, col, row, color);
			col++;
		}
		row++;
	}
	printf("Finished render\n");
	return (0);
}

// need to understand how to manage shadows...
int	get_pixel_color(t_scene *scene, t_ray ray, t_object *objects)
{
	int	final_color;
	t_intersection	closest_intersection;

	final_color = 0;
	closest_intersection = get_closest_intersection(scene, ray, objects, NULL);
	if (closest_intersection.hit_distance < 0)
		return (0); // but could also just be a shadow??...
	apply_lighting(scene, &closest_intersection, &final_color);
	//apply_shadow(scene, &closest_intersection, ray, &final_color);
	
	return (final_color);
}

void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour)
{
	char	*dst;

	if ((x >= 0 && x < W_WIDTH) && (y > 0 && y < W_HEIGHT))
	{
		dst = map->addr + (y * map->l_l + x * (map->bpp / 8));
		*(unsigned int *)dst = colour;
	}
}
