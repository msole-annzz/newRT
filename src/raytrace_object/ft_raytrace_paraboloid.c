#include "rtv1.h"

t_cross	ft_paraboloid(t_object *object, t_vector *ray)
{
	double		a;
	double		b;
	double		c;
	t_vector	oc;
	t_vector	normal;

	oc = ft_sub_vectors(origin, &object->pos);
	normal = object->axis;
	normal = ft_mult_num_vector(1 / ft_length_vector(normal), normal);

	a = ft_dotproduct(direction, direction) - (ft_dotproduct(direction, normal) * ft_dotproduct(direction, normal));
	b = 2 * (ft_dotproduct(oc, direction) - (ft_dotproduct(direction, normal) * (ft_dotproduct(oc, normal) + 2 * object.k_paraboloid)));
	c = ft_dotproduct(oc, oc) - (ft_dotproduct(oc, normal) * (ft_dotproduct(oc, normal) + 4 * object.k_paraboloid));
	return (ft_quadrsolution(a, b, c));
}