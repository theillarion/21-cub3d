/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:55:11 by ltowelie          #+#    #+#             */
/*   Updated: 2022/10/20 12:55:12 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_direction(t_setting *g, const char *map_line)
{
	if (*map_line == 'N')
		g->direction = NORTH;
	else if (*map_line == 'S')
		g->direction = SOUTH;
	else if (*map_line == 'W')
		g->direction = WEST;
	else if (*map_line == 'E')
		g->direction = EAST;
}

void	set_position(t_setting *g, int **map, int *map_row, int *map_col)
{
	if (g->position.x || g->position.y)
		map_error();
	map[*map_row][++(*map_col)] = 0;
	g->position.x = *map_row;
	g->position.y = *map_col;
}

int	calc_map_width_height(t_setting *g, char *mapline)
{
	int	current_width;
	int	last_width;
	int	height;

	current_width = -1;
	last_width = -1;
	height = 0;
	while (mapline && *mapline)
	{
		current_width += 1;
		if (*mapline == '\n')
		{
			if (current_width > last_width)
				last_width = current_width;
			current_width = 0;
			height++;
		}
		mapline++;
	}
	errno = 0;
	if (last_width == -1)
		ft_raise_error("Empty map!");
	(*g).map.height = height + 4;
	(*g).map.width = last_width + 2;
	return (0);
}

void	fill_map(t_setting *g, char *ml, int **map)
{
	int	map_row;
	int	map_col;

	map_row = 1;
	while (ml && *ml && ++map_row)
	{
		map_col = 1;
		while (ml && *ml && *ml != '\n')
		{
			if (*ml == '0' || *ml == '1' )
				map[map_row][++map_col] = (int) *ml - 48;
			else if (*ml == ' ')
				map[map_row][++map_col] = -1;
			else if (*ml == 'N' || *ml == 'S' || *ml == 'W' || *ml == 'E')
			{
				set_position(g, map, &map_row, &map_col);
				set_direction(g, ml);
			}
			else
				map_error();
			ml++;
		}
		if (ml && *ml)
			ml++;
	}
}

void	map_is_closed(t_setting *g, int *const *m)
{
	int	r;
	int	c;

	r = 0;
	while (++r < (g->map.height))
	{
		c = 0;
		while (++c < (g->map.width))
		{
			printf("%2d", m[r][c]);
			if (m[r][c] == 0)
			{
				if (m[r - 1][c - 1] == -1 || m[r - 1][c] == -1
					|| m[r - 1][c + 1] == -1)
					map_error();
				if (m[r][c - 1] == -1 || m[r][c + 1] == -1)
					map_error();
				if (m[r + 1][c - 1] == -1 || m[r + 1][c] == -1
					|| m[r + 1][c + 1] == -1)
					map_error();
			}
		}
		printf("\n");
	}
}
