#include "cub3d.h"

int	check_fill_path(t_setting *g, int *p_fld, char **s, enum e_textures tex)
{
	*p_fld = 1;
	*s += 2;
	if (! skip_ws(s))
		return (-1);
	if (set_path(&(g->paths[tex]), *s) == -1)
		return (-1);
	return (0);
}

int	fill_params_path(t_setting *g, char *string_of_map)
{
	int	param_filled;

	param_filled = 0;
	if (! ft_strncmp(string_of_map, "NO", 2))
	{
		if (check_fill_path(g, &param_filled, &string_of_map, TEX_NORTH) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "SO", 2))
	{
		if (check_fill_path(g, &param_filled, &string_of_map, TEX_SOUTH) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "WE", 2))
	{
		if (check_fill_path(g, &param_filled, &string_of_map, TEX_WEST) == -1)
			return (-1);
	}
	else if (! ft_strncmp(string_of_map, "EA", 2))
	{
		if (check_fill_path(g, &param_filled, &string_of_map, TEX_EAST) == -1)
			return (-1);
	}
	return (param_filled);
}

int	fill_params_srgb(t_setting *g, char *string_of_map)
{
	if (! ft_strncmp(string_of_map, "F", 1))
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

int	fill_params(t_setting *g, char *str_of_map)
{
	int	param_filled;

	param_filled = 0;
	skip_ws(&str_of_map);
	param_filled = fill_params_path(g, str_of_map);
	if (param_filled == -1)
		return (-1);
	else if (!param_filled
		&& (!ft_strncmp(str_of_map, "F", 1) || !ft_strncmp(str_of_map, "C", 1)))
		param_filled = fill_params_srgb(g, str_of_map);
	if (param_filled == -1)
		return (-1);
	return (0);
}

void	check_all_params_filled(t_setting *g, int *params_filled)
{
	int	params_filled_local;

	params_filled_local = 1;
	if (! g->paths[TEX_EAST] || ! g->paths[TEX_WEST]
		|| ! g->paths[TEX_SOUTH] || ! g->paths[TEX_NORTH])
		params_filled_local = 0;
	if (params_filled_local
		&& (! g->ceilling.data || ! g->floor.data))
		params_filled_local = 0;
	*params_filled = params_filled_local;
}
