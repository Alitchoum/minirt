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
# include <X11/X.h>
# include <X11/keysym.h>

# define W_WIDTH 1000
# define W_HEIGHT 1000

# define  WHITESPACE " \t\v\f\r"

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

# define LEFT_ARROW  65363
# define RIGHT_ARROW 65361
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define ADD 65451
# define SUBTRACT 65453
# define SUBTRACT_H 65432
# define ADD_H 65434

# define X 0
# define Y 1
# define Z 2

# define EPSILON 0.000001

# define SPHERE 0
# define CYLINDER 1
# define PLANE 2

typedef enum e_menu
{
	MODE_SPHERE = SPHERE,
	MODE_CYLINDER = CYLINDER,
	MODE_PLANE = PLANE,
	MODE_VIEW,
	MODE_LIGHT
}	t_menu;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}			t_vector;

typedef struct s_color
{
	double		r;
	double		g;
	double		b;
}			t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}			t_ambient;

typedef struct s_cam
{
	t_tuple		position;
	t_tuple		orientation;
	int			fov;
}				t_cam;

typedef struct s_light
{
	t_tuple		position;
	double		ratio;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_tuple		center;
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
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root_discriminant;
	double	two_a;
	double	t[2];
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

typedef struct s_ray
{
	t_tuple	origin;
	t_tuple	direction;
}	t_ray;

typedef struct s_local
{
	t_tuple	up;
	t_tuple	right;
	t_tuple	forward;
}	t_local;

typedef struct s_object
{
	int		type;
	t_tuple	position;
	t_tuple	orientation;
	t_tuple	normal;
	double	radius;
	double	radius_squared;
	double	height;
	double	half_height;
	t_color	color;
	t_local basis;
}	t_object;

typedef struct s_scene
{
	int			obj_count;
	t_list		*lines;
	t_ambient	ambient;
	t_cam		camera;
	t_light		light;
	t_object	*objects;
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
	t_menu		mode;
}				t_scene;

typedef struct s_intersection
{
	double		hit_distance;
	t_tuple		point;
	t_object 	*object;
	t_tuple		world_normal;
	t_tuple		world_position;
	t_tuple		local_position;
	t_tuple		local_normal;
}	t_intersection;

//---FUNCTIONS UTILS---//

void			free_split(char **s);
double			ft_atof(char *s);
int				is_valid_int(char *s);
int				is_valid_double(char *s);
void			print_list(t_list *lines);
int				is_valid_orientation_range(t_tuple orientation);
int				shut_down(t_scene *scene);
int				count_line_tab(char **s);

//--DRAW--//
void			my_mlx_pixel_put(t_scene *map, int x, int y, int colour);
int				render_image(t_scene *scene);
int				rgb_to_int(t_color colour, double light_scalar);

//---PARSING TYPE---//
int		parse_element_line(char *line, t_scene *scene, int *sphere_count);
void	prepare_initial_computations(t_object *shapes, int obj_count);

int				parse_scene(char *file, t_scene *scene);
int				parse_element_line(char *line, t_scene *scene, int *sphere_count);
int				check_sphere(char *line, t_object *sphere, int *object_index);
int				check_plane(char *line, t_object *plane, int *object_index);
int				check_cylinder(char *line, t_object *cylinder, int *object_index);
int	update_color(t_color *color, char *line);
int	update_tuple(t_tuple *tuple, char *line, double w);


//--INIT MLX--//

void			initialise_mlx(t_scene *scene);

//--INTERSECTIONS--//

t_intersection	intersect(t_object *shape, t_ray ray);
t_intersection	intersect_cylinder(t_object *cylinder, t_ray ray);
int				solve_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder);
void			prep_sphere_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder);


t_intersection	intersect_sphere(t_object *shape, t_ray ray);
t_intersection	intersection_plane(t_ray ray, t_object *plane);
t_intersection	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects);
void			apply_lighting(t_scene *scene, t_intersection *hit, int *final_color);
int				is_in_shadow(t_scene *scene, t_tuple hit_position, t_tuple light_position, t_object *object, t_tuple hit_normal);
double			specular_reflect(t_tuple hit_point, t_tuple normal, t_tuple light_dir, t_scene *scene);
void			prep_quadratic(t_quadratic *quadratic, t_ray ray, t_object *object);

//--MATHS_UTILS--//

int			is_equal(double a, double b);
double		vec3_dot(t_vector a, t_vector b);
t_vector	vec3_add(t_vector a, t_vector b);
t_vector	vec3_subtract(t_vector a, t_vector b);
t_vector	vec3_normalize(t_vector a);
t_vector	vec3_scale(t_vector a, double scale);
double		radians(double degrees);
float		get_discriminant(double a, double b, double c);
t_tuple		transform_normal(t_tuple local_normal, t_local basis);

//-- TUPLE --//

t_tuple		tuple(double x, double y, double z, double w);
t_tuple		point(double x, double y, double z);
t_tuple 	vector(double x, double y, double z);
int			tuple_is_equal(t_tuple a, t_tuple b);
t_tuple		add_tuple(t_tuple a, t_tuple b);
t_tuple		subtract_tuple(t_tuple a, t_tuple b);
t_tuple		negate_tuple(t_tuple a);
t_tuple		scale_tuple(t_tuple a, double scale);
double		magnitude(t_tuple a);
t_tuple		normalize_tuple(t_tuple a);
double		dot_tuple(t_tuple a, t_tuple b);
t_tuple		cross_tuple(t_tuple a, t_tuple b);
double		distance(t_tuple a, t_tuple b);
t_tuple 	rotate_tuple(t_tuple a, int axe, double angle);

//-- RAY --//

t_ray		new_ray(t_tuple origin, t_tuple direction);
t_tuple		position(t_ray ray, double distance);
t_ray		rotate_ray_to_local_space(t_ray ray, t_object *shape);

// --KEYBOARD--//

void	translation(t_tuple *position, int keysym);
void	rotation(t_tuple *orientation, int keysym);
void	scaling_radius(double *radius, int keysym);
void	scaling_height(double *height, int keysym);
void	prep_initial_cylinder_computations(t_object *cylinder);
void	prep_initial_sphere_computations(t_object *sphere);

#endif
