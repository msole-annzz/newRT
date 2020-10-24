#include "rtv1.h"

// double		check_intersect(t_vector *ray, t_vector *pos,t_vector *axis, double len)
// {
// 	t_vector	intersect;
// 	double		check;

// 	intersect = ft_multiply_vector_num(ray, len);
// 	intersect = ft_sub_vectors(&intersect, pos);
// 	check = ft_vector_projection_on_ray(&intersect, axis);
// 	return (check);
// }

void	calculate_len_plane(t_vector *ray, t_object *sphere, t_cross *result)
{
	t_vector	intersect;
	double		angle;

	angle = ft_vector_scalar(&sphere->axis, ray);
	if (sphere->min == 0.0)
		result->len = ft_vector_scalar(&sphere->pos, &sphere->axis) / angle;
	else
	{
		intersect = ft_multiply_vector_num(&sphere->axis, sphere->min);
		intersect = ft_add_vectors(&sphere->pos, &intersect);
		result->len = ft_vector_scalar(&intersect, &sphere->axis) / angle;
	}
	result->id = INTERSECT;
	result->check = e_caps;
}

t_cross		ft_intersect_ray_hemisphere(t_object *sphere, t_vector *ray)
{
	t_cross		result;
	double		proection_ray;
	double		len;
	double		check;

	result.id = NO_INTERSECT;
	proection_ray = ft_vector_projection_on_ray(&sphere->pos, ray);
	len = sphere->radius * sphere->radius - sphere->len_pos * sphere->len_pos +
			proection_ray * proection_ray;
	if (len < 0)
		return (result);
	result.len = proection_ray - sqrt(len);
	check = check_intersect(ray, &sphere->pos, &sphere->axis, result.len);
	if (check <= sphere->min)
	{
		result.id = INTERSECT;
		result.check = e_body;
		return (result);
	}
	result.len = proection_ray + sqrt(len);
	check = check_intersect(ray, &sphere->pos, &sphere->axis, result.len);
	if (check <= sphere->min)
		calculate_len_plane(ray, sphere, &result);
	return (result);
}
