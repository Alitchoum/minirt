
#include "minirt.h"

// RETURNS DOT PRODUCT OF TWO VECTORS
// Multiplies the matching variables together then adds them up

float	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
}

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

// transofrming rgb to final int colour (taking into account light scalar)
int	rgb_to_int(t_color colour, double light_scalar)
{
	colour.r *= light_scalar;
	colour.g *= light_scalar;
	colour.b *= light_scalar;
	return (colour.r << 16 | colour.g << 8 | colour.b);
}

// returns what you need to multiply the colour by to take into account light
// Essentially, solving the quadratic equation to find closest intersection to the camera
// between 0 and 1
double	solve_min_quadratic(double a, double b, double discriminant)
{
	double	t0;
	double	t1_closest;

	t0 = (-b + sqrt(discriminant)) / (2.0 * a);
	t1_closest = (-b - sqrt(discriminant)) / (2.0 * a);

	if (t0 > 0 && (t1_closest < 0 || t0 < t1_closest))
		return (t0);
	if (t1_closest > 0)
		return (t1_closest);
	return (-1);
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

int	get_color(t_vector ray_origin, t_vector ray_direction, t_sphere *sphere, t_scene *scene)
{
	double		a;
	double		b;
	double		c;
	double		min_quad;
	double		discriminant;
	t_color		color;
	t_vector	hit_point;
	t_vector	normal;
	t_vector	light_dir;
	t_vector	diff_sphere_camera;

	color = sphere->color;

	diff_sphere_camera = vec3_subtract(ray_origin, sphere->center);

	a = vec3_dot(ray_direction, ray_direction);
	b = 2.0f * vec3_dot(diff_sphere_camera, ray_direction);
	c = vec3_dot(diff_sphere_camera, diff_sphere_camera) - ((sphere->diametre * 0.5) * (sphere->diametre * 0.5));

	// IF NO INTERSECTION(S) WERE FOUND, return BLACK
	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0.0)
		return (0);
	//printf("discriminant: %f\n", discriminant);
	// ELSE, SOlVE THE EQUATION TO GET THE CLOSEST POINT OF INTERSECTION TO THE CAMERA
	min_quad = solve_min_quadratic(a, b, discriminant);
	if (min_quad < 0)
		return (0);
	hit_point = vec3_add(ray_origin, vec3_scale(ray_direction, min_quad));
	normal = vec3_subtract(hit_point, sphere->center);
	normal = vec3_normalize(normal);
	
	light_dir = vec3_subtract(scene->light.position, hit_point);
	light_dir = vec3_normalize(light_dir);
	
	double dot = vec3_dot(normal, light_dir);
	if (dot < 0)
		dot = 0;
	double	light_scaler = dot * scene->light.ratio;
	light_scaler += scene->ambient.ratio;
	if (light_scaler > 1.0)
		light_scaler = 1;
	return (rgb_to_int(color, light_scaler));
}


int	render_image(t_scene *scene)
{
	double aspect_ratio = W_WIDTH / (double)W_HEIGHT; // to avoid distorting
	t_vector ray_origin = scene->camera.position;
	t_vector ray_direction;
	//t_vector camera_orientation;
	double	normalised_row;
	double	normalised_col;
	double	fov_scale = tan((scene->camera.fov * 0.5) * M_PI / 180.0);

	int	col = 0;
	int	row = 0;
	int	i;
	int	color;
	// PUT A COLOUR ON EACH PIXEL OF THE SCREEN
	while (row < W_HEIGHT)
	{
		col = 0;
		while (col < W_WIDTH)
		{
			// NORMALIZE THE PIXEL BETWEEN -1 AND 1
			normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);// * aspect_ratio;
			normalised_row = (double)row / (double)W_HEIGHT * 2 - 1;

			ray_direction.x = normalised_col * aspect_ratio * fov_scale;
			ray_direction.y = normalised_row * fov_scale;
			ray_direction.z = 1.0;
			ray_direction = vec3_normalize(ray_direction);

			//FIND THE COLOUR THE PIXEL SHOULD BE
			i = 0;
			color = 0;
			while (i < scene->nb_sp)
			{
				color = get_color(ray_origin, ray_direction, &scene->spheres[i], scene);
				if (color != 0)
					break;
				i++;
			}
			if (color != 0)
			{
				my_mlx_pixel_put(scene, col, row, color);
			}
			col++;
		}
		row++;
	}
	return (0);
}
