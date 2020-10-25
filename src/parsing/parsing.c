
#include "rtv1.h"

void	camera_parsing(char *str, int *index, t_rtv *rt)
{
	int checker;

	checker = 0;
	//rt->camera = NULL;
	rt->camera = ft_memalloc(sizeof(t_camera));
	if (rt->camera == NULL)
		ft_exit(ERR_CREAT_TO_ARR);
	//rt->camera = (t_camera *)malloc(sizeof(t_camera));
	// добавить проверку выделения памяти
	while (((checker % 2) == 0) && (checker < 4))
	{
		if (find_quotes(str, index, "\"position\"\0"))
		{
			rt->camera->start = parsing_coordinates(str, index);//rt->camera.plase
			*index += 1;
			checker++;
		}
		else if (find_quotes(str, index, "\"angle_direction\"\0"))
		{
			rt->camera->angle= parsing_angles(str, index);//rt->camera.rotate
			checker++;
		}
		else
			file_contents_error();
		checker++;
	}
	rt->camera->dir = (t_vector){0, 0 ,1};
	rt->camera->pos = rt->camera->start;
}

void	check_normals(t_rtv *rt)
{
	int n;

	n = 0;
	while (rt->object[n] != NULL)
	{
		if ((rt->object[n]->type == 2) || (rt->object[n]->type == 3) ||\
			(rt->object[n]->type == 4))
			if ((rt->object[n]->axis.x == 0) &&\
			(rt->object[n]->axis.y == 0) && \
			(rt->object[n]->axis.z == 0))
				file_contents_error();
		n++;
	}
}

void	parsing_cont(char *str, int *index, t_rtv *rt)
{

	if (find_quotes(str, index, "\"objects\"\0"))
	{
		*index += 1;
		objects_parsing(str, index, rt);
	//	printf("ob");
	}
	else
		file_contents_error();
	printf("obj = %d\n", rt->n_objects);
	check_normals(rt);
}

void	parsing(char *str, t_rtv *rt)
{
	int *index;
	int x;

	x = 1;
	index = &x;
	if (find_quotes(str, index, "\"camera\"\0"))
	{
		*index += 2;
		camera_parsing(str, index, rt);
		//printf("cam");
	}
	else
		file_contents_error();
	if (find_quotes(str, index, "\"lights\"\0"))
	{
		*index += 1;
		lights_parsing(str, index, rt);
		//printf("li");
	}
	else
		file_contents_error();
	parsing_cont(str, index, rt);
}
