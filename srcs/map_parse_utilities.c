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
	int	found_q;

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
	}
	if (! found_q)
		*skip = -1;
	(*skip)++;
}
