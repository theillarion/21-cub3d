#include "cub3d.h"

void	ft_success(t_env *env)
{
	ft_destroy(env);
	ft_putendl_fd("Game over\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_failure(t_env	*env, const char	*msg)
{
	ft_destroy(env);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_failure_errno(t_env	*env)
{
	ft_destroy(env);
	if (errno)
	{
		perror("Error");
		errno = 0;
	}
	exit(EXIT_FAILURE);
}
