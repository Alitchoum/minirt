/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:13:47 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/04 18:37:31 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// RETURNS DOT PRODUCT OF TWO VECTORS
// Multiplies the matching variables together then adds them up


t_vector	get_vec3(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;

	return (new);
}

float	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

float	vec3_dot(t_vector a, t_vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector	vec3_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vec3_subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}


// transofrming rgb to final int colour (taking into account light scalar)
int	rgb_to_int(t_color colour, double light_scalar)
{
	colour.r *= light_scalar;
	colour.g *= light_scalar;
	colour.b *= light_scalar;
	return (colour.r << 16 | colour.g << 8 | colour.b);
}

// returns what you need to multiply the colour by to take into account light
// Essentially, solving the quadratic equation to find closest intersection to the camera
// between 0 and 1
double	solve_min_quadratic(double a, double b, double discriminant)
{
	double	t0;
	double	t1_closest;

	t0 = (-b + sqrt(discriminant)) / (2.0 * a);
	t1_closest = (-b - sqrt(discriminant)) / (2.0 * a);

	if (t0 < t1_closest)
		return (t0);
	return (t1_closest);
}

t_vector	vec3_scale(t_vector a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	return (a);
}

int	get_colour(t_vector ray_origin, t_vector ray_direction, double radius)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_color	colour;
	t_vector closest_hit_position;
	double	min_quad;

	colour.r = 255;
	colour.g = 0;
	colour.b = 255;
	double	light_scaler = 0.5; // between 0 and 1 (1 full colour, 0 black)

	a = vec3_dot(ray_direction, ray_direction);
	b = 2.0f * vec3_dot(ray_origin, ray_direction);
	c = vec3_dot(ray_origin, ray_origin) - (radius * radius);

	discriminant = get_discriminant(a, b, c);
	printf("discriminant: %f\n", discriminant);
	// IF NO INTERSECTION(S) WERE FOUND, return BLACK
	if (discriminant < 0.0)
		return (0);
	// ELSE, SOlVE THE EQUATION TO GET THE CLOSEST POINT OF INTERSECTION TO THE CAMERA
	min_quad = solve_min_quadratic(a, b, discriminant);
	closest_hit_position = vec3_add(ray_origin, vec3_scale(ray_direction, min_quad));
	return (rgb_to_int(colour, light_scaler));
}

t_vector	vec3_normalize(t_vector v)
{
	double	length;

	length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	if (length == 0)
		return (v);
	v.x /= length;
	v.y /= length;
	v.z /= length;
	return (v);

}

int	render_image(t_scene *scene)
{
	//double aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distorting
	t_vector camera_position = get_vec3(0.0, 0.0, 1.0);
	//t_vector camera_orientation = get_vec3(0.0, 0.0, -1.0);
	t_vector ray_direction;
	double	normalised_row;
	double	normalised_col;

	double sphere_radius = 6.0f;
	//double fov = 180.0;
	//double fov_scale = tan((fov * 0.5) * M_PI / 180.0);

	int	col = 0;
	int	row = 0;

	// PUT A COLOUR ON EACH PIXEL OF THE SCREEN
	while (row < W_HEIGHT)
	{
		printf("row %i\n", row);
		col = 0;
		while (col < W_WIDTH)
		{
			// NORMALIZE THE PIXEL BETWEEN -1 AND 1
			normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);
			normalised_row = (double)row / (double)W_HEIGHT * 2 - 1;
			ray_direction.x = normalised_col; //* aspect_ratio * fov_scale;
			ray_direction.y = normalised_row; //* fov_scale;
			ray_direction.z = 1;

			ray_direction = vec3_normalize(ray_direction);
			// FIND THE COLOUR THE PIXEL SHOULD BE
			int colour = get_colour(camera_position, ray_direction, sphere_radius);
			//if (colour != 0)
			//	printf("colour: %i\n", colour);
			my_mlx_pixel_put(scene, col, row, colour);
			col++;
		}
		row++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_scene scene;

	ft_bzero(&scene, sizeof(t_scene));

	if (ac != 2)
		return (ft_putstr_fd("Error:Numbers of arguments no valid.\n", 2), EXIT_FAILURE);
	if (!parse_scene(av[1], &scene))
		return (EXIT_FAILURE);

	// INITIALISE MLX
	initialise_mlx(&scene);

	// DRAW THE IMAGE
	render_image(&scene);
	
	// PUT IT TO THE WINDOW
	mlx_put_image_to_window(scene.mlx_ptr, scene.win_ptr, scene.img, 0, 0);

	// MLX LOOP
	mlx_loop(scene.mlx_ptr);

	free(scene.ambient.color);
	return (0);
}
