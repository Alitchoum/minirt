/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:37:58 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/12 18:26:49 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Verifier si float plusieurs "." -> OK
//Pour overflow ajouter verif direct dans atoi et atof putot que pour chaque données??

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
	printf("split camera elements:\n");
	print_tab(elements);
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
	printf("split light elements:\n");
	print_tab(elements);
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

static int	check_sphere(char *line, t_object *sphere, int *object_index)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split sphere failed.\n", 2), 0);
	printf("split sphere elements:\n");
	print_tab(elements);
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
	// pre_computing the radius squared at beginning (if changed need to update radius squared in render)
	sphere->type = SPHERE;
	*object_index += 1;
	return (1);
}
static int	check_plane(char *line, t_object *plane, int *object_index)
{
	char	**elements = NULL;

	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split plane failed.\n", 2), 0);
	printf("split plane elements:\n");
	print_tab(elements);
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

static int	check_cylinder(char *line, t_object *cylinder, int *object_index)
{
	char	**elements = NULL;
	
	elements = ft_split_set(line, WHITESPACE);
	if (!elements)
		return (ft_putstr_fd("Error: Split cylinder failed.\n", 2), 0);
	printf("split cylinder elements:\n");
	print_tab(elements);
	if (count_line_tab(elements) != 6)
		return (free_split(elements), ft_putstr_fd("Error: Nb of elements of cylinder isn't valid.\n", 2), 0);
	if (!update_tuple(&cylinder->position, elements[1], 1))
		return (free_split(elements), 0);
	if (!update_tuple(&cylinder->orientation, elements[2], 1))
		return (free_split(elements), 0);
	if (!is_valid_orientation_range(cylinder->orientation))
		return (free_split(elements), ft_putstr_fd("Error: Cylinder ratio isn't in a valid range.\n", 2), 0);
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
