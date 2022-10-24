/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:55:30 by ltowelie          #+#    #+#             */
/*   Updated: 2021/11/05 18:35:31 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*makestr_secure(char *s1, char *s2, int mode)
{
	char	*tmp;
	char	*res;

	tmp = s1;
	res = NULL;
	if (mode == 0)
		res = ft_strdup(s2);
	else if (mode == 1)
		res = ft_strjoin(s1, s2);
	free(tmp);
	return (res);
}

char	*make_line(char **remain, char **res, char **buf)
{
	char		*tmp;
	char		*n_pos;

	n_pos = ft_strchr(*buf, '\n');
	if (n_pos)
	{
		*n_pos = '\0';
		if (!*res)
			*res = ft_calloc(1, 1);
		*res = makestr_secure(*res, *buf, 1);
		*res = makestr_secure(*res, "\n", 1);
		tmp = *remain;
		if (ft_strlen(++n_pos))
			*remain = ft_strdup(n_pos);
		free(tmp);
		free(*buf);
	}
	else
	{
		if (!*res)
			*res = ft_calloc(1, 1);
		*res = makestr_secure(*res, *buf, 1);
		free(*buf);
	}
	return (n_pos);
}

char	*check_remain_new(char **remain, char **res)
{
	char	*n_pos;

	n_pos = NULL;
	*res = NULL;
	if (*remain)
	{
		n_pos = ft_strchr(*remain, '\n');
		if (n_pos)
		{
			*n_pos = '\0';
			*res = ft_strdup(*remain);
			*res = makestr_secure(*res, "\n", 1);
			*remain = makestr_secure(*remain, ++n_pos, 0);
		}
		else
		{
			if (ft_strlen(*remain))
				*res = ft_strdup(*remain);
			free(*remain);
			*remain = NULL;
		}
	}
	return (n_pos);
}

char	*read_file(int fd)
{
	char		*buf;
	int			read_count;

	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	read_count = read(fd, buf, BUFFER_SIZE);
	if (read_count <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[read_count] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*n_pos;
	char		*res;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n_pos = check_remain_new(&remain, &res);
	while (n_pos == NULL)
	{
		buf = read_file(fd);
		if (!buf)
			break ;
		n_pos = make_line(&remain, &res, &buf);
	}
	return (res);
}
