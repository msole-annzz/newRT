
#include "rtv1.h"

void		check_parsing(t_rtv *rt)
{
	int n = 0;
	printf("\e[92;4mCamera:\n\e[0m");
	printf("Rotate:\t\t\tPlase:\n");
	printf("x %f\t\tx %f\n", rt->camera->angle.x, rt->camera->pos.x);
	printf("y %f\t\ty %f\n", rt->camera->angle.y, rt->camera->pos.y);
	printf("z %f\t\tz %f\n", rt->camera->angle.z, rt->camera->pos.z);
	printf("\n");
	printf("\e[92;4mLights:\n\e[0m");
	printf("Type:\t\tPlase:\t\tDirection:\tIntensity:\t%d\n", rt->n_lights);
	while (n < rt->n_lights)
	{
		printf("%d\t\tx %f\tx %f\t\t%f\n", rt->lights[n]->type,rt->lights[n]->pos.x,rt->lights[n]->direction.x, rt->lights[n]->intensity);
		printf("\t\ty %f\ty %f\n", rt->lights[n]->pos.y,rt->lights[n]->direction.y);
		printf("\t\tz %f\tz %f\n", rt->lights[n]->pos.z, rt->lights[n]->direction.z);

		printf("Color:\n");
		printf("r %d\n", rt->lights[n]->color.red);
		printf("g %d\n", rt->lights[n]->color.green);
		printf("b %d\n", rt->lights[n]->color.blue);
		printf("\n");
		n++;
	}
	n = 0;
	printf("\e[92;4mObjects:\n\e[0m");

	while (rt->object[n] != NULL)
	{
		printf("Type:\t\tRadius:\t\t\tAngel:\t\tHigh:\n");
		printf("\e[93;4m%d\e[0m\t\t%f\t\t%f\t\t%f\n", rt->object[n]->type,rt->object[n]->radius, rt->object[n]->angle, rt->object[n]->high);
		printf("Specularity:\tReflection:\t\tRefraction:\n");
		printf("%d\t\t%f\t\t%f\n", rt->object[n]->specular, rt->object[n]->reflection, rt->object[n]->refraction);
		printf("Position:\t\tColor:\t\tNormal:\t\tNormal Angel:\n");
		printf("x %f\t\tr %d\t\tx %f\t\tx %f\n", rt->object[n]->pos.x, rt->object[n]->color.red, rt->object[n]->axis.x, rt->object[n]->angle_n.x);
		printf("y %f\t\tg %d\t\ty %f\t\ty %f\n", rt->object[n]->pos.y, rt->object[n]->color.green, rt->object[n]->axis.y, rt->object[n]->angle_n.y);
		printf("z %f\t\tb %d\t\tz %f\t\tz %f\n", rt->object[n]->pos.z, rt->object[n]->color.blue, rt->object[n]->axis.z, rt->object[n]->angle_n.z);
		printf("\n");
		n++;
	}
}
