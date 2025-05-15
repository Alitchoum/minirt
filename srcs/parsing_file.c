/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:06:39 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 15:06:48 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// removed "free line"
static int	add_line_to_scene(t_scene *scene, char *line)
{
	char	*content;
	t_list	*new_node;

	content = ft_strdup(line);
	if (!content)
		return (0); 
	if (ft_strchr(content, '\n'))
		content[ft_strlen(content) - 1] = '\0';
	new_node = ft_lstnew(content);
	if (!new_node)
		return (free(content), 0);
	ft_lstadd_back(&scene->lines, new_node);
	return (1);
}

//Function read and create an list with the lines of file.rt
int	create_scene_list(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error: Cannot open the file"), exit(EXIT_FAILURE), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			if (!add_line_to_scene(scene, line))
			{
				perror("Malloc");
				return (free(line), close(fd), get_next_line(-5), 0);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

// currently accepts "Camera"
static int	count_nb_element(char *line, int *cam, int *ambient, int *light)
{
	if (ft_strncmp(line, "A", 1) == 0)
			(*ambient)++;
	else if (ft_strncmp(line, "C", 1) == 0)
			(*cam)++;
	else if (ft_strncmp(line, "L", 1) == 0)
			(*light)++;
	else
		return (0);
	return (1);
}

// to amend element id / object check -> accepts "sphere" or "Camera" etc
// added a check for if there are no objects in the scene
int	check_type_of_scene(t_list *lines, int *obj_count)
{
	t_list	*current;
	char	*line;
	int		cam;
	int		ambient;
	int		light;

	cam = 0;
	ambient = 0;
	light = 0;
	current = lines;
	while (current)
	{
		line = current->content;
		if (!count_nb_element(line, &cam, &ambient, &light))
		{
			if (ft_strncmp(line, "sp", 2) != 0 && ft_strncmp(line, "pl", 2) != 0
				&& ft_strncmp(line, "cy", 2) != 0)
				return (ft_putstr_fd("Error: Invalid element id.\n", 2), 0);
			(*obj_count)++;
		}
		current = current->next;
	}
	if (cam != 1 || ambient != 1 || light != 1 || *obj_count == 0)
		return (ft_putstr_fd("Error: Must be 1 cam,ambient,light,shape.\n", 2), 0);
	return (1);
}

int	parse_scene(char *file, t_scene *scene)
{
	t_list	*current;
	char	*line;
	int		element_count;

	element_count = 0;
	if (!check_extension(file))
		return (0);
	if (!create_scene_list(scene, file))
		return (ft_lstclear(&scene->lines, free), 0);
	if (!check_type_of_scene(scene->lines, &scene->obj_count))
		return (ft_lstclear(&scene->lines, free), 0);
	scene->objects = ft_calloc(scene->obj_count, sizeof(t_object));
	if (!scene->objects)
		return (ft_lstclear(&scene->lines, free), perror("Malloc"), 0); // added free scene lines
	current = scene->lines;
	while (current)
	{
		line = current->content;
		if (!parse_element_line(line, scene, &element_count))
			return (ft_lstclear(&scene->lines, free), free(scene->objects), 0); //added free scene objects
		current = current->next;
	}
	ft_lstclear(&scene->lines, free);
	prepare_initial_computations(&scene->camera, scene->objects, scene->obj_count);
	return (1);
}
