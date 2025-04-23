/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:46:17 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/23 15:37:19 by alsuchon         ###   ########.fr       */
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

void	print_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("[%s]\n", s[i]);
		i++;
	}	
}

int	is_valid_int(char *s)
{
	int		i;
	int		nb;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i++] == '-')
			sign = -sign;
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (ft_putstr_fd("Error: Not a number.\n", 2), 0);
		nb = s[i] - '0';
		if ((sign == 1 && result > (INT_MAX - nb) / 10) ||
			(sign == -1 && -result < (INT_MIN + nb) / 10))
			return (ft_putstr_fd("Error: Overflow value.\n", 2), 0);
		result = result * 10 + nb;
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
			return (ft_putstr_fd("Error: Not a number.\n", 2), 0);
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
//Fonction for count nb of lines of array of strings
int	count_line_tab(char **s)
{
	int	count;

	count = 0;
	while (s[count] != NULL)
		count++;
	return (count);
}