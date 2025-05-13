/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:20:46 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/13 16:48:21 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	translation(t_tuple *position, int keysym)
{
	printf("touch = %d\n", keysym);
	if (keysym == 105) //i ->reculer
		position->z += 0.5;
	else if (keysym == 107) //k->avancer
		position->z -= 0.5;
	else if (keysym == 106) //j->droite
		position->x -= 0.5;
	else if (keysym == 101) //e ->gauche
		position->x += 0.5;
	else if (keysym == 117) //u->bas
		position->y += 0.5;
	else if (keysym == 111) // o->haut
		position->y -= 0.5;
}

void	rotation(t_tuple *orientation, int keysym)
{
	if (keysym == 65363) //-> orientation gauche (Y)
		*orientation = rotate_tuple(*orientation, Y, 0.1);
	else if (keysym == 65361) //-> orientation droite (Y)
		*orientation = rotate_tuple(*orientation, Y, -0.1);
	else if (keysym == 65362) //-> orientation haut (x)
		*orientation = rotate_tuple(*orientation, X, 0.1);
	else if (keysym == 65364) //-> orientation bas (x)
		*orientation = rotate_tuple(*orientation, X, -0.1);
}

void	scaling_radius(double *radius, int keysym)
{
	if (keysym == 65451) // +
		*radius *= 1.1;
	else if (keysym == 65453) // -
		*radius *= 0.9;
}

void	scaling_height(double *height, int keysym)
{
	if (keysym == 65434) //9 -> +
		*height += 0.1;
	else if (keysym == 65432) //6-> -
		*height -= 0.1;
}
