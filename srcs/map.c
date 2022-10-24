/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 12:25:30 by ltowelie          #+#    #+#             */
/*   Updated: 2022/03/10 12:25:31 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_param_and_map(t_setting *g, int fd, char **map_line, int *p_filled)
{
	char	*current_line;

	current_line = get_next_line(fd);
	*p_filled = 0;
	*map_line = NULL;
	while (current_line)
	{
		check_all_params_filled(g, p_filled);
		if (*p_filled)
			*map_line = ft_strjoin_with_free(*map_line, current_line, 1, 1);
		else
		{
			if (fill_params(g, current_line) == -1)
				map_error();
			free(current_line);
		}
		current_line = get_next_line(fd);
	}
}

void	character_is_on_scene(t_setting *g)
{
	if (! g->position.x && ! g->position.y)
		map_error();
}

void	read_scene_file(t_setting *g, int map_fd)
{
	char	*map_line;
	char	*map_line_bkp;
	int		params_filled;
	int		**map;

	read_param_and_map(g, map_fd, &map_line, &params_filled);
	if (! params_filled)
		map_error();
	map_line_bkp = map_line;
	while (map_line && *map_line == '\n')
		map_line++;
	if (*map_line == '\0')
		map_error();
	calc_map_width_height(g, map_line);
	map = allocate_map(g);
	if (! map)
		ft_raise_error("malloc error");
	fill_map(g, map_line, map);
	free(map_line_bkp);
	map_is_closed(g, map);
	character_is_on_scene(g);
	g->map = map;
}

void	read_scene(char *map_path, t_setting *g)
{
	int		map_fd;
	size_t	map_len;
	char	*ext;

	map_len = ft_strlen(map_path);
	ext = ft_substr(map_path, map_len - 4, map_len);
	if (! ext)
		ft_raise_error("wrong filename");
	if (ft_strncmp(ext, ".cub", 3))
	{
		free(ext);
		ft_raise_error("wrong file extension");
	}
	free(ext);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		map_error();
	read_scene_file(g, map_fd);
}
