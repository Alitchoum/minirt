/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:06:39 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/04 15:20:34 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void print_tab(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}	
}

//Function for check if the extension is terminate by .rt
static int	scene_is_valid(char *file)
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

static int	check_colors(char *line, t_scene *scene)
{
	char	**rvb = NULL;

	rvb = split(line, ',');
	if (!rvb)
		return (ft_putstr_fd("Error: Split failed.\n", 2), 0);
	print_tab(rvb);
	
}

static int	check_ambient(char *line, t_scene *scene)
{
	char	**elements = NULL;
	
	elements = ft_split(line, ' ');
	if (!elements)
		return (ft_putstr_fd("Error: Split failed.\n", 2), 0);
	print_tab(elements);
	scene->ambient.ratio = ft_atoi(elements[1]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (ft_putstr_fd("Error: Ratio doesn't in a valid range.\n", 2), 0);
	free_split(elements);
	return (1);
}

//Function for parse doc_name.rt line by line
int	read_and_parse_scene(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	int		len;

	if (!scene_is_valid(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Cannot open the file.\n", 2), 0);
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strncmp(line, "A", 1) == 0)
			check_ambient(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
