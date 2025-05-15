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
		*orientation = rotate(*orientation, Y, 0.1);
	else if (keysym == RIGHT_ARROW)
		*orientation = rotate(*orientation, Y, -0.1);
	else if (keysym == UP_ARROW)
		*orientation = rotate(*orientation, X, 0.1);
	else if (keysym == DOWN_ARROW)
		*orientation = rotate(*orientation, X, -0.1);
}

// cylindre et sphere
// + -> Augmenter la taille (radius)
// - -> Reduire la taille
void	scaling_radius(double *radius, int keysym)
{
	if (keysym == ADD && *radius < INT_MAX)
	{
		*radius *= 1.1;
	}
	else if (keysym == SUBTRACT && *radius < INT_MAX)
		*radius *= 0.9;
}

// Pour cylindre uniquement
// + -> Augmenter la longueur
// - -> Reduire la longueur
void	scaling_height(double *height, int keysym)
{
	if (keysym == ADD_H && *height < INT_MAX)
		*height += 0.1;
	else if (keysym == SUBTRACT_H && *height < INT_MAX)
		*height -= 0.1;
}

void	recomp_basis(t_object *cy, int keysym)
{
	if (keysym == LEFT_ARROW || keysym == RIGHT_ARROW || keysym == UP_ARROW || keysym == DOWN_ARROW)
	{
		cy->basis.forward = cy->orientation;
		if (fabs(cy->basis.forward.x) < 0.9)
		{	
			cy->basis.right = cross(vector(1, 0, 0), cy->basis.forward);
			cy->basis.right = normalize(cy->basis.right);
		}
		else
		{
			cy->basis.right = cross(vector(0, 1, 0), cy->basis.forward);
			cy->basis.right = normalize(cy->basis.right);
		}
		cy->basis.up = normalize(cross(cy->basis.forward, cy->basis.right));
	}
}
