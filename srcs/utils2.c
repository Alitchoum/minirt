/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:06:21 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:15:52 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Function for check if the extension is terminate by .rt
int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.'
		|| file[len - 2] != 'r' || file[len - 1] != 't')
	{
		ft_putstr_fd("Error: File extension isn't valid.\n", 2);
		return (0);
	}
	return (1);
}
