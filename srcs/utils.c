/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:46:17 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/16 17:31:26 by alsuchon         ###   ########.fr       */
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

