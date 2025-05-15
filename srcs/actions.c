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
// for camera, the translation goes the wrong way, fine for shapes
void	translation(t_tuple *position, int keysym)
{
	printf("touch = %d\n", keysym);
	if (keysym == 'z') //z ->reculer
		position->z += 0.5;
	else if (keysym == 'x') //x->avancer
		position->z -= 0.5;
	else if (keysym == 'g') //j->droite
		position->x += 0.5;
	else if (keysym == 'd') //e ->gauche
		position->x -= 0.5;
	else if (keysym == 'f') //u->bas
		position->y -= 0.5;
	else if (keysym == 'r') // o->haut
		position->y += 0.5;
}

// TO CHECK - BOTH DO THE SAME -
// > JUST CHANGE TO R(otation)? then just use arrows to move whatever way??
void	rotation(t_tuple *orientation, int keysym)
{
	if (keysym == LEFT_ARROW) //-> orientation gauche (Y)
		*orientation = rotate_tuple(*orientation, Y, 0.1);
	else if (keysym == RIGHT_ARROW) //-> orientation droite (Y)
		*orientation = rotate_tuple(*orientation, Y, -0.1);
	else if (keysym == UP_ARROW) //-> orientation haut (x)
		*orientation = rotate_tuple(*orientation, X, 0.1);
	else if (keysym == DOWN_ARROW) //-> orientation bas (x)
		*orientation = rotate_tuple(*orientation, X, -0.1);
}

void	scaling_radius(double *radius, int keysym)
{
	if (keysym == ADD) // +
		*radius *= 1.1;
	else if (keysym == SUBTRACT) // -
		*radius *= 0.9;
}

void	scaling_height(double *height, int keysym)
{
	if (keysym == ADD_H) //9 -> +
		*height += 0.1;
	else if (keysym == SUBTRACT_H) //6-> -
		*height -= 0.1;
}
