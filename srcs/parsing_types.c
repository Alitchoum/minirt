/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:37:58 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/14 17:30:45 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Verifier si float plusieurs "." -> OK
//Pour overflow ajouter verif direct dans atoi 
//et atof putot que pour chaque données??

//Parsing of the line ambient light (type A)
static int	check_ambient(char *line, t_scene *scene)
{
	char	**elements = NULL;
	
	elements = ft_split_set(line, " \t\r\v\f");
	if (!elements)
		return (ft_putstr_fd("Error: Split ambient failed.\n", 2), 0);
	if (count_line_tab(elements) != 3)
			return (free_split(elements), ft_putstr_fd("Error Nb of elements of ambient isn't valid.\n", 2), 0);
	if (!is_valid_double(elements[1]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	scene->ambient.ratio = ft_atof(elements[1]);
	if (!update_color(&scene->ambient.color, elements[2]))
		return (free_split(elements), 0);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (free_split(elements), ft_putstr_fd("Error: Ambient ratio isn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

//Parsing of the line camera (type C)
static int	check_camera(char *line, t_scene *scene)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);// corriger split_set
	if (!elements)
		return (ft_putstr_fd("Error: Split camera failed.\n", 2), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of camera isn't valid.\n", 2), 0);
	if (!update_tuple(&scene->camera.position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&scene->camera.orientation, elements[2], 0))
		return (free_split(elements), 0);
	if ((scene->camera.orientation.x < -1 || scene->camera.orientation.x > 1) || (scene->camera.orientation.y < -1 || scene->camera.orientation.y > 1) ||
		(scene->camera.orientation.x < -1 || scene->camera.orientation.x > 1))
		return (free_split(elements), ft_putstr_fd("Error: Cam orientation isn't in a valid range.\n", 2), 0);
	if (!is_valid_int(elements[3]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	scene->camera.fov = ft_atoi(elements[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180) 	
		return (free_split(elements), ft_putstr_fd("Error: Cam ratio isn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

static int	check_light(char *line, t_scene *scene)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split light failed.\n", 2), 0);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of light isn't valid.\n", 2), 0);
	if (!update_tuple(&scene->light.position, elements[1], 1))
		return (free_split(elements), 0);
	if (!is_valid_double(elements[2]))
		return (free_split(elements), ft_putstr_fd("Error: Isn't a number.\n", 2), 0);
	scene->light.ratio = ft_atof(elements[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		return (free_split(elements), ft_putstr_fd("Error: Light ratio isn't in a valid range.\n", 2), 0);
	if (!update_color(&scene->light.color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	return (1);
}

//Function for parse elements of type line by line
int	parse_element_line(char *line, t_scene *scene, int *element_index)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		if (!check_ambient(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (!check_camera(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "L", 1) == 0)
	{
		if (!check_light(line, scene))
			return (0);
	}
	else if (ft_strncmp(line, "sp", 2) == 0)
	{
		if (!check_sphere(line, &scene->objects[*element_index], element_index))
			return (0);
	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		if (!check_plane(line, &scene->objects[*element_index], element_index))
			return (0);
	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		if (!check_cylinder(line, &scene->objects[*element_index], element_index))
			return (0);
	}
	return (1);
}

