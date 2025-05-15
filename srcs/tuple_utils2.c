/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:14 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 16:25:20 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	add(t_tuple a, t_tuple b)
{
	t_tuple	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	new.w = a.w + b.w;
	return (new);
}

t_tuple	subtract(t_tuple a, t_tuple b)
{
	t_tuple	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	new.w = a.w - b.w;
	return (new);
}

t_tuple	negate(t_tuple a)
{
	a.x = -a.x;
	a.y = -a.y;
	a.z = -a.z;
	a.w = -a.w;
	return (a);
}

t_tuple	scale(t_tuple a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	a.w *= scale;
	return (a);
}

t_tuple	transform_normal(t_tuple local_normal, t_local basis)
{
	t_tuple	world_normal;

	world_normal.x = local_normal.x * basis.right.x
		+ local_normal.y * basis.up.x
		+ local_normal.z * basis.forward.x;
	world_normal.y = local_normal.x * basis.right.y
		+ local_normal.y * basis.up.y
		+ local_normal.z * basis.forward.y;
	world_normal.z = local_normal.x * basis.right.z
		+ local_normal.y * basis.up.z
		+ local_normal.z * basis.forward.z;
	world_normal.w = 0;
	return (world_normal);
}
