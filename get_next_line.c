/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:38:59 by poliveir          #+#    #+#             */
/*   Updated: 2021/03/22 22:24:31 by poliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int
	nl_check(char **save, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*save)[i] != '\n' && (*save)[i] != '\0')
		++i;
	if ((*save)[i] == '\n')
	{
		*line = ft_substr(*save, 0, i);
		temp = ft_strdup(*save + i + 1);
		free(*save);
		*save = temp;
	}
	else
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (0);
	}
	return (1);
}

static int
	return_mng(int ret, char **save, char **line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && !(*save))
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (nl_check(save, line));
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	static char	*save;
	char		*buf;
	char		*temp;

	buf = NULL;
	if (fd < 0 || fd >= MAX_SPCFD_FD || !line || BUFFER_SIZE <= 0
	|| read(fd, buf, 0) < 0 || !(buf = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!save)
			save = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(save, buf);
			free(save);
			save = temp;
		}
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buf);
	return (return_mng(ret, &save, line));
}
