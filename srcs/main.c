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

float	get_discriminant(float a, float b, float c)
{
	return ((b * b) - 4 *(a * c));
}

float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


int	hit_sphere(int x, int y, t_vector origin, t_vector orientation, int radius)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	orientation.x = x;
	orientation.y = y;

	a = dot_product(orientation, orientation);
	b = 2 * dot_product(origin, orientation);
	c = dot_product(origin, origin) - (radius * radius);

	discriminant = get_discriminant(a, b, c);
	printf("discriminant: %f\n", discriminant);
	
	return (discriminant >= 0);
}

int	render_image(t_scene *scene)
{
	t_vector camera;
	t_vector orientation;

	camera.x = -50.0;
	camera.y = 0.0;
	camera.z = 20.0;
	orientation.x = 0;
	orientation.y = 0;
	orientation.z = -1.0;

	float radius = 55;

	int	width = 0;
	int	height = 0;

	// BACKGROUND
	while (height < W_HEIGHT)
	{
		width = 0;
		while (width < W_WIDTH)
		{
			if (hit_sphere(width, height, camera, orientation, radius))
				my_mlx_pixel_put(scene, width, height, YELLOW);
			width++;
		}
		height++;
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
