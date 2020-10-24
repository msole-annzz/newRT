#include "rtv1.h"

// double		ft_intersect_ray_sphere(t_vector *ray, t_object *s)
// {
// 	double	proection_ray;
// 	double	len_dir;
// 	// t_vector check;

// 	proection_ray = ft_vector_projection_on_ray(&s->pos, ray);
// 	len_dir = s->radius * s->radius -
// 			s->len_pos * s->len_pos +
// 			proection_ray * proection_ray;
// 	if (len_dir < 0)
// 		return (NO_INTERSECT);
// 	// if (s->len_pos > s->radius)
// 		len_dir = proection_ray - sqrt(len_dir);
// 	// else
// 	// 	len_dir = proection_ray + sqrt(len_dir);

// 	// check = ft_multiply_vector_num(ray, len_dist);
// 	// if (check.y < 5)
// 	// 	return (NO_INTERSECT);
// 	return (len_dir);
// }

// double		ft_intersect_ray_plane(t_vector *ray, t_object *plane)
// {
// 	double		angele;
// 	double		len_dist;

// 	angele = ft_vector_scalar(&plane->axis, ray);
// 	if (-angele <= 0.001f)
// 		return (NO_INTERSECT);
// 	len_dist = ft_vector_scalar(&plane->pos, &plane->axis) / angele;
// 	return (len_dist);
// }


// double		ft_intersect_circle_plane(t_vector *ray, t_object *plane, double r)
// {
// 	double		len_dist;
// 	t_vector	delta;

// 	len_dist = ft_intersect_ray_plane(ray, plane);
// 	if (len_dist == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	delta = ft_multiply_vector_num(ray, len_dist);
// 	delta= ft_sub_vectors(&delta, &plane->pos);
// 	if (ft_vector_scalar(&delta, &delta) > (r * r))
// 		return (NO_INTERSECT);
// 	return (len_dist);
// }

// double		ft_intersect_ray_hemisphere(t_vector *ray, t_object *s)
// {
// 	double	len_dir;
// 	double	len_plane;
// 	double	angle;
// 	t_vector	check;

// 	len_dir = ft_intersect_ray_sphere(ray, s);
// 	if (len_dir == NO_INTERSECT)
// 		return (NO_INTERSECT);
// 	else
// 	{
// 		check = ft_multiply_vector_num(ray, len_dir);
// 		check = ft_sub_vectors(&check, &s->pos);
// 		ft_unit_vector(&check);
// 		angle = ft_vector_scalar(&check, &s->axis);
// 		if (angle > 0)
// 		{
// 			len_plane = ft_intersect_circle_plane (ray, s, s->radius);
// 			if (len_plane != NO_INTERSECT)
// 			{
// 				s->check = e_caps;
// 				return (len_plane);
// 			}
// 			return (NO_INTERSECT);
// 		}
// 	}
// 	s->check = e_body;
// 	return (len_dir);
// }


// /*
// **Check if the ray and cilinder intersect
// ** FIST
// ** V_1 = (Ray - ft_vector_scalar(Ray, Nor) * Nor)
// ** V_1 = ft_multiply_vector_num(Nor, ft_vector_scalar(Ray, Nor))
// ** V_1 = ft_subtraction_vector(Ray, V_1)
// ** A = ft_vector_scalar(V_1, V_1)
// ** V_2 = ft_vector_scalar(Pos, Nor) * Nor) - Pos
// ** V_2 = ft_multiply_vector_num(Nor, ft_vector_scalar(Pos, Nor))
// ** V_2 = ft_subtraction_vector(V_2, Pos)
// ** B = 2 * (Ray - ft_vector_scalar(Ray, Nor) * Nor) * -1 * (Vector_Pos * V_2)
// ** B = 2 * ft_vector_scalar(V_1, V_2)
// ** C = ft_vector_scalar(V_2, V_2) - Radius^2
// ** SECOND
// ** A = Ray|Ray - (Ray|Nor_p)^2
// ** B = -2 * (Ray|Pos - (Ray|Nor_p)*(Pos|Nor_p))
// ** C = Pos|Pos - (Pos|Nor_p)^2 - Radius * Radius
// ** double discr = B * B - 4 * A * C;
// ** void		ft_solve_discriminant(t_discr *discr)
// ** {
// ** 	discr->discr = discr->b * discr->b - 4 * discr->a * discr->c;
// ** }
// */

// double		ft_intersect_ray_cylinder(t_vector *ray, t_object *cil)
// {
// 	t_vector	v1;
// 	t_discr		cilindr;
// 	double		len_dist;

// 	v1 = ft_multiply_vector_num(&cil->axis,\
// 								ft_vector_scalar(ray, &cil->axis));
// 	v1 = ft_sub_vectors(ray, &v1);
// 	cilindr.a = ft_vector_scalar(&v1, &v1);
// 	cilindr.b = 2 * ft_vector_scalar(&v1, &cil->discr.v2);
// 	cilindr.c = cil->discr.c;
// 	len_dist = ft_solve_quadratic_equation_2(&cilindr);
// 	return (len_dist);
// }

// double		ft_intersect_ray_cone(t_vector *ray, t_object *cone)
// {
// 	t_discr	conus;
// 	double	ray_norm;
// 	double	ray_ray;
// 	double	ray_pos;
// 	double	len_dist;

// 	ray_ray = ft_vector_scalar(ray, ray);
// 	ray_norm = ft_vector_scalar(ray, &cone->axis);
// 	ray_pos = ft_vector_scalar(ray, &cone->pos);
// 	conus.a = ray_ray - cone->discr.k_tan * (ray_norm * ray_norm);
// 	conus.b = 2 * (cone->discr.k_tan * ray_norm * cone->discr.pos_n_p \
// 							- ray_pos);
// 	conus.c = cone->discr.c;
// 	len_dist = ft_solve_quadratic_equation_2(&conus);
// 	return (len_dist);
// }

// double	ft_raytrace_objects(t_vector *ray, t_object *object)
// {
// 	double		len_dist;

// 	len_dist = -1;
// 	if (object->type == e_sphere)
// 		len_dist = ft_intersect_ray_sphere(ray, object);
// 	if (object->type == e_plane) 
// 		len_dist = ft_intersect_ray_plane(ray, object);
// 	if (object->type == e_cylindr)
// 		len_dist = ft_intersect_ray_cylinder(ray, object);
// 	if (object->type == e_cone)
// 		len_dist = ft_intersect_ray_cone(ray, object);
// 	if (object->type == e_hemisphere)
// 		len_dist = ft_intersect_ray_hemisphere(ray, object);
// 	return (len_dist);
// }
