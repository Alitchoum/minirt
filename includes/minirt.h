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

#define  WHITESPACE " \t" //a completer00

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

# define EPSILON 0.00001

# define SPHERE 0
# define CYLINDER 1
# define PLANE 2

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef struct s_matrix
{
	int size;
	double m[4][4];
}	t_matrix;

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
	t_matrix		translation_matrix[4][4]; //moves to the correct position
	t_matrix		scaling_matrix[4][4]; // adjusts the sphere's radius
	t_matrix		transform_matrix[4][4]; // combines the 2
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

typedef struct s_object
{
	int	type;
	t_tuple	position;
	t_tuple	point;
	t_tuple	orientation;
	t_tuple	normal;
	double	radius;
	double	diametre;
	double	height;
	t_matrix	transform_matrix;
	t_matrix	rotation_matrix;
	t_matrix	translation_matrix;
	double	determinant;
	t_color	color;
}	t_object;


typedef struct s_scene
{
	int		obj_count;
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
}				t_scene;

typedef struct s_intersection
{
	double		hit_distance;
	t_tuple		point;
	t_object 	*object;
	t_tuple		world_normal;
	t_tuple		world_position;
}	t_intersection;

int		parse_scene(char *file, t_scene *scene);

//---FUNCTIONS UTILS---//
void	free_split(char **s);
double	ft_atof(char *s);
int		is_valid_int(char *s);
int		is_valid_double(char *s);
void	print_list(t_list *lines);
int	is_valid_orientation_range(t_tuple orientation);

//--DRAW--//
void	my_mlx_pixel_put(t_scene *map, int x, int y, int colour);
int		render_image(t_scene *scene);
int	rgb_to_int(t_color colour, double light_scalar);

//---PARSING TYPE---//
int		parse_element_line(char *line, t_scene *scene, int *sphere_count);

//--INIT MLX--//
void	initialise_mlx(t_scene *scene);

//--INTERSECTIONS--//
t_intersection	intersect(t_object *shape, t_ray ray);
t_intersection	intersect_cylinder(t_object *cylinder, t_ray ray);
void	prep_cylinder_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder);
void	prep_sphere_quadratic(t_quadratic *q, t_ray ray, t_object *cylinder);
t_intersection	intersect_sphere(t_object *shape, t_ray ray);
double	intersection_plane(t_ray ray, t_object *plane);
t_intersection	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects);
void	apply_lighting(t_scene *scene, t_intersection *hit, int *final_color);
int	is_in_shadow(t_scene *scene, t_tuple hit_position, t_tuple light_position);
double	specular_reflect(t_tuple hit_point, t_tuple normal, t_tuple light_dir, t_scene *scene);
void	prep_quadratic(t_quadratic *quadratic, t_ray ray, t_object *object);

//--MATHS_UTILS--//
int	is_equal(double a, double b);
double	vec3_dot(t_vector a, t_vector b);
t_vector	vec3_add(t_vector a, t_vector b);
t_vector	vec3_subtract(t_vector a, t_vector b);
t_vector vec3_normalize(t_vector a);
t_vector	vec3_scale(t_vector a, double scale);
double	radians(double degrees);
float	get_discriminant(double a, double b, double c);

//-- TUPLE --//
//
t_tuple	tuple(double x, double y, double z, double w);
t_tuple	point(double x, double y, double z);
t_tuple vector(double x, double y, double z);
int	tuple_is_equal(t_tuple a, t_tuple b);
t_tuple	add_tuple(t_tuple a, t_tuple b);
t_tuple	subtract_tuple(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple a);
t_tuple	scale_tuple(t_tuple a, double scale);
double	magnitude(t_tuple a);
t_tuple	normalize_tuple(t_tuple a);
double dot_tuple(t_tuple a, t_tuple b);
t_tuple	cross_tuple(t_tuple a, t_tuple b);
double	distance(t_tuple a, t_tuple b);

//-- MATRIX --//
t_matrix	new_matrix(int size);
int	matrix_are_equal(t_matrix a,t_matrix b);
t_matrix	mat4_multiply(t_matrix *result, t_matrix a, t_matrix b);
t_tuple	mat4_multiply_tuple(t_matrix matrix, t_tuple tup);
void	set_identity_matrix(t_matrix *matrix);
t_matrix	get_identity_matrix(void);
t_matrix	transpose_matrix(t_matrix *matrix);
double	determinant_mat2(t_matrix *matrix);
t_matrix	submatrix(t_matrix *from, int row_del, int col_del);
double	minor(t_matrix *old, int row, int col);
double	cofactor(t_matrix *matrix, int row, int col);
double	determinant(t_matrix *matrix);
t_matrix	inverse(t_matrix *matrix);
void	run_matrix_tests(void);
t_ray	transform(t_ray ray, t_matrix matrix);
void	set_transform(t_object *shape, t_matrix matrix);
void	print_matrix(t_matrix *m);

//-- MATRIX TRANSFORMATIONS --//
void	run_transformation_tests(void);
t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	rotation_x(double radians);
t_matrix	rotation_y(double radians);
t_matrix	rotation_z(double radians);

// RAY
t_ray	new_ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray ray, double distance);
int	matrix_are_equal(t_matrix a, t_matrix b);
#endif
