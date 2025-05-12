
#include "minirt.h"

int		shut_down(t_scene *scene);
t_tuple	mat4_multiply_tuple(t_matrix matrix, t_tuple tup);

void	camera_control(int keysym, t_scene *scene)
{

	//translate
	printf("touch = %d\n", keysym);
	if (keysym == 105) //i -> avancer
		scene->camera.position.z += 0.5;
	else if (keysym == 107) //k -> reculer
		scene->camera.position.z -= 0.5;
	else if (keysym == 106) //j ->gauche
		scene->camera.position.x -= 0.5; 
	else if (keysym == 108) //l ->droite
		scene->camera.position.x += 0.5;
	else if (keysym == 117) //u ->bas
		scene->camera.position.y += 0.5;
	else if (keysym == 111) //o -> haut
		scene->camera.position.y -= 0.5;
	//rotation
	else if (keysym == 113) // q -> orientation gauche (Y)
		scene->camera.orientation = rotate_tuple(scene->camera.orientation, Y, 0.1);
	else if (keysym == 101) // e -> orientation droite (Y)
		scene->camera.orientation = rotate_tuple(scene->camera.orientation, Y, -0.1);
	else if (keysym == 116) // t -> orientation haut (X)
		scene->camera.orientation = rotate_tuple(scene->camera.orientation, X, -0.1);
	else if (keysym == 103) // g -> orientation bas (X)
		scene->camera.orientation = rotate_tuple(scene->camera.orientation, X, 0.1);
}

int	do_keypress(int keysym, t_scene *scene)
{
	if (keysym == XK_Escape)
		shut_down(scene);
	else if (keysym == 115)
	{
		printf("[S]cale pressed\n");
		scene->objects[0].orientation = rotate_tuple(scene->objects[0].orientation, Y, 0.1);
	}
	else if (keysym == 65363)
	{
		printf("Right arrow pressed (translate right)\n");
		scene->objects[0].position.x += 0.1;
	}
	else if (keysym == 65361)
	{
		printf("Left arrow pressed (translate left)\n");
		scene->objects[0].position.x -= 0.1;
	}
	else if (keysym == 65362)
	{
		printf("Up arrow pressed (translate up)\n");
		scene->objects[0].position.y += 0.1;
	}
	else if (keysym == 65364)
	{
		printf("Down arrow pressed (translate down)\n");
		scene->objects[0].position.y -= 0.1;
	}
	else if (keysym == 98)
	{
		printf("[F]orward pressed (translate closer on z)\n");
		scene->objects[0].position.z += 0.1;
	}
	else if (keysym == 102)
	{
		printf("[B]ackward pressed (translate closer on z)\n");
		scene->objects[0].position.z -= 0.1;
	}
	else if (keysym == 105 || keysym == 107 || keysym == 106 || keysym == 108 || keysym == 117 || keysym == 111 || keysym == 113 ||
			keysym == 101 || keysym == 116 || keysym == 103)
	{
		printf("move camera\n");
		camera_control(keysym, scene);
	}
	else
		printf("pressed key: %i\n", keysym);
	render_image(scene);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, scene->img, 0, 0);
	return (0);
}
