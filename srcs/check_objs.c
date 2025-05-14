/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:53:43 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/14 17:30:03 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	update_color(t_color *color, char *line)
{
	char	**rgb = NULL;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (ft_putstr_fd("Error: Split color failed.\n", 2), 0);
	if (count_line_tab(rgb) != 3)
		return (free_split(rgb), ft_putstr_fd("Error Nb of elements isn't valid.\n", 2), 0);
	if (!is_valid_int(rgb[0]) || !is_valid_int(rgb[1]) || !is_valid_int(rgb[2]))
		return (free_split(rgb), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if ((color->r < 0 || color->r > 255) || (color->g < 0 || color->r > 255) ||
		(color->b < 0 || color->b > 255))
		return (free_split(rgb), ft_putstr_fd("Error: Color isn't in a valid range.\n", 2), 0);
	color->r /= (double)255.0;
	color->g /= (double)255.0;
	color->b /= (double)255.0;
	free_split(rgb);
	return (1);
}

static int	update_tuple(t_tuple *tuple, char *line, double w)
{
	char	**coords = NULL;

	coords = ft_split(line, ',');
	if (!coords)
		return (ft_putstr_fd("Error: Split vector failed.\n", 2), 0);
	if (count_line_tab(coords) != 3)
		return (free_split(coords), ft_putstr_fd("Error Nb of elements isn't valid.\n", 2), 0);
	if (!is_valid_double(coords[0]) || !is_valid_double(coords[1]) || !is_valid_double(coords[2]))
		return (free_split(coords), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	tuple->x = ft_atof(coords[0]);
	tuple->y = ft_atof(coords[1]);
	tuple->z = ft_atof(coords[2]);
	tuple->w = w;
	free_split(coords);
	return (1);
}

int	check_sphere(char *line, t_object *sphere, int *object_index)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split sphere failed.\n", 2), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of sphere isn't valid.\n", 2), 0);
	if (!update_tuple(&sphere->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!is_valid_double(elements[2]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	// Changed for radius instead of diameter
	sphere->radius = ft_atof(elements[2]) / 2;
	if (!update_color(&sphere->color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	sphere->type = SPHERE;
	*object_index += 1;
	return (1);
}

int	check_plane(char *line, t_object *plane, int *object_index)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split plane failed.\n", 2), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of plane isn't valid.\n", 2), 0);
	if (!update_tuple(&plane->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&plane->normal, elements[2], 1))
		return (free_split(elements), 0);
	if (!is_valid_orientation_range(plane->normal))
		return (free_split(elements), ft_putstr_fd("Error: Plane ratio isn't in a valid range.\n", 2), 0);
	if (!update_color(&plane->color, elements[3]))
		return (free_split(elements), 0);
	plane->type = PLANE;
	*object_index += 1;
	return (1);
}

int	check_cylinder(char *line, t_object *cylinder, int *object_index)
{
	char	**elements = NULL;
	
	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split cylinder failed.\n", 2), 0);
	if (count_line_tab(elements) != 6)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of cylinder isn't valid.\n", 2), 0);
	if (!update_tuple(&cylinder->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&cylinder->orientation, elements[2], 0))
		return (free_split(elements), 0);
	if (!is_valid_orientation_range(cylinder->orientation))
		return (free_split(elements), ft_putstr_fd("Error: Cylinder ratio isn't in a valid range.\n", 2), 0);
	cylinder->orientation = normalize_tuple(cylinder->orientation);
	if (!is_valid_double(elements[3]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	cylinder->radius = ft_atof(elements[3]) / 2;
	if (!is_valid_double(elements[4]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	cylinder->height = ft_atof(elements[4]);
	if (!update_color(&cylinder->color, elements[5]))
		return (free_split(elements), 0);
	cylinder->type = CYLINDER;
	*object_index += 1;
	return (1);
}
