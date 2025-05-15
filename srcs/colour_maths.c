/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:47:53 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:47:54 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

// transforming rgb to final int colour (taking into account light scalar)
// converts back from decimal between 0 - 1 to an integer ready for my_pixel_put
int	rgb_to_int(t_color colour, double light_scalar)
{
	int r;
	int g;
	int b;
	colour.r *= light_scalar;
	colour.g *= light_scalar;
	colour.b *= light_scalar;
	r = (int)(colour.r * 255);
	g = (int)(colour.g * 255);
	b = (int)(colour.b * 255);
	return (r << 16 | g << 8 | b);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	new;

	new.r = a.r + b.r;
	new.g = a.g + b.g;
	new.b = a.b + b.b;
	return (new);
}

t_color	color_subtract(t_color a, t_color b)
{
	t_color new;

	new.r = a.r - b.r;
	new.g = a.g - b.g;
	new.b = a.b - b.b;
	return (new);
}

t_color	color_scale(t_color c, double scale)
{
	c.r *= scale;
	c.g *= scale;
	c.b *= scale;
	return (c);
}

t_color	color_multiply(t_color a, t_color b)
{
	a.r = a.r * b.r;
	a.g = a.g * b.g;
	a.b = a.b * b.b;
	return (a);
}
