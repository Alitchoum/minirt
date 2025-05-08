/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:13:47 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/20 17:25:40 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	do_keypress(int keysym, t_scene *scene);
int	shut_down(t_scene *scene);

int	main(int ac, char **av)
{
	t_scene scene;

	ft_bzero(&scene, sizeof(t_scene));

	if (ac != 2)
		return (ft_putstr_fd("Error:Numbers of arguments no valid.\n", 2), EXIT_FAILURE);
	if (!parse_scene(av[1], &scene))
		return (EXIT_FAILURE);

	//run_matrix_tests();
	//exit(1);
	// INITIALISE MLX
	initialise_mlx(&scene);

	// DRAW THE IMAGE
	render_image(&scene);
	mlx_key_hook(scene.win_ptr, do_keypress, &scene);
	mlx_hook(scene.win_ptr, 17, 0, shut_down, &scene);

	
	// PUT IT TO THE WINDOW
	mlx_put_image_to_window(scene.mlx_ptr, scene.win_ptr, scene.img, 0, 0);

	// MLX LOOP
	mlx_loop(scene.mlx_ptr);
	return (0);
}

int	do_keypress(int keysym, t_scene *scene)
{
	if (keysym == XK_Escape)
		shut_down(scene);
	else if (keysym == 115)
	{
		printf("[S]cale pressed\n");
		scene->objects[0].diametre *= 1.1;
	}
	else if (keysym == 65363)
	{
		printf("Right arrow pressed (translate right)\n");
		scene->objects[0].position.x += 0.1;
	}
	else if (keysym == 65361)
	{
		printf("Left arrow pressed (translate left)\n");
		scene->objects[0].position.x -= 0.1;
	}
	else if (keysym == 65362)
	{
		printf("Up arrow pressed (translate up)\n");
		scene->objects[0].position.y += 0.1;
	}
	else if (keysym == 65364)
	{
		printf("Down arrow pressed (translate down)\n");
		scene->objects[0].position.y -= 0.1;
	}
	else if (keysym == 98)
	{
		printf("[F]orward pressed (translate closer on z)\n");
		scene->objects[0].position.z += 0.1;
	}
	else if (keysym == 102)
	{
		printf("[B]ackward pressed (translate closer on z)\n");
		scene->objects[0].position.z -= 0.1;
	}
	else
		printf("pressed key: %i\n", keysym);
	render_image(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img, 0, 0);
	return (0);
}

int	shut_down(t_scene *scene)
{
	mlx_destroy_image(scene->mlx_ptr, scene->img);
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	mlx_destroy_display(scene->mlx_ptr);
	free(scene->mlx_ptr);
	// FREE ALL THE SHIT IN THE SCENE
	
	free(scene->objects);
	exit(0);
	return (0);
}
