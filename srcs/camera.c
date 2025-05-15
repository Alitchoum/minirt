#include "minirt.h"

t_tuple	get_cam_offset(t_cam *cam, t_local cam_basis, double row, double col)
{
	t_tuple	right;
	t_tuple	up;
	t_tuple	combined_offset;

	right = scale(cam_basis.right, col * cam->aspect_ratio * cam->fov_scale);
	up = scale(cam_basis.up, row * cam->fov_scale);
	combined_offset = add(right, up);
	return (combined_offset);
}
void	setup_cam(t_cam *cam)
{
	cam->basis.forward = vector(0, 1, 0);
	if (fabs(cam->orientation.x) < EPSILON && fabs(cam->orientation.z) < EPSILON)
		cam->basis.forward = vector(0, 0, 1); 
	cam->basis.right = normalize(cross(cam->orientation, cam->basis.forward));
	cam->basis.up = normalize(cross(cam->basis.right, cam->orientation));
}