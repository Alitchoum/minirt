/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:13:47 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/23 15:51:51 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return (0);
}
