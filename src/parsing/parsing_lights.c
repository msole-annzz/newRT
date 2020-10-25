
#include "rtv1.h"

int		move(char *str, int *index, int counter)
{
	if (str[*index] == ',')
		*index = *index + 1;
	if (str[*index] == '{')
		*index = *index + 1;
	counter++;
	return (counter);
}

int		move_type(char *str, int *index, int counter)
{
	if (str[*index] == '}')
		*index = *index + 3;
	else if (str[*index] == ',')
		*index = *index + 1;
	counter++;
	return (counter);
}

int		find_option(char *str, int *index, int counter, t_rtv *rt)
{
	if ((find_quotes(str, index, "\"type\"\0")))
	{
		rt->lights[rt->current_light]->type = parsing_type(str, index);
		counter = move_type(str, index, counter);
	//	printf("l1 %d\n", rt->lights[rt->current_light]->type);
	}
	else if (find_quotes(str, index, "\"position\"\0"))
	{
		rt->lights[rt->current_light]->pos = \
		parsing_coordinates(str, index);
		counter = move(str, index, counter);
	}
	else if (find_quotes(str, index, "\"direction\"\0"))
	{
		rt->lights[rt->current_light]->direction = \
		parsing_coordinates(str, index);
		counter = move(str, index, counter);

	}
	else if (find_quotes(str, index, "\"intensity\"\0"))
	{
		intensity_parsing(str, index, rt, rt->current_light);
		counter++;
		//printf("l1-1 %d\n", rt->lights[rt->current_light]->type);
	}
	else if (find_quotes(str, index, "\"color\"\0"))
	{
		rt->lights[rt->current_light]->color = parsing_color(str, index);
		//intensity_parsing(str, index, rt, rt->current_light);
		counter++;
		//*index= *index +1;
		// printf("str- %c\n", str[*index]);
		// printf("str- %c\n", str[*index + 1]);
		// printf("str- %c\n", str[*index + 2]);
		// printf("str- %c\n", str[*index + 3]);
		// printf("str- %c\n", str[*index + 4]);
	}
	else
	{
	//	printf ("error");
		file_contents_error();
	}
	// printf("counter - %d\n", counter);
	return (counter);
}

void	lights_parsing(char *str, int *index, t_rtv *rt)
{
	int n;
	int i;
	int counter;

	n = *index;
	i = *index;
	counter = 0;
	malloc_lightes(str, index, rt);
	*index = n + 2;
	n = 0;
	while (n < rt->n_lights)
	{
		rt->current_light = n;
		if ((counter == 0) && (n > 0))
		{
			*index = *index + 1;
		}
		counter = find_option(str, index, counter, rt);
		if (counter == 5)
		{
			n++;
			counter = 0;
		}
	}
}
