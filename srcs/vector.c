/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caburges <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:26:04 by caburges          #+#    #+#             */
/*   Updated: 2025/04/21 18:26:06 by caburges         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Produit scalaire de 2 vecteurs
float	vec3_dot(t_vector a, t_vector b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector	vec3_add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	vec3_subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

// NORMALISE UN VECTEUR (longueur 1) = direction
t_vector vec3_normalize(t_vector a)
{
	double len = sqrt(vec3_dot(a, a));
	a.x /= len;
	a.y /= len;
	a.z /= len;
	return (a);
}

//Permet de se deplacer par palier sur le rayon (vecteur directionnel * distance scalaire)
//Acance recule sur axe du rayon
t_vector	vec3_scale(t_vector a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	return (a);
}

