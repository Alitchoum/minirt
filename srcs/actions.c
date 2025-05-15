/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsuchon <alsuchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:20:46 by alsuchon          #+#    #+#             */
/*   Updated: 2025/05/15 18:02:21 by alsuchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//-- TRANSLATE COMMANDS --
//z ->reculer
//x -> avancer
//g-> droite
//d -> gauche
//f -> bas
//r -> haut
void	translation(t_tuple *position, int keysym)
{
	if (keysym == 'z')
		position->z += 0.5;
	else if (keysym == 'x')
		position->z -= 0.5;
	else if (keysym == 'g')
		position->x += 0.5;
	else if (keysym == 'd')
		position->x -= 0.5;
	else if (keysym == 'f')
		position->y -= 0.5;
	else if (keysym == 'r')
		position->y += 0.5;
}

//-- ROTATE COMMANDS -- 
// fleche gauche -> orientation gauche (axe Y)
// fleche droite -> orientation droite (axe Y)
// fleche haut -> orientation haut (axe x)
// fleche bas-> orientation bas (axe x)
void	rotation(t_tuple *orientation, int keysym)
{
	if (keysym == LEFT_ARROW)
		*orientation = rotate_tuple(*orientation, Y, 0.1);
	else if (keysym == RIGHT_ARROW)
		*orientation = rotate_tuple(*orientation, Y, -0.1);
	else if (keysym == UP_ARROW)
		*orientation = rotate_tuple(*orientation, X, 0.1);
	else if (keysym == DOWN_ARROW)
		*orientation = rotate_tuple(*orientation, X, -0.1);
}

// cylindre et sphere
// + -> Augmenter la taille (radius)
// - -> Reduire la taille
void	scaling_radius(double *radius, int keysym)
{
	if (keysym == ADD)
		*radius *= 1.1;
	else if (keysym == SUBTRACT)
		*radius *= 0.9;
}

// Pour cylindre uniquement
// + -> Augmenter la longueur
// - -> Reduire la longueur
void	scaling_height(double *height, int keysym)
{
	if (keysym == ADD_H)
		*height += 0.1;
	else if (keysym == SUBTRACT_H)
		*height -= 0.1;
}
