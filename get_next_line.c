/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:44:29 by chchin            #+#    #+#             */
/*   Updated: 2022/05/11 16:10:10 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static void	gnl_free(char **s)
{
	free(*s);
	*s = NULL;
}

static void	gnl_read(int fd, char *buf, char **str)
{
	int		numbytes;
	char	*tmp;

	numbytes = 1;
	while (numbytes)
	{
		numbytes = read(fd, buf, BUFFER_SIZE);
		if (numbytes < 1)
			break ;
		buf[numbytes] = '\0';
		if (!*str)
			*str = ft_strdup("");
		tmp = *str;
		*str = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	gnl_free(&buf);
}

static char	*gnl_return(char **str)
{
	size_t	offset;
	size_t	remainder;
	char	*line;
	char	*tmp;

	if (!*str)
		return (NULL);
	if (!ft_strchr(*str, '\n'))
	{
		line = ft_substr(*str, 0, ft_strlen(*str));
		gnl_free(str);
		return (line);
	}
	remainder = ft_strlen(ft_strchr(*str, '\n')) - 1;
	offset = ft_strlen(*str) - remainder;
	line = ft_substr(*str, 0, offset);
	tmp = *str;
	*str = ft_substr(ft_strchr(tmp, '\n'), 1, remainder);
	free(tmp);
	if ((*str)[0] == '\0')
		gnl_free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd == -1 || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	gnl_read(fd, buf, &str);
	return (gnl_return(&str));
}
