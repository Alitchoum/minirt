
#include "minirt.h"

int		shut_down(t_scene *scene);
t_tuple	mat4_multiply_tuple(t_matrix matrix, t_tuple tup);

// void inverse_cam_transform(t_scene *scene)
// {
//     int i;
//     t_matrix inverse_rot;

//     inverse_rot = inverse(&(scene->camera.orientation));
//     i = 0;
//     while (i < scene->obj_count)
//     {
//         scene->objects[i].position = mat4_multiply_tuple(inverse_rot, scene->objects[i].position);
//         i++;
//     }
// }

void	camera_control(int keysym, t_scene *scene)
{
    t_matrix rotate;

	//translate
	if (keysym == 105) //i -> avancer
		scene->camera.position.z += 0.5;
	else if (keysym == 107) //k -> reculer
		scene->camera.position.z -= 0.5;
	else if (keysym == 106) //j ->gauche
		scene->camera.position.x -= 0.5; 
	else if (keysym == 108) //l ->droite
		scene->camera.position.x -= 0.5;
	else if (keysym == 117)  //u ->haut
		scene->camera.position.y += 0.5;
	else if (keysym == 111) //o -> bas
		scene->camera.position.y -= 0.5;
	//rotation

	else if (keysym == 113) //q -> orientation gauche (y)
    {
        rotate = rotation_y(radians(5));
		scene->camera.orientation = mat4_multiply_tuple(rotate, scene->camera.orientation);
        //inverse_cam_transform(scene);
    }
	else if (keysym == 101) //e -> orientation droite (y)
    {
        rotate = rotation_y(-radians(5));
		scene->camera.orientation = mat4_multiply_tuple(rotate, scene->camera.orientation);
    } 
	else if (keysym == 116)  //t -> orientation haut (x)
    {
        rotate = rotation_x(radians(5));
		scene->camera.orientation = mat4_multiply_tuple(rotate, scene->camera.orientation);
    }
	else if (keysym == 103) //g -> orientation bas (x)
    {
        rotate = rotation_x(-radians(5));
		scene->camera.orientation = mat4_multiply_tuple(rotate, scene->camera.orientation);
    }
}

int	do_keypress(int keysym, t_scene *scene)
{
	if (keysym == XK_Escape)
		shut_down(scene);
	else if (keysym == 115)
	{
		printf("[S]cale pressed\n");
		scene->objects[0].diametre *= 1.1;
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
	else if (keysym == 105 || keysym == 107 || keysym == 106 || keysym == 108 || keysym == 111 || keysym == 113 ||
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
