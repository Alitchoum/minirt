/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alize <alize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:06:39 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/20 18:38:32 by alize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

//Function read and create an list with the lines of file.rt
int	create_scene_list(t_scene *scene, char *file)
{
	t_list	*new_node;
	int		fd;
	char	*line;
	char	*content;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error: Cannot open the file"), exit(EXIT_FAILURE), 0);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 1) != 0)
		{
			content = ft_strdup(line);
			//printf("avant: %s\n", content);
			if (!content)
				return (free(line), 0);
			if (ft_strchr(content, '\n'))
				content[ft_strlen(content) - 1] = '\0';
			//printf("apres: %s\n", content);
			new_node = ft_lstnew(content); //malloc
			ft_lstadd_back(&scene->lines, new_node);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

// 1: Check element IDs are valid (1st word)
// 2: Check right number of elements
// 3: Correct num parameters for each element
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
		if (ft_strncmp(line, "A", 1) == 0)
			ambient++;
		else if (ft_strncmp(line, "C", 1) == 0)
			cam++;
		else if (ft_strncmp(line, "L", 1) == 0)
			light++;
		else if (ft_strncmp(line, "sp", 2) != 0 && ft_strncmp(line, "pl", 2) != 0 && ft_strncmp(line, "cy", 2) != 0)
			return (ft_putstr_fd("Error: Element(s) doesn't valid(s).\n", 2), 0);
		else
			*obj_count = *obj_count + 1;
		current = current->next;
	}
	if (cam > 1 || ambient > 1 || light > 1)
		return (ft_putstr_fd("Error: Nb elements doesn't valid.\n", 2), 0);
	printf("number of objects: %i\n", *obj_count);
	return (1);
}
//FUNCTION COUNT NB OF OBJECTS (SP, CY, PL) IS THE SCENE + CHECK LIMITS 
// int	count_scene_objects(t_list *lines, t_scene *scene)
// {
// 	t_list	*current;

// 	current = lines;
// 	while (current)
// 	{
// 		if (ft_strncmp(current->content, "sp", 2) == 0)
// 			scene->nb_sp++;
// 		else if (ft_strncmp(current->content, "cy", 2) == 0)
// 			scene->nb_cy++;
// 		else if (ft_strncmp(current->content, "pl", 2) == 0)
// 			scene->nb_pl++;
// 		current = current->next;
// 	}
// 	if (scene->nb_sp > MAX_SP || scene->nb_cy >MAX_CY || scene->nb_pl > MAX_PL)
// 		return (ft_putstr_fd("Error: Too many objects in the scene.\n", 2), 0);
// 	return (1);
// }
//Function parsing global
//A: Check Valid Inputs
// 1: Check file extension
// 2: Check issue with open
// 2a: Check file is not empty
//
//B: Parse into appropriate structs/format
//
//CHECK MAX NUMBER OF ELEMENTS?
int	parse_scene(char *file, t_scene *scene)
{
	t_list *current;
	char	*line;
	int element_count = 0;
	
	if (!check_extension(file))
		return (0);
	if (!create_scene_list(scene, file))
		return (ft_lstclear(&scene->lines, free), 0);
	if (!check_type_of_scene(scene->lines, &scene->obj_count))
		return (ft_lstclear(&scene->lines, free), 0);
	scene->objects = ft_calloc(scene->obj_count, sizeof(t_object));
	if (!scene->objects)
		return (ft_putstr_fd("Error: Malloc failed.\n", 2), 0);
	current = scene->lines;
	while (current)
	{
		line = current->content;
		
		if (!parse_element_line(line, scene, &element_count))
			return (ft_lstclear(&scene->lines, free), 0);
		current = current->next;
	}
	ft_lstclear(&scene->lines, free);
	return (1);
}
