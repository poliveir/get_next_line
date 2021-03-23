/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:38:59 by poliveir          #+#    #+#             */
/*   Updated: 2021/03/22 17:01:55 by poliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int
	nl_check(char **save, int fd, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while (save[fd][i] != '\n' && save[fd][i] != '\0')
		++i;
	if (save[fd][i] == '\n')
	{
		*line = ft_substr(save[fd], 0, i);
		temp = ft_strdup(save[fd] + i + 1);
		free(save[fd]);
		save[fd] = temp;
	}
	else
	{
		*line = ft_strdup(save[fd]);
		free(save[fd]);
		save[fd] = NULL;
		return (0);
	}
	return (1);
}

static int
	return_mng(int ret, int fd, char **save, char **line)
{
	if (ret == 0 && !save[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (ret < 0)
		return (-1);
	return (nl_check(save, fd, line));
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	*save[MAX_SPCFD_FD];
	char		*buf;
	char		*temp;

	buf = NULL;
	if (fd < 0 || fd >= MAX_SPCFD_FD || !line || BUFFER_SIZE <= 0
	|| read(fd, buf, 0) < 0 || !(buf = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!save[fd])
			save[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(save[fd], buf);
			free(save[fd]);
			save[fd] = temp;
		}
		if (ft_strchr(save[fd], '\n'))
			break ;
	}
	free(buf);
	return (return_mng(ret, fd, save, line));
}
