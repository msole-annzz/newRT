/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:39:48 by wrhett            #+#    #+#             */
/*   Updated: 2020/10/25 16:36:03 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_navigation(t_rtv *p)
{
	char	*str;
	char	*coord;

	coord = ft_itoa(p->fov);
	str = ft_strjoin(STR2, coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 20, COLOR_STR, str);
	free(coord);
	free(str);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 40, COLOR_STR, STR1);
	coord = ft_itoa(p->camera->start.x);
	str = ft_strjoin("X = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 60, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.y);
	str = ft_strjoin("Y = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 80, COLOR_STR, str);
	free(coord);
	free(str);
	coord = ft_itoa(p->camera->start.z);
	str = ft_strjoin("Z = ", coord);
	mlx_string_put(p->mlx_ptr, p->win_ptr, 20, 100, COLOR_STR, str);
	free(coord);
	free(str);
}

void	ft_mlx_init(t_rtv *p, char *str)
{
	p->mlx_ptr = mlx_init();
	p->win_ptr = mlx_new_window(p->mlx_ptr, p->width, p->height, str);
	p->img_ptr = mlx_new_image(p->mlx_ptr, p->width, p->height);
	p->draw =
	(int *)mlx_get_data_addr(p->img_ptr, &p->bpp, &p->size_line, &p->endian);
}

void	ft_init_configuration(t_rtv *p, char *str)
{
	p->width = WIDHT;
	p->height = HIGHT;
	p->x0 = (p->width - 1) / 2.0;
	p->y0 = (p->height - 1) / 2.0;
	p->fov = (double)p->width;
	p->mouse_key = 0;
	p->mouse_x = 0;
	p->mouse_y = 0;
	p->window_menu = CLOSED;
	p->samples = MIN_SAMPLE;
	p->depth_mirror = DEPTH_REFL;
	p->depth_refract = DEPTH_REFR;
	p->camera->dir.z = p->fov;
	ft_mlx_init(p, str);
}

void	ft_paint_scene(t_rtv *paint)
{
	ft_multi_thread_paint(paint);
	// ft_paint_object(p);

	// mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	// print_navigation(p, p->camera);
	// print_instructions(p);
	expose_hook(paint);
}

int		main(int argc, char **argv)
{
	t_rtv	paint;
	// int		fd = 0;

	// int		num;
	//char	*str;

	//str = NULL;

	if (argc != 2)
		ft_exit(ERR_USAGE);

	// paint = (t_rtv *)malloc(sizeof(t_rtv));
// if (!(paint = (t_rtv *)malloc(sizeof(t_rtv))) );//||\
// 					!(scene->mouse = (t_mouse *)malloc(sizeof(t_mouse))))
// 		memory_allocation_error();
	read_file(&paint, argv[1]);
	// check_parsing(&paint); // DELETE ME

	//if ((fd = open(argv[1], O_RDONLY)) <= 0)
	//	ft_exit(ERR_FILE_OPEN);
	//if ((num = how_many_object(fd)) == 0)
	//	ft_exit("No object for raytrasing. Exit");
	//paint.object = (t_object **)malloc(sizeof(t_object *) * (paint.n_objects + 1));
	//paint.object = (t_object **)malloc(sizeof(t_object *) * (num + 1));
	// if (paint.object == NULL)
	// 	ft_exit(ERR_CREAT_TO_ARR);
	// paint.light = NULL;
	// paint.camera = NULL;
	// paint.width = WIDHT;
	// paint.height = HIGHT;
	paint.name_file = argv[1];
	// init_tab_object(&paint, argv[1]);




	ft_init_configuration(&paint, argv[1]);
	calculate_constant(&paint, &paint.camera->start);
	ft_paint_scene(&paint);
	ft_hook_operation(&paint);

	return (0);
}
