/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:06:39 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/04 19:07:44 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Fonction for count nb of lines of array of strings
static int	count_line_tab(char **s)
{
	int	count;

	count = 0;
	while (s[count] != NULL)
		count++;
	return (count);
}

//print a array of strings
static void print_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}	
}

//Function for check if the extension is terminate by .rt
static int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 3 || file[len - 3] != '.' || file[len - 2] != 'r' || file[len - 1] != 't')
	{
		ft_putstr_fd("Error: Extension doesn't valid.\n", 2);
		return (0);
	}
	return (1);
}

//counts nb of line in the file.rt
static int count_lines_file(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error: Cannot open the file"), 0);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

//Function read and create an array with the lines of file.rt
char	**create_tab_of_scene(char *file)
{
	int		fd;
	char	*line;
	char	**scene_array;
	int		len;
	int		i;
	
	len = count_lines_file(file);
	scene_array = malloc(sizeof(char *) * (len + 1));
	if (!scene_array)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free_split(scene_array), perror("Error: Cannot open the file"), NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		scene_array[i] = line;
		i++;
		line = get_next_line(fd);
	}
	scene_array[i] = NULL;
	close(fd);
	return (scene_array);
}

static int	check_type_of_scene(char **lines)
{
	int	i;
	int	cam;
	int	ambient;
	int	light;
	
	i = 0;
	cam = 0;
	ambient = 0;
	light = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "A", 1) == 0)
			cam++;
		else if (ft_strncmp(lines[i], "C", 1) == 0)
			ambient++;
		else if (ft_strncmp(lines[i], "L", 1) == 0)
			light++;
		// Il faudra ajouter pour les autres elements aussi ici je pense
		i++;
	}
	// Pour l'instant j'ai juste vérifier si il y avait max 1 camera, 1 lumiere ambiante et 1 lumiere diffuse
	if (cam != 1 || ambient != 1 || light != 1)
		return (ft_putstr_fd("Error: Nb elements doesn't valid.\n", 2), 0);
	return (1);
}

//create & return a struct with code color RGB
t_color	*extract_color(char *line)
{
	t_color *color;
	char	**rgb = NULL;

	rgb = ft_split(line, ',');
	if (!rgb)
		return (ft_putstr_fd("Error: Split failed.\n", 2), NULL);
	if (count_line_tab(rgb) != 3)
		return (free_split(rgb), ft_putstr_fd("Error Nb of elements doens't valid.\n", 2), NULL);
	print_tab(rgb);
	color = malloc(sizeof(t_color));
	if (!color)
		return (free_split(rgb), ft_putstr_fd("Error: Malloc failed.\n", 2), NULL);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	if ((color->r < 0 || color->r > 255) && (color->g < 0 || color->r > 255) &&
		(color->b < 0 || color->b > 255))
	{
		free_split(rgb);
		free(color);
		ft_putstr_fd("Error: Color doesn't in a valid range.\n", 2);
		return (NULL);
	}	
	free_split(rgb);
	return (color);
}

//Parsing of the line ambient light (type A)
static int	check_ambient(char *line, t_scene *scene)
{
	char	**elements = NULL;
	
	elements = ft_split(line, ' ');
	if (!elements)
			return (ft_putstr_fd("Error: Split failed.\n", 2), 0);
	if (count_line_tab(elements)!= 3)
		return (free_split(elements), ft_putstr_fd("Error Nb of elements doens't valid.\n", 2), 0);
	print_tab(elements);
	scene->ambient.ratio = ft_atoi(elements[1]);
	scene->ambient.color = extract_color(elements[2]);
	if (!scene->ambient.color)
		return (free_split(elements), 0);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (free_split(elements), ft_putstr_fd("Error: Ratio doesn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

//Function for parse elements of type line by line
static int	parse_element_line(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "A", 1) == 0)
	{
		if (!check_ambient(line, scene))
			return (0);
	}
	//add function for others types of elements
	return (1);
}

//Function parsing global
int	parse_scene(char *file, t_scene *scene)
{
	char	**lines;
	int		i;
	
	if (!check_extension(file))
		return (0);
	lines = create_tab_of_scene(file);
	if (!lines)
		return (ft_putstr_fd("Error: Malloc failed.\n", 2), 0);
	if (!check_type_of_scene(lines))
		return (0);
	i = 0;
	while (lines[i])
	{
		parse_element_line(lines[i], scene);
		i++;
	}
	free_split(lines);
	return (1);
}
