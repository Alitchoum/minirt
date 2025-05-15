/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:28:31 by caburges          #+#    #+#             */
/*   Updated: 2025/05/14 14:48:34 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

float	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

//will rotate that tuple around an axis
double	radians(double degrees)
{
	return ((degrees / 180) * M_PI);
}
