/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:46:17 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/13 17:43:47 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

//Fonction for count nb of lines of array of strings
int	count_line_tab(char **s)
{
	int	count;

	count = 0;
	while (s[count] != NULL)
		count++;
	return (count);
}

int	is_valid_int(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_double(char *s)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (point == 1)
				return (0);
			point = 1;
		}
		else if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_orientation_range(t_tuple orientation)
{
	if ((orientation.x < -1 || orientation.x > 1)
		|| (orientation.y < -1 || orientation.y > 1)
		|| (orientation.z < -1 || orientation.z > 1))
		return (0);
	return (1);
}
