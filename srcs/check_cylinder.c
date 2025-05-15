/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:12:43 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:15:02 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	fill_cylinder_data(t_object *cylinder, char **elements)
{
	if (!update_tuple(&cylinder->position, elements[1], 1))
		return (0);
	if (!update_tuple(&cylinder->orientation, elements[2], 0))
		return (0);
	if (!is_valid_orientation_range(cylinder->orientation))
		return (ft_putstr_fd("Error: Ratio isn't in a valid range.\n", 2), 0);
	cylinder->orientation = normalize(cylinder->orientation);
	if (!is_valid_double(elements[3]) || !is_valid_double(elements[4]))
		return (ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	cylinder->radius = ft_atof(elements[3]) / 2;
	cylinder->height = ft_atof(elements[4]);
	if (!update_color(&cylinder->color, elements[5]))
		return (0);
	return (1);
}

int	check_cylinder(char *line, t_object *cylinder, int *object_index)
{
	char	**elements;

	elements = NULL;
	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split cylinder failed.\n", 2), 0);
	if (count_line_tab(elements) != 6)
		return (free_split(elements),
			ft_putstr_fd("Error: Nb of elements of plane isn't valid.\n", 2), 0);
	if (!fill_cylinder_data(cylinder, elements))
		return (free_split(elements), 0);
	free_split(elements);
	cylinder->type = CYLINDER;
	*object_index += 1;
	return (1);
}
