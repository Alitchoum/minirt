/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:40:35 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/24 19:02:52 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersection_plane(t_ray ray, t_object *plane)
{
	t_tuple	diff;
	double	denominator;
	double	numerator;
	double	dist;
	t_intersection xs;

	xs.hit_distance = -1;

	denominator = dot_tuple(plane->normal, ray.direction);
	if (is_equal(denominator, 0.0))
		return	(xs);
	diff = subtract_tuple(plane->position, ray.origin);
	numerator = dot_tuple(plane->normal, diff);
	dist = numerator / denominator;
	if (dist < EPSILON)
		return (xs);
	xs.hit_distance = dist;
	return (xs);
}

/*static int get_color_plane(t_ray ray, t_plane *plane, t_scene *scene)
{
	t_tuple	hit_point;
	t_tuple	light_dir;
	double	dist;
	double	dot;
	
	dist = intersection_plane(ray, plane);
	if (dist < EPSILON) // Si il n'y a pas d'intersection
		return (0);
	//printf("hit dist %f\n", dist);
	hit_point = add_tuple(ray.origin, scale_tuple(ray.direction, dist));

	light_dir = subtract_tuple(scene->light.position, hit_point);
	light_dir = normalize_tuple(light_dir);
	dot = dot_tuple( plane->normal, light_dir);
	if (dot < 0)
		dot = 0;
	double light_scaler = dot * scene->light.ratio;
	light_scaler += scene->ambient.ratio;
	if (light_scaler > 1.0)
		light_scaler = 1.0;
	return (rgb_to_int(plane->color, light_scaler));
}

int render_image_plane(t_scene *scene)
{
	double aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distortion
	t_ray	ray;
	t_tuple	ray_direction;
	double	normalised_row;
	double	normalised_col;
	int	col = 0;
	int	row = 0;
	int	i;
	int	color;
	double	fov_scale = tan((scene->camera.fov * 0.5) * M_PI / 180.0);
	
	t_tuple cam_orientation = normalize_tuple(scene->camera.orientation);
	t_tuple tmp_up = vector(0, 1, 0); // Up global, à adapter si trop proche du forward
	if (fabs(dot_tuple(tmp_up, cam_orientation)) > 0.999) // Si parallèle on change les coordonnees
		tmp_up = vector(0, 0, 1);

	t_tuple right = normalize_tuple(cross_tuple(tmp_up, cam_orientation));
	t_tuple up = cross_tuple(cam_orientation, right);
	
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			normalised_col = (2 * ((col + 0.5) / W_WIDTH) - 1) * aspect_ratio * fov_scale;
			normalised_row = (1 - 2 * ((row + 0.5) / W_HEIGHT)) * fov_scale;
			ray_direction = add_tuple(add_tuple(scale_tuple(right, normalised_col), scale_tuple(up, normalised_row)), cam_orientation);
			ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
			i = 0;
			color = 0;
			while (i < scene->nb_pl)
			{
				color = get_color_plane(ray, &scene->planes[i], scene);
				if (color != 0)
				{
					my_mlx_pixel_put(scene, col, row, color); 
					break;
				}
			i++;
		}
		col++;
		}
		row++;
	}
	return (0);
}*/
