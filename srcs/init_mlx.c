
#include "minirt.h"

void	initialise_mlx(t_scene *scene)
{
	scene->mlx_ptr = mlx_init();
	scene->win_ptr = mlx_new_window(scene->mlx_ptr, W_WIDTH, W_HEIGHT, "MiniRT");
	scene->img = mlx_new_image(scene->mlx_ptr, W_WIDTH, W_HEIGHT);
	scene->addr = mlx_get_data_addr(scene->img, &scene->bpp, &scene->l_l, &scene->end);
}
