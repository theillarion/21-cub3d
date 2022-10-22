/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:02 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:14:03 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_event_key_press(int keycode, t_env	*env)
{
	if (env == NULL)
		return (EXIT_FAILURE);
	if (keycode == KeyLeft || keycode == KeyRight
		|| keycode == KeyUp || keycode == KeyDown)
		env->game.keycode = keycode;
	return (EXIT_SUCCESS);
}

int	ft_event_key_release(int keycode, t_env	*env)
{
	if (keycode == KeyEsc)
		ft_success(env);
	return (EXIT_SUCCESS);
}

int	ft_event_exit(t_env *env)
{
	ft_success(env);
	return (EXIT_SUCCESS);
}
