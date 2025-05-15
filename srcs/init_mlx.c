/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:47:44 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:47:46 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialise_mlx(t_scene *s)
{
	s->mlx_ptr = mlx_init();
	if (!s->mlx_ptr)
	{
		ft_putstr_fd("ERROR: failed initialisating mlx\n", 2);
		shut_down(s, EXIT_FAILURE);
	}
	s->win_ptr = mlx_new_window(s->mlx_ptr, W_WIDTH, W_HEIGHT, "MiniRT");
	if (!s->win_ptr)
	{
		ft_putstr_fd("ERROR: failed initialisating mlx window\n", 2);
		shut_down(s, EXIT_FAILURE);
	}
	s->img = mlx_new_image(s->mlx_ptr, W_WIDTH, W_HEIGHT);
	if (!s->img)
	{
		ft_putstr_fd("ERROR: failed to get mlx new img\n", 2);
		shut_down(s, EXIT_FAILURE);
	}
	s->addr = mlx_get_data_addr(s->img, &s->bpp, &s->l_l, &s->end);
}
