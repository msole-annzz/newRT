
#include "rtv1.h"

int		fill_objects_start(char *str, int *index, t_rtv *rt, int counter)
{
	if ((find_quotes(str, index, "\"type\"\0")))
	{
		rt->object[rt->current_object]->type = parsing_object_type(str, index);
		if (str[*index] == ',')
			*index = *index + 1;
		if (str[*index] == '}')
			*index = *index + 2;
		counter++;
		//printf("type %c,%c,%c,%c,%c\n", str[*index],str[*index+1],str[*index+2],str[*index+3],str[*index+4]);
	}
	else if (find_quotes(str, index, "\"position\"\0"))
	{
		//printf("%c,%c,%c,%c,%c\n", str[*index],str[*index+1],str[*index+2],str[*index+3],str[*index+4]);
		//rt->object[rt->current_object]->center = parsing_coordinates(str, index);
		rt->object[rt->current_object]->pos = parsing_coordinates(str, index);
		counter++;
		*index = *index + 1;
		//printf("%c,%c,%c,%c,%c\n", str[*index],str[*index+1],str[*index+2],str[*index+3],str[*index+4]);
	}
	return (counter);
}

int		fill_objects_middle(char *str, int *index, t_rtv *rt, int counter)
{
	if (find_quotes(str, index, "\"color\"\0"))
	{
		rt->object[rt->current_object]->color = parsing_color(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"radius\"\0"))
	{
		rt->object[rt->current_object]->radius = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"reflection\"\0"))
	{
		rt->object[rt->current_object]->reflection = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"refraction\"\0"))
	{
		rt->object[rt->current_object]->refraction = double_parsing(str, index);
		counter = counter + 1;
	}
	return (counter);
}

int		fill_objects_end(char *str, int *index, t_rtv *rt, int counter)
{
	if (find_quotes(str, index, "\"angle\"\0"))
	{
		rt->object[rt->current_object]->angle = double_parsing(str, index);
		rt->object[rt->current_object]->angle *= (PI / 180);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"axis\"\0"))
	{
		rt->object[rt->current_object]->axis = \
		parsing_coordinates(str, index);
		*index = *index + 1;
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"axis_angle\"\0"))
	{
		rt->object[rt->current_object]->angle_n = \
		parsing_coordinates(str, index);
		rt->object[rt->current_object]->angle_n.x *= (PI / 180);
		rt->object[rt->current_object]->angle_n.y *= (PI / 180);
		rt->object[rt->current_object]->angle_n.z *= (PI / 180);
		*index = *index + 1;
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"specularity\"\0"))
	{
		rt->object[rt->current_object]->specular = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"high\"\0"))
	{
		rt->object[rt->current_object]->high = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"k_paraboloid\"\0"))
	{
		rt->object[rt->current_object]->k_paraboloid = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"min\"\0"))
	{
		rt->object[rt->current_object]->min = double_parsing(str, index);
		counter = counter + 1;
	}
	else if (find_quotes(str, index, "\"max\"\0"))
	{
		rt->object[rt->current_object]->max = double_parsing(str, index);
		counter = counter + 1;
	}

	return (counter);
}

int		fill_objects(char *str, int *index, t_rtv *rt, int counter)
{
	int checker;

	checker = counter;
	if ((str[*index + 1] == 't') || (str[*index + 1] == 'p'))
	{
		//printf("t or p\n");
		counter = fill_objects_start(str, index, rt, counter);
	}
	else if ((str[*index + 1] == 'c') || (str[*index + 1] == 'r'))
	{
		//printf("c or r\n");
		counter = fill_objects_middle(str, index, rt, counter);
	}
	else if ((str[*index + 1] == 'a') || (str[*index + 1] == 'n') || (str[*index + 1] == 's') || (str[*index + 1] == 'h') || (str[*index + 1] == 'k') || (str[*index + 1] == 'm'))
		{
		counter = fill_objects_end(str, index, rt, counter);
		//printf("k ob %d\n", rt->current_object);
		}
	else
	{
		//printf("error");
		file_contents_error();
	}
	if (counter != checker + 1)
		file_contents_error();
	return (counter);
}

void	objects_parsing(char *str, int *index, t_rtv *rt)
{
	int n;
	int counter;

	n = *index;
	counter = 0;
	malloc_objects(str, index, rt, n);
	n = 0;
	while (n < rt->n_objects)
	{
		rt->current_object = n;
		counter = fill_objects(str, index, rt, counter);
		if (counter == 14)
		{
			ft_rotate_vector(&rt->object[n]->angle_n, &rt->object[n]->axis);
			n++;
			counter = 0;
			*index = *index + 1;
		}
	}
}
