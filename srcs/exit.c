/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:04 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:14:05 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_success(t_env *env)
{
	ft_destroy(env);
	ft_putendl_fd("Game over", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_failure(t_env	*env, const char	*msg)
{
	ft_destroy(env);
	ft_putstr_fd("Error: ", STDERR_FILENO);
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
