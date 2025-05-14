/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:29:25 by alsuchon          #+#    #+#             */
/*   Updated: 2025/04/16 17:31:46 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

double	fractional_part(char *s, int *i)
{
	double	result;
	double	facteur_dec;

	result = 0.0;
	facteur_dec = 1.0;
	if (s[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(s[*i]))
		{
			result = result * 10 + (s[*i] - '0');
			facteur_dec *= 10;
			(*i)++;
		}
	}
	return (result / facteur_dec);
}

double	ft_atof(char *s)
{
	int		i;
	int		sign;
	double	result;

	i = 0;
	sign = 1;
	result = 0.0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	result += fractional_part(s, &i);
	return (result * sign);
}
