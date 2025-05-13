/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:31:14 by caburges          #+#    #+#             */
/*   Updated: 2025/05/13 13:10:48 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pixel_color(t_scene *scene, t_ray ray, t_object *objects);
void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour);
double	radians(double degrees);

int	render_image(t_scene *scene)
{
	double	aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distorting
	t_ray	ray;
	t_tuple	ray_direction;
	double	normalised_row;
	double	normalised_col;
	t_tuple	world_up = vector(0, 1, 0); // Default up direction
	double	fov_scale = tan(radians((scene->camera.fov * 0.5)));
	t_tuple	horizontal, vertical;

	// Change the up vector if the camera orientation is along x or z axis
	if (fabs(scene->camera.orientation.x) < 1e-6 && fabs(scene->camera.orientation.z) < 1e-6)
		world_up = vector(0, 0, 1); // Change to use z-up

	// Calculate horizontal and vertical vectors on the fly based on the camera orientation
	horizontal = normalize_tuple(cross_tuple(scene->camera.orientation, world_up));
	vertical = normalize_tuple(cross_tuple(horizontal, scene->camera.orientation));

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
			normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);
			normalised_row = ((double)row / (double)W_HEIGHT * 2 - 1);

            // Calculate the direction of the ray based on the pixel
			t_tuple offset_right = scale_tuple(horizontal, normalised_col * aspect_ratio * fov_scale);
			t_tuple offset_up = scale_tuple(vertical, normalised_row * fov_scale);
			t_tuple combined_offset = add_tuple(offset_right, offset_up);
			t_tuple look_at = add_tuple(scene->camera.position, scene->camera.orientation);
			t_tuple view_dir = subtract_tuple(look_at, scene->camera.position);
			ray_direction = normalize_tuple(add_tuple(combined_offset, view_dir));

            // Create the ray and get the pixel color
			ray = new_ray(scene->camera.position, ray_direction);
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
