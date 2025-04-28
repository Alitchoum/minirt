/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:51:55 by caburges          #+#    #+#             */
/*   Updated: 2025/04/15 17:13:33 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	count_words(char const *s, char *charset)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		while (ft_strchr(charset, *s))
			s++;
		if (*s == '\0')
			return (word_count);
		word_count++;
		while (*s && !ft_strchr(charset, *s))
			s++;
	}
	return (word_count);
}

static char	**free_array(char **array, size_t words_to_free)
{
	size_t	i;

	i = 0;
	while (i < words_to_free)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static size_t	count_word_len(char const *s, char *charset)
{
	size_t	len;

	len = 0;
	while (s[len] && !ft_strchr(charset, s[len]))
		len++;
	return (len);
}

char	**ft_split_set(char const *s, char *charset)
{
	char	**array;
	size_t	i;
	size_t	word_len;

	if (!s || !charset)
		return (NULL);
	array = ft_calloc((count_words(s, charset) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (ft_strchr(charset, *s))
			s++;
		if (*s != '\0')
		{
			word_len = count_word_len(s, charset);
			array[i] = ft_substr(s, 0, word_len);
			if (!array[i])
				return (free_array(array, i));
			i++;
			s = s + word_len;
		}
	}
	return (array);
}
