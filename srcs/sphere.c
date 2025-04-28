
#include "minirt.h"
double	specular_reflect(t_tuple hit_point, t_tuple normal, t_tuple light_dir, t_scene *scene)
{
	t_tuple		cam_dir;
	t_tuple		reflect_dir;
	double		dot_reflect_cam; // multi entre direction reflection et direction de la camera
	double		specular;
	double		coeff = 0.7;
	double		shininess = 100;

	cam_dir = normalize_tuple(subtract_tuple(scene->camera.position, hit_point));
	reflect_dir = subtract_tuple(scale_tuple(normal, 2.0 * dot_tuple(normal, light_dir)),light_dir);
	reflect_dir = normalize_tuple(reflect_dir);
	dot_reflect_cam = dot_tuple(reflect_dir, cam_dir);
	if (dot_reflect_cam < 0)
		dot_reflect_cam = 0;
	specular = coeff * scene->light.ratio * pow(dot_reflect_cam, shininess);
	return (specular);
}

void	prep_sphere_quadratic(t_quadratic *quadratic, t_ray ray, t_object *sphere)
{
	t_tuple	diff_sphere_camera;

	diff_sphere_camera = subtract_tuple(ray.origin, sphere->position);
	quadratic->a = dot_tuple(ray.direction, ray.direction);
	quadratic->b = 2.0f * dot_tuple(diff_sphere_camera, ray.direction);
	quadratic->c = dot_tuple(diff_sphere_camera, diff_sphere_camera) - (pow((sphere->diametre * 0.5), 2));
	quadratic->discriminant = get_discriminant(quadratic->a, quadratic->b, quadratic->c);
}

void	prep_quadratic(t_quadratic *quadratic, t_ray ray, t_object *object)
{
	if (object->type == SPHERE)
		prep_sphere_quadratic(quadratic, ray, object);
	//else if (object->type == CYLINDER)
	//	prep_cylinder_quadratic(quadratic, ray, object);
	//else if (object->type == PLANE)
	//	prep_plane_quadratic(quadratic, ray, object);
	return ;
}

t_intersection	finalize_hit_data(t_ray ray, t_intersection intersection)
{
	//t_tuple centre = intersection.object->position;
	//t_matrix m = translation(centre.x, centre.y, centre.z);
	//t_ray r2 = transform(ray, m);
	//ray.origin = mat4_multiply_tuple(m, ray.origin);
	intersection.world_position = position(ray, intersection.hit_distance);
	if (intersection.object->type == PLANE)
	{
		intersection.world_normal = intersection.object->normal;
		ray.origin = subtract_tuple(ray.origin, intersection.object->point);

	}
	else
	{
		ray.origin = subtract_tuple(ray.origin, intersection.object->position);
		intersection.world_normal = normalize_tuple(subtract_tuple(intersection.world_position, intersection.object->position));
		intersection.world_position = add_tuple(intersection.world_position, intersection.object->position);

	}
	//intersection.world_normal = normalize_tuple(intersection.world_position);
	return (intersection);
}

t_intersection	get_closest_intersection(t_scene *scene, t_ray ray, t_object *objects)
{
	t_intersection	closest_intersection;
	t_object	*closest_shape = NULL;
	double	current_distance;
	int	i = 0;
	t_quadratic q;
	
	closest_intersection.hit_distance = INT_MAX;

	while(i < scene->obj_count)
	{
		if (objects[i].type == PLANE)
		{
			current_distance = intersection_plane(ray, &objects[i]);
			if ((current_distance < closest_intersection.hit_distance) && (current_distance >= 0))
			{
				closest_intersection.hit_distance = current_distance;
				closest_shape = &objects[i];
			}
			i++;
			continue;
		}
		prep_sphere_quadratic(&q, ray, &objects[i]);
		if (q.discriminant > 0.0)
		{
			current_distance = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
			if ((current_distance < closest_intersection.hit_distance) && (current_distance >= 0))
			{
				closest_intersection.hit_distance = current_distance;
				closest_shape = &objects[i];
			}
		}
		i++;
	}
	if (closest_shape == NULL)
	{
		closest_intersection.hit_distance = -1;
		return (closest_intersection);
	}
	closest_intersection.object = closest_shape;
	return (finalize_hit_data(ray, closest_intersection));
}

double	distance(t_tuple a, t_tuple b)
{
	t_tuple c = subtract_tuple(a, b);
	double distance = magnitude(c);
	return (distance);
}

int	is_in_shadow(t_scene *scene, t_tuple hit_position, t_tuple light_position)
{
	t_ray shadow_ray;
	t_intersection shadow_intersection;
	double	light_distance;

	shadow_ray.origin = hit_position;
	shadow_ray.direction = normalize_tuple(subtract_tuple(light_position, hit_position));
	light_distance = distance(hit_position, light_position);
	shadow_intersection = get_closest_intersection(scene, shadow_ray, scene->objects);
	if (shadow_intersection.hit_distance >= 0 && shadow_intersection.hit_distance < light_distance)
		return (1);
	return (0);
}

// Doesn't take into account colour of the light
void	apply_lighting(t_scene *scene, t_intersection *hit, int *final_color)
{
	t_tuple	light_direction;
	double	dot;
	double	light_scalar;

	light_direction = subtract_tuple(scene->light.position, hit->world_position);
	light_direction = normalize_tuple(light_direction);

	if (is_in_shadow(scene, hit->world_position, scene->light.position))
	{
		light_scalar = scene->ambient.ratio;
	}
	else
	{
		dot = dot_tuple(hit->world_normal, light_direction);
		if (dot < 0)
			dot = 0;
		light_scalar = dot * scene->light.ratio;
		light_scalar += scene->ambient.ratio;
		light_scalar += specular_reflect(hit->world_position, hit->world_normal, light_direction, scene);
		if (light_scalar > 1.0)
			light_scalar = 1;
	}
	*final_color = rgb_to_int(hit->object->color, light_scalar);
}

// need to understand how to manage shadows...
int	get_pixel_color(t_scene *scene, t_ray ray, t_object *objects)
{
	int	final_color;
	t_intersection	closest_intersection;

	final_color = 0;
	closest_intersection = get_closest_intersection(scene, ray, objects);
	if (closest_intersection.hit_distance < 0)
		return (final_color); // but could also just be a shadow??...
	apply_lighting(scene, &closest_intersection, &final_color);
	//apply_shadow(scene, &closest_intersection, ray, &final_color);
	
	return (final_color);
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
			ray_direction = vector(normalised_col * aspect_ratio * fov_scale, normalised_row * fov_scale, 1);
			ray = new_ray(scene->camera.position, normalize_tuple(ray_direction));
			color = get_pixel_color(scene, ray, scene->objects);
			my_mlx_pixel_put(scene, col, row, color);
			col++;
		}
		row++;
	}
	printf("Finished render\n");
	return (0);
}
