/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrhett <wrhett@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:45:43 by wrhett            #+#    #+#             */
/*   Updated: 2020/04/17 16:10:26 by wrhett           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lenchr(char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\n')
		index += 1;
	return (index);
}

static char		*get_next_line_read(const int fd, char *str)
{
	char		bufer[BUFF_SIZE + 1];
	char		*tmp;
	ssize_t		ret;

	if (str == NULL)
		str = ft_strnew(0);
	while (ft_strchr(str, '\n') == NULL)
	{
		ret = read(fd, bufer, BUFF_SIZE);
		if (ret == 0)
			return (str);
		if (ret == -1)
			return (NULL);
		bufer[ret] = '\0';
		tmp = ft_strjoin(str, bufer);
		ft_strdel(&str);
		str = tmp;
	}
	return (str);
}

static t_fd		*lst_create(char *str, int fd)
{
	t_fd *newlist;

	newlist = (t_fd *)malloc(sizeof(t_fd));
	if (newlist == NULL)
		return (NULL);
	if (str == NULL)
		newlist->str = NULL;
	newlist->discriptor = fd;
	newlist->next = NULL;
	return (newlist);
}

static t_fd		*lst_search_create(t_fd *fd_open, int fd)
{
	t_fd *cursor;

	cursor = fd_open;
	while (cursor->next != NULL)
	{
		if (cursor->discriptor == fd)
			return (cursor);
		cursor = cursor->next;
	}
	if (cursor->next == NULL && cursor->discriptor != fd)
	{
		cursor->next = lst_create(NULL, fd);
		cursor = cursor->next;
	}
	return (cursor);
}

int				get_next_line_list(const int fd, char **line)
{
	static t_fd	*fd_open;
	t_fd		*fd_tmp;
	char		*str;

	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	if (fd_open == NULL)
		fd_open = lst_create(NULL, fd);
	fd_tmp = (fd_open == NULL) ? fd_open : lst_search_create(fd_open, fd);
	if ((str = get_next_line_read(fd, fd_tmp->str)) == NULL)
		return (-1);
	if (ft_strchr(str, '\n') != NULL)
	{
		*line = ft_strsub(str, 0, ft_lenchr(str));
		fd_tmp->str = ft_strdup(ft_strchr(str, '\n') + 1);
		ft_strdel(&str);
		return (1);
	}
	if (*str != '\0')
	{
		*line = str;
		fd_tmp->str = ft_strnew(0);
		return (1);
	}
	return (0);
}
