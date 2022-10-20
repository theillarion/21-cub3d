/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltowelie <ltowelie@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:55:08 by ltowelie          #+#    #+#             */
/*   Updated: 2022/10/20 12:55:09 by ltowelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	skip_ws(char **str)
{
	int	skipped;

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
	int		found_q;
	char	*tmp;

	found_q = 0;
	while (string[*skip])
	{
		if (string[*skip] == s)
		{
			found_q = 1;
			tmp = (char *)string + *skip + 1;
			skip_ws(&tmp);
			if (*(tmp) != '\n')
			{
				*skip = -1;
				break ;
			}
			break ;
		}
		(*skip)++;
	}
	if (! found_q)
		*skip = -1;
}

int	handle_quotes(char **string, int *len)
{
	int	quotes_was;

	quotes_was = 0;
	if ((*string)[(*len)] == '"')
	{
		(*len)++;
		(*string)++;
		go_to_sym((*string), len, '"');
		quotes_was = 1;
	}
	else if ((*len) != -1 && (*string)[(*len)] == '\'')
	{
		(*len)++;
		(*string)++;
		go_to_sym((*string), len, '\'');
		quotes_was = 1;
	}
	return (quotes_was);
}
