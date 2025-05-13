/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:14 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/13 16:55:16 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	new.w = a.w + b.w;
	return (new);
}

t_tuple	subtract_tuple(t_tuple a, t_tuple b)
{
	t_tuple	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	new.w = a.w - b.w;
	return (new);
}

t_tuple	negate_tuple(t_tuple a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	a.w = -a.w;
	return (a);
}

t_tuple	scale_tuple(t_tuple a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	a.w *= scale;
	return (a);
}
