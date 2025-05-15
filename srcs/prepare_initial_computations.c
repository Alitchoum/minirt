/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_initial_computations.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:48:37 by caburges          #+#    #+#             */
/*   Updated: 2025/05/15 18:48:38 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	prep_cylinder_basis(t_local *basis, t_tuple orientation)
{
	basis->forward = orientation;
	
	if (fabs(basis->forward.x) < 0.9)
	{
		basis->right = cross(vector(1, 0, 0), basis->forward);
		basis->right = normalize(basis->right);
	}
	else
	{
		basis->right = cross(vector(0, 1, 0), basis->forward);
		basis->right = normalize(basis->right);
	}
	basis->up = normalize(cross(basis->forward, basis->right));
}

void	prep_initial_cylinder_computations(t_object *cylinder)
{
	cylinder->radius_squared = cylinder->radius * cylinder->radius;
	cylinder->half_height = cylinder->height / 2;
	prep_cylinder_basis(&cylinder->basis, cylinder->orientation);
}

void	prep_initial_sphere_computations(t_object *sphere)
{
	sphere->radius_squared = sphere->radius * sphere->radius;
}

void	prepare_initial_computations(t_cam *cam, t_object *shapes, int obj_count)
{
	int	i;

	cam->aspect_ratio = W_WIDTH / (double)W_HEIGHT;
	cam->fov_scale = tan(radians((cam->fov * 0.5)));

	i = 0;
	while (i < obj_count)
	{
		if (shapes[i].type == CYLINDER)
			prep_initial_cylinder_computations(&shapes[i]);
		else if (shapes[i].type == SPHERE)
			prep_initial_sphere_computations(&shapes[i]);
		i++;
	}
}
