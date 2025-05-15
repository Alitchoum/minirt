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
int	shut_down(t_scene *scene, int status);

int	main(int ac, char **av)
{
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./miniRT scene.rt\n", 2);
		return (EXIT_FAILURE);
	}
	if (!parse_scene(av[1], &scene))
		return (EXIT_FAILURE);
	initialise_mlx(&scene);
	render_image(&scene);
	mlx_key_hook(scene.win_ptr, do_keypress, &scene);
	mlx_hook(scene.win_ptr, 17, 0, shut_down, &scene);
	mlx_put_image_to_window(scene.mlx_ptr, scene.win_ptr, scene.img, 0, 0);
	mlx_loop(scene.mlx_ptr);
	return (0);
}

int	shut_down(t_scene *scene, int status)
{
	if (scene->img != NULL)
		mlx_destroy_image(scene->mlx_ptr, scene->img);
	if (scene->win_ptr != NULL)
		mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	if (scene->mlx_ptr != NULL)
		mlx_destroy_display(scene->mlx_ptr);
	free(scene->mlx_ptr);
	free(scene->objects);
	exit(status);
	return (0);
}
