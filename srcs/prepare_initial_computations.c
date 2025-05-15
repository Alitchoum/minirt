#include "minirt.h"

void	compute_cylinder_local_basis(t_local *basis, t_tuple orientation)
{
	basis->forward = orientation;
	if (fabs(basis->forward.x) < 1)
		basis->right = normalize_tuple(cross_tuple(vector(1, 0, 0), basis->forward));
	else
		basis->right = normalize_tuple(cross_tuple(vector(0, 1, 0), basis->forward));
	basis->up = normalize_tuple(cross_tuple(basis->forward, basis->right));
}

void	prep_initial_cylinder_computations(t_object *cylinder)
{
	// radius squared
	cylinder->radius_squared = pow(cylinder->radius, 2);
	// half height
	cylinder->half_height = cylinder->height / 2;
	// local basis
	compute_cylinder_local_basis(&cylinder->basis, cylinder->orientation);
}

void	prep_initial_sphere_computations(t_object *sphere)
{
	sphere->radius_squared = pow(sphere->radius, 2);
}

void	prepare_initial_computations(t_object *shapes, int obj_count)
{
	int	i;

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
