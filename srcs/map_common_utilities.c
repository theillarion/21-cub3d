/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_common_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:54:56 by ltowelie          #+#    #+#             */
/*   Updated: 2022/10/22 17:26:32 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_raise_error(char *str)
{
	if (errno)
		perror(str);
	else
	{
		ft_putendl_fd("Error", 2);
		if (str)
			ft_putendl_fd(str, 2);
	}
	exit(EXIT_FAILURE);
}

void	map_error(void)
{
	ft_raise_error("wrong map");
}

char	*ft_strjoin_with_free(char *str1, char *str2, int free_1, int free_2)
{
	char	*result;

	if (! str1 && ! str2)
		return (NULL);
	else if (!str1)
		result = ft_strdup(str2);
	else if (!str2)
		result = ft_strdup(str1);
	else
		result = ft_strjoin(str1, str2);
	if (str1 && free_1)
	{
		free(str1);
		str1 = NULL;
	}
	if (str2 && free_2)
	{
		free(str2);
		str2 = NULL;
	}
	return (result);
}

void	*free_allocated(int **map, int map_row)
{
	int	i;

	i = -1;
	while (++i < map_row)
		free(map[i]);
	free(map);
	return (NULL);
}

int	**allocate_map(const t_setting *g)
{
	int	map_row;
	int	map_col;
	int	**map;

	map = malloc(sizeof(int *) * (g->map_height + 1));
	if (! map)
		return (NULL);
	map_row = -1;
	while (++map_row < (g->map_height))
	{
		map[map_row] = malloc(sizeof(int) * (g->map_width));
		if (! map[map_row])
			return (free_allocated(map, map_row));
		map_col = -1;
		while (++map_col < (g->map_width))
			map[map_row][map_col] = -1;
	}
	map[map_row] = NULL;
	return (map);
}
