/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:46:17 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/20 16:56:42 by alize            ###   ########.fr       */
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

void	print_list(t_list *lines)
{
	t_list	*current;

	current = lines;
	while (current)
	{
		printf("[%s]\n", (char *)current->content);
		current = current->next;
	}	
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
	if ((orientation.x < -1 || orientation.x > 1) ||
		(orientation.y < -1 || orientation.y > 1) ||
		(orientation.z < -1 || orientation.z > 1))
		return (0);
	return (1);
}
