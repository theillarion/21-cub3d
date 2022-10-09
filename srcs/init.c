#include "cub3d.h"

bool	ft_init(t_env *env)
{
	if (!env)
		return (false);
	ft_memset((void *)env, '\0', sizeof(*env));
	return (true);
}
