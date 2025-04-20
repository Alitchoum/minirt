#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <limits.h>

# define W_WIDTH 800
# define W_HEIGHT 800

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

# define MAX_SP 10 //A DEFINIR
# define MAX_CY 10 //A DEFINIR
# define MAX_PL 10 //A DEFINIR

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
	t_color	color;
}			t_ambient;

typedef struct s_cam
{
	t_vector	position;
	t_vector	orientation;
	int			fov;
}				t_cam;

typedef struct s_light
{
	t_vector	position;
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
	t_vector	*orientation;
	t_color		*color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	*center;
	t_vector	*orientation;
	double		diametre;
	double		height;
	t_color		*color;
}				t_cylinder;

typedef struct s_quadratic
{
	double	solutions[2];
	double	discriminant;
}	t_quadratic;

typedef	struct s_mlx
{
	void	*win_ptr;
	void	*mlx_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		l_l;
	int		end;
}	t_mlx;

typedef struct s_scene
{
	t_list		*lines;
	t_ambient	ambient;
	t_cam		camera;
	t_light		light;
	t_sphere	*spheres;
	int			nb_sp;
	int			nb_cy;
	int			nb_pl;
	t_mlx		mlx_data;
	void		*win_ptr;
	void		*mlx_ptr;
	void		*img;
	char		*addr;
	int			bpp;
	int			l_l;
	int			end;
}				t_scene;

int		main(int ac, char **av);
int		parse_scene(char *file, t_scene *scene);

//---FUNCTIONS UTILS---//
void	free_split(char **s);
double	ft_atof(char *s);
int		is_valid_int(char *s);
int		is_valid_double(char *s);
void	print_list(t_list *lines);

//--DRAW--//
void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour);
int		render_image(t_scene *scene);

//---PARSING TYPE---//
int		parse_element_line(char *line, t_scene *scene);

//--INIT MLX--//
void	initialise_mlx(t_scene *scene);


#endif
