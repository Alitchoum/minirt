#ifndef MINIRT_H
# define MINIRT_H

#include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>

#define W_WIDTH 1080
#define W_HEIGHT 900

# define PURPLE 0x4b0082
# define WHITE 0xffffff
# define YELLOW 0xffa500
# define PINK 0xff69b4
# define TEAL 0x008080
# define CORAL 0xff7f50
# define BLUE 0x0000ff
# define FUSCHIA 0xff00ff
# define BRIGHT_GREEN 0x00ff00
# define RED 0xff0000

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}			t_vector;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	*color;
}			t_ambient;

typedef struct s_cam
{
	double		viewpoint;
	t_vector	orientation;
	int			fov;
}				t_cam;

typedef struct s_light
{
	double		position;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		diametre;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	viewpoint;
	t_vector	orientation;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	orientation;
	double		diametre;
	double		height;
	t_color		color;
}				t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_cam		camera;
	t_light		light;	

	void	*win_ptr;
	void	*mlx_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_l;
	int		end;
}				t_scene;

int		main(int ac, char **av);
int		parse_scene(char *file, t_scene *scene);
void	free_split(char **s);

// INIT MLX
void	initialise_mlx(t_scene *scene);

// DRAW
void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour);

#endif
