/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_params_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:55:03 by ltowelie          #+#    #+#             */
/*   Updated: 2022/10/20 12:55:04 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_ws_check_after(const char *string, char **tmp, int *len, int *skipped)
{
	if ((*len))
	{
		(*tmp) = (char *)string + (*len);
		(*skipped) = skip_ws((tmp));
		if ((*skipped))
		{
			(*len) += (*skipped);
			if (*(*tmp) != '\n')
			{
				(*len) = -1;
				return (-1);
			}
		}
	}
	return (0);
}

int	set_path(char **path, char *string)
{
	int		len;
	char	*tmp;
	int		skipped;

	len = 0;
	skipped = 0;
	while (string[len])
	{
		if (skip_ws_check_after(string, &tmp, &len, &skipped) == -1)
			break ;
		if ((len && (string[len] == '"' || string[len] == '\'')))
		{
			len = -1;
			break ;
		}
		if (handle_quotes(&string, &len))
			break ;
		if (len == -1 || string[len] == '\n')
			break ;
		len++;
	}
	if (! len || len == -1)
		return (-1);
	*path = ft_substr(string, 0, len - skipped);
	return (0);
}

void	add_cdigit(const char *string_of_map, int *len, char **tmp, char **r)
{
	(*tmp) = ft_substr(string_of_map, (*len), 1);
	(*r) = ft_strjoin_with_free((*r), (*tmp), 1, 1);
	(*len)++;
}

int	check_zap(char **tmp, int *len, char *string_of_map, char *col)
{
	*tmp = string_of_map + *len;
	if (ft_atoi(col) > 255)
		return (-1);
	if (*tmp)
	{
		*len += skip_ws(tmp);
		if (string_of_map[*len] != ',')
			return (-1);
		else
			(*len)++;
	}
	return (0);
}

int	set_rgb(t_srgb *srgb, char *string_of_map)
{
	int		len;
	char	*tmp;
	char	*c[3];

	initiate_color_params(&tmp, c, &len);
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &(*c));
	if (check_zap(&tmp, &len, string_of_map, c[0]))
		return (-1);
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &(*(c + 1)));
	if (check_zap(&tmp, &len, string_of_map, c[1]))
		return (-1);
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &(*(c + 2)));
	if (ft_atoi(c[2]) > 255)
		return (-1);
	tmp = string_of_map + len;
	if (tmp)
		len += skip_ws(&tmp);
	if (string_of_map[len] != '\n')
		return (-1);
	*srgb = ft_srgb_create(0, ft_atoi(c[0]), ft_atoi(c[1]), ft_atoi(c[2]));
	free_colors(c);
	return (0);
}
