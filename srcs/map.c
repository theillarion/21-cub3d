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

#include "../includes/cub3d.h"

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

int	check_map_symbol(char sym)
{
	// todo space check with ft_ispace?
	if (sym == '0' || sym == '1' || sym == 'N' || sym == 'S' || sym == 'E' || sym == 'W' || sym == ' ' || sym == '\n' || sym == '\0')
		return (0);
	return (-1);
}

char	*ft_strjoin_mem(char *s1, char *s2)
{
	char	*temp_s1;
	char	*temp_s2;
	char	*res;

	temp_s1 = s1;
	temp_s2 = s2;
	res = ft_strjoin(s1, s2);
	if (temp_s1)
		free(temp_s1);
	if (temp_s2)
		free(temp_s2);
	return (res);
}

void	act_map_string(t_setting *g, const char *current_line)
{
	if (check_map_symbol(*(current_line - 1)))
		ft_raise_error("Wrong map!");
	if (*(current_line - 1) == '\n')
		(*g).map.height += 1;
}

int	calc_map_width_height(t_setting *g, char *mapline)
{
	int	current_width;
	int	last_width;
	int height;

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

void	check_map_closed(t_setting *g, char *mapline)
{
	int	i;
	int	current_ln;

	if ((*g).map.height < 3)
		ft_raise_error("Wrong map!");
	i = -1;
	current_ln = 0;
	while (mapline[++i])
	{
		if (current_ln == 0 && mapline[i] != '\n' && mapline[i] != '1')
			ft_raise_error("Wrong map!");
		if (current_ln == (*g).map.height && mapline[i] != '\n'
			&& mapline[i] != '1')
			ft_raise_error("Wrong map!");
		if (mapline[i] == '\n')
		{
			if (i > 0 && mapline[i - 1] != '1')
				ft_raise_error("Wrong map!");
			if (mapline[i + 1] != '1' && mapline[i + 1] != '\0')
				ft_raise_error("Wrong map!");
			current_ln++;
		}
	}
}

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ');
}

int skip_ws(char **str)
{
	int skipped;

	skipped = 0;
	while (ft_isspace(**str) && **str != '\n')
	{
		(*str)++;
		skipped++;
	}
	return (skipped);
}

void	go_to_sym(const char *string, int *skip, char s)
{
	int found_q;

	found_q = 0;
	while (string[*skip] && string[*skip] != s)
	{
		(*skip)++;
		if (string[*skip] == s)
		{
			found_q = 1;
			if ((string[*skip] + 1) != '\n')
				*skip = -1;
		}
	};
	if (! found_q)
		*skip = -1;
	(*skip)++;
}

int set_path(char **path, char *string)
{
	int	len;

	len = 0;
	while(string[len])
	{
		if (ft_isspace(string[len])
			&& string[len] != '\n' && string[len + 1] != '\n')
			return (-1);
		if (string[len] == '"')
			go_to_sym(string, &len, '"');
		else if (len != -1 && string[len] == '\'')
			go_to_sym(string, &len, '\'');
		if (len == -1)
			return (-1);
		if (string[len] == '\n')
			break ;
		len++;
	}
	if (! len)
		return (-1);
	*path = ft_substr(string, 0, len);
	return (0);
}

int set_rgb(t_srgb *srgb, char *string_of_map)
{
	int	len;
	char *tmp;
	char *r;
	char *g;
	char *b;

	len = 0;
	tmp = NULL;
	r = NULL;
	g = NULL;
	b = NULL;
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
	{
		tmp = ft_substr(string_of_map, len, 1);
		r = ft_strjoin_with_free(r, tmp, 1, 1);
		len++;
	}
	if (ft_atoi(r) > 255)
		return (-1);
	if (tmp)
	{
		len += skip_ws(&tmp);
		if (string_of_map[len] != ',')
			return (-1);
		else
			len++;
	}
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
	{
		tmp = ft_substr(string_of_map, len, 1);
		g = ft_strjoin_with_free(g, tmp, 1, 1);
		len++;
	}
	if (ft_atoi(g) > 255)
		return (-1);
	tmp = string_of_map + len;
	if (tmp)
	{
		len += skip_ws(&tmp);
		if (string_of_map[len] != ',')
			return (-1);
		else
			len++;
	}
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
	{
		tmp = ft_substr(string_of_map, len, 1);
		b = ft_strjoin_with_free(b, tmp, 1, 1);
		len++;
	}
	if (ft_atoi(b) > 255)
		return (-1);
	tmp = string_of_map + len;
	if (tmp)
		len += skip_ws(&tmp);
	if (string_of_map[len] != '\n')
		return -1;
	*srgb = ft_srgb_create(0, ft_atoi(r), ft_atoi(g), ft_atoi(b));
	return (0);
}

int fill_params(t_setting *g, char *string_of_map)
{
	skip_ws(&string_of_map);
	if (! ft_strncmp(string_of_map, "NO", 2))
	{
		string_of_map += 2;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_path(&g->paths[TEX_NORTH], string_of_map) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "SO", 2))
	{
		string_of_map += 2;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_path(&g->paths[TEX_SOUTH], string_of_map) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "WE", 2))
	{
		string_of_map += 2;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_path(&g->paths[TEX_WEST], string_of_map) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "EA", 2))
	{
		string_of_map += 2;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_path(&g->paths[TEX_EAST], string_of_map) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "F", 1))
	{
		string_of_map += 1;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_rgb(&(g->floor), string_of_map) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "C", 1))
	{
		string_of_map += 1;
		if (! skip_ws(&string_of_map))
			return (-1);
		if (set_rgb(&(g->ceilling), string_of_map) == -1)
			return (-1);
	}
	return (0);
}

void	check_all_params_filled(t_setting *g, int *params_filled)
{
	int params_filled_local;

	params_filled_local = 1;
	if (! g->paths[TEX_EAST] || ! g->paths[TEX_WEST]
		|| ! g->paths[TEX_SOUTH] || ! g->paths[TEX_NORTH])
		params_filled_local = 0;
	if (params_filled_local
		&& (! g->ceilling.data || ! g->floor.data))
		params_filled_local = 0;
	*params_filled = params_filled_local;
}

void	read_map_file(t_setting *g, int map_fd)
{
	char	*map_line;
	char	*current_line;
	int 	params_filled;
	int 	**map;
	int 	map_row;
	int 	map_col;

	current_line = get_next_line(map_fd);
	params_filled = 0;
	map_line = NULL;
	while (current_line)
	{
		check_all_params_filled(g, &params_filled);
		if (params_filled)
			map_line = ft_strjoin_with_free(map_line, current_line, 0, 1);
		else
		{
			if (fill_params(g, current_line) == -1)
				ft_raise_error("wrong map");
		}
		current_line = get_next_line(map_fd);
	}
	if (! params_filled)
		ft_raise_error("wrong map");
	current_line = map_line;
	while (current_line && *current_line == '\n')
		current_line++;
	if (*current_line == '\0')
		ft_raise_error("wrong map");
	calc_map_width_height(g, current_line);
	map = malloc(sizeof(int *) * (g->map.height));
	map_row = -1;
	while (++map_row < (g->map.height))
	{
		map[map_row] = malloc(sizeof(int) * (g->map.width ));
		map_col = -1;
		while (++map_col < (g->map.width + 1))
			map[map_row][map_col] = -1;
	}
	map_row = 1;
	while (current_line && *current_line)
	{
		++map_row;
		map_col = 1;
		while (current_line && *current_line && *current_line != '\n')
		{
			if (*current_line == '0' || *current_line == '1' )
				map[map_row][++map_col] = (int) *current_line - 48;
			else if (*current_line == ' ')
				map[map_row][++map_col] = -1;
			else if (*current_line == 'N' || *current_line == 'S' || *current_line == 'W' || *current_line == 'E')
			{
				// todo add checking for character already in map
				if (g->position.x || g->position.y)
					ft_raise_error("wrong map");
				map[map_row][++map_col] = 0;
				g->position.x = map_row;
				g->position.y = map_col;
				if (*current_line == 'N')
					g->direction = NORTH;
				else if (*current_line == 'S')
					g->direction = SOUTH;
				else if (*current_line == 'W')
					g->direction = WEST;
				else if (*current_line == 'E')
					g->direction = EAST;
			}
			else
				ft_raise_error("wrong map");
			current_line++;
		}
		current_line++;
	}
	map_row = 0;
	while (++map_row < (g->map.height))
	{
		map_col = 0;
		while (++map_col < (g->map.width))
		{
			printf("%2d", map[map_row][map_col]);
			if (map[map_row][map_col] == 0)
			{
				if (map[map_row - 1][map_col - 1] == -1)
					ft_raise_error("wrong map");
				if (map[map_row - 1][map_col] == -1)
					ft_raise_error("wrong map");
				if (map[map_row - 1][map_col + 1] == -1)
					ft_raise_error("wrong map");
				if (map[map_row][map_col - 1] == -1)
					ft_raise_error("wrong map");
				if (map[map_row][map_col + 1] == -1)
					ft_raise_error("wrong map");
				if (map[map_row + 1][map_col - 1] == -1)
					ft_raise_error("wrong map");
				if (map[map_row + 1][map_col] == -1)
					ft_raise_error("wrong map");
				if (map[map_row + 1][map_col + 1] == -1)
					ft_raise_error("wrong map");
			}
		}
		printf("\n");
	}
	g->map.ptr = map;

//	while (current_line++ && *current_line)
//		act_map_string(g, current_line);
//	check_map_closed(g, map_line);
//	return (map_line);
}

void	read_map(char *map_path, t_setting *g)
{
//	char	**map;
	//char	*map_line;
	int		map_fd;

	//map_line = malloc(sizeof(char));
//	if (!map_line)
//		ft_raise_error(0);
//	*map_line = '\0';
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		ft_raise_error(map_path);
	read_map_file(g, map_fd);
	//map = ft_split(map_line, '\n');
	//(*g).map.height += 1;
//	if (map_line)
//		free(map_line);
//	return (map);
}
