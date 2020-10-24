
#include "rtv1.h"

int		count_spaces(char *str)
{
	int n;
	int i;

	n = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
			n++;
		i++;
	}
	return (n);
}
