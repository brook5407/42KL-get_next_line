/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:57:44 by chchin            #+#    #+#             */
/*   Updated: 2022/05/11 16:18:25 by chchin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static void	gnl_free(char **s)
{
	free(*s);
	*s = NULL;
}

static void	gnl_read(int fd, char *buf, char **str)
{
	int		numbytes;
	char	*tmp;

	if (!str[fd] || !ft_strchr(str[fd], '\n'))
	{
		numbytes = 1;
		while (numbytes)
		{
			numbytes = read(fd, buf, BUFFER_SIZE);
			if (numbytes < 1)
				break ;
			buf[numbytes] = '\0';
			if (!str[fd])
				str[fd] = ft_strdup("");
			tmp = str[fd];
			str[fd] = ft_strjoin(tmp, buf);
			free(tmp);
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	free(buf);
}

static char	*gnl_return(int fd, char **str)
{
	int		offset;
	int		remainder;
	char	*line;
	char	*tmp;

	if (!str[fd])
		return (NULL);
	if (!ft_strchr(str[fd], '\n'))
	{
		line = ft_substr(str[fd], 0, ft_strlen(str[fd]));
		gnl_free(&str[fd]);
		return (line);
	}
	remainder = ft_strlen(ft_strchr(str[fd], '\n')) - 1;
	offset = ft_strlen(str[fd]) - remainder;
	line = ft_substr(str[fd], 0, offset);
	tmp = str[fd];
	str[fd] = ft_substr(ft_strchr(tmp, '\n'), 1, remainder);
	free(tmp);
	if (str[fd][0] == '\0')
		gnl_free(&str[fd]);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str[OPEN_MAX + 1];

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (fd == -1 || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	gnl_read(fd, buf, str);
	return (gnl_return(fd, str));
}
