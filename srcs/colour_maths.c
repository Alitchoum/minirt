/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 20:40:57 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 20:41:05 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// transforming rgb to final int colour (taking into account light scalar)
// converts back from decimal between 0 - 1 to an integer ready for my_pixel_put
int	rgb_to_int(t_color colour, double light_scalar)
{
	int	r;
	int	g;
	int	b;

	colour.r *= light_scalar;
	colour.g *= light_scalar;
	colour.b *= light_scalar;
	r = (int)(colour.r * 255);
	g = (int)(colour.g * 255);
	b = (int)(colour.b * 255);
	return (r << 16 | g << 8 | b);
}
