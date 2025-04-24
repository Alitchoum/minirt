
#include "minirt.h"

// RETURNS DOT PRODUCT OF TWO VECTORS
// Multiplies the matching variables together then adds them up

float	get_discriminant(double a, double b, double c)
{
	return ((b * b) - (4 * a * c));
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

int	get_color(t_ray ray, t_object *sphere, t_scene *scene)
{
	double		a;
	double		b;
	double		c;
	double		distance;
	double		discriminant;
	t_color		color;
	t_tuple	hit_point;
	t_tuple	normal;
	t_tuple	light_dir;
	t_tuple		diff_sphere_camera;

	color = sphere->color;

	diff_sphere_camera = subtract_tuple(ray.origin, sphere->position);

	a = dot_tuple(ray.direction, ray.direction);
	b = 2.0f * dot_tuple(diff_sphere_camera, ray.direction);
	c = dot_tuple(diff_sphere_camera, diff_sphere_camera) - (pow((sphere->diametre * 0.5), 2));

	// IF NO INTERSECTION(S) WERE FOUND, return BLACK
	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0.0)
		return (0);
	// ELSE, SOlVE THE EQUATION TO GET THE CLOSEST POINT OF INTERSECTION TO THE CAMERA
	distance = solve_min_quadratic(a, b, discriminant);
	if (distance < 0)
		return (0);
	// hit point = ray origin + ray direction * t(distance);
	hit_point = position(ray, distance);
	normal = subtract_tuple(hit_point, sphere->position);
	normal = normalize_tuple(normal);
	
	light_dir = subtract_tuple(scene->light.position, hit_point);
	light_dir = normalize_tuple(light_dir);
	
	double dot = dot_tuple(normal, light_dir);
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
	t_ray	ray;

	t_tuple ray_direction;
	//t_vector camera_orientation;
	double	normalised_row;
	double	normalised_col;
	double	fov_scale = tan(radians((scene->camera.fov * 0.5)));

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
			normalised_col = ((double)col / (double)W_WIDTH * 2 - 1);
			normalised_row = (double)row / (double)W_HEIGHT * 2 - 1;

			// CALCULATE RAY DIRECTION
			ray_direction = vector(normalised_col * aspect_ratio * fov_scale, normalised_row * fov_scale, 1);

			// CREATE A NEW RAY (ORIGIN, DIRECTION)
			ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
			//FIND THE COLOUR THE PIXEL SHOULD BE
			i = 0;
			color = 0;
			while (i < 2)
			{
				color = get_color(ray, &scene->objects[i], scene);
				if (color != 0)
				{
					my_mlx_pixel_put(scene, col, row, color);
				}
				i++;
			}
			col++;
		}
		row++;
	}
	return (0);
}
