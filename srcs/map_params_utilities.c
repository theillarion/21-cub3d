#include "cub3d.h"

int	set_path(char **path, char *string)
{
	int	len;

	len = 0;
	while (string[len])
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
	char	*r;
	char	*g;
	char	*b;

	len = 0;
	tmp = NULL;
	r = NULL;
	g = NULL;
	b = NULL;
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &r);
	if (check_zap(&tmp, &len, string_of_map, r))
		return (-1);
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &g);
	if (check_zap(&tmp, &len, string_of_map, g))
		return (-1);
	while (string_of_map[len] && ft_isdigit(string_of_map[len]))
		add_cdigit(string_of_map, &len, &tmp, &b);
	if (ft_atoi(b) > 255)
		return (-1);
	tmp = string_of_map + len;
	if (tmp)
		len += skip_ws(&tmp);
	if (string_of_map[len] != '\n')
		return (-1);
	*srgb = ft_srgb_create(0, ft_atoi(r), ft_atoi(g), ft_atoi(b));
	free(r);
	free(g);
	free(b);
	return (0);
}
