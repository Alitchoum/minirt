/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:37:58 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/16 16:54:31 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Verifier si float plusieurs "."

//Fonction for count nb of lines of array of strings
static int	count_line_tab(char **s)
{
	int	count;

	count = 0;
	while (s[count] != NULL)
		count++;
	return (count);
}

static void	print_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("[%s]\n", s[i]);
		i++;
	}	
}

// int	check_tab_is_digit(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (!ft_isdigit(tab[i]))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

//create & return a struct with code color RGB
//CHECKS: int overflow; isdigit; split with isspace
static int	update_color(t_color *color, char *line)
{
	char	**rgb = NULL;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (ft_putstr_fd("Error: Split color failed.\n", 2), 0);
	if (count_line_tab(rgb) != 3)
		return (free_split(rgb), ft_putstr_fd("Error Nb of elements isn't valid.\n", 2), 0);
	print_tab(rgb);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if ((color->r < 0 || color->r > 255) || (color->g < 0 || color->r > 255) ||
		(color->b < 0 || color->b > 255))
		return (free_split(rgb), ft_putstr_fd("Error: Color isn't in a valid range.\n", 2), 0);
	free_split(rgb);
	return (1);
}

static int	update_vector(t_vector *vector, char *line)
{
	char	**coordonates = NULL;

	coordonates = ft_split(line, ',');
	if (!coordonates)
		return (ft_putstr_fd("Error: Split vector failed.\n", 2), 0);
	if (count_line_tab(coordonates) != 3)
		return (free_split(coordonates), ft_putstr_fd("Error Nb of elements isn't valid.\n", 2), 0);
	vector->x = ft_atof(coordonates[0]);
	vector->y = ft_atol(coordonates[1]);
	vector->z = ft_atol(coordonates[2]);
	//ajouter ici verif overflow pour coordonees??
	free_split(coordonates);
	return (1);
}

//Parsing of the line ambient light (type A)
static int	check_ambient(char *line, t_scene *scene)
{
	char	**elements = NULL;
	
	elements = ft_split_set(line, " \t\r\v\f");
	if (!elements)
			return (ft_putstr_fd("Error: Split ambient failed.\n", 2), 0);
	if (count_line_tab(elements) != 3)
		return (free_split(elements), ft_putstr_fd("Error Nb of elements of ambient isn't valid.\n", 2), 0);
	printf("split ambiant elements:\n");
	print_tab(elements);
	scene->ambient.ratio = ft_atof(elements[1]);
	printf("%f\n", scene->ambient.ratio);
	if (!update_color(&scene->ambient.color, elements[2]))
		return (free_split(elements), 0);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (free_split(elements), ft_putstr_fd("Error: Ambient ratio isn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

//Parsing of the line ambient light (type A)
static int	check_camera(char *line, t_scene *scene)
{
	char	**elements = NULL;

	elements = ft_split_set(line, " ");// corriger split_set
	if (!elements)
		return (ft_putstr_fd("Error: Split camera failed.\n", 2), 0);
	printf("split camera elements:\n");
	print_tab(elements);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of camera isn't valid.\n", 2), 0);
	if (!update_vector(&scene->camera.viewpoint, elements[1]))
		return (free_split(elements), 0);
	if (!update_vector(&scene->camera.orientation, elements[2]))
		return (free_split(elements), 0);
	if ((scene->camera.orientation.x < -1 || scene->camera.orientation.x > 1) || (scene->camera.orientation.y < -1 || scene->camera.orientation.y > 1) ||
		(scene->camera.orientation.x < -1 || scene->camera.orientation.x > 1))
		return (free_split(elements), ft_putstr_fd("Error: Cam orientation isn't in a valid range.\n", 2), 0);
	scene->camera.fov = ft_atoi(elements[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180) 	
		return (free_split(elements), ft_putstr_fd("Error: Cam ratio isn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

static int	check_light(char *line, t_scene *scene)
{
	char	**elements = NULL;

	elements = ft_split_set(line, " ");
	if (!elements)
		return (ft_putstr_fd("Error: Split light failed.\n", 2), 0);
	printf("split light elements:\n");
	print_tab(elements);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of light isn't valid.\n", 2), 0);
	if (!update_vector(&scene->light.position, elements[1]))
		return (free_split(elements), 0);
	scene->light.ratio = ft_atof(elements[2]);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		return (free_split(elements), ft_putstr_fd("Error: Light ratio isn't in a valid range.\n", 2), 0);
	if (!update_color(&scene->light.color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	return (1);
}

static int	check_sphere(char *line, t_scene *scene)
{
	char	**elements = NULL;

	elements = ft_split_set(line, " ");
	if (!elements)
		return (ft_putstr_fd("Error: Split sphere failed.\n", 2), 0);
	printf("split sphere elements:\n");
	print_tab(elements);
	if (count_line_tab(elements) != 4)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of sphere isn't valid.\n", 2), 0);
	if (!update_vector(&scene->sphere.center, elements[1]))
		return (free_split(elements), 0);
	scene->sphere.diametre = ft_atof(elements[2]);
	if (!update_color(&scene->sphere.color, elements[3]))
		return (free_split(elements), 0);
	free_split(elements);
	return (1);
}

//Function for parse elements of type line by line
int	parse_element_line(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		if (!check_ambient(line, scene))
			return (0);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		if (!check_camera(line, scene))
			return (0);
	}
	if (ft_strncmp(line, "L", 1) == 0)
	{
		if (!check_light(line, scene))
			return (0);
	}
	if (ft_strncmp(line, "sp", 2) == 0)
	{
		if (!check_sphere(line, scene))
			return (0);
	}
	//add function for others types of elements
	return (1);
}
