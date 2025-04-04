/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:13:47 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/04 14:59:51 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene scene;
	
	if (ac != 2)
		return (ft_putstr_fd("Error:Numbers of arguments no valid.\n", 2), EXIT_FAILURE);
	if (!read_and_parse_scene(av[1], &scene))
		return (EXIT_FAILURE);
	return (0);
}