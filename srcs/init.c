/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:28:17 by illarion          #+#    #+#             */
/*   Updated: 2022/10/24 12:57:08 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_init(t_env *env)
{
	if (!env)
		return (false);
	ft_memset((void *)env, '\0', sizeof(*env));
	env->settings.ceilling.data = -1;
	env->settings.floor.data = -1;
	env->settings.position.x += 0.5;
	env->settings.position.y += 0.5;
	env->settings.speed_move = SPEED_MOVE;
	env->settings.speed_rotate = SPEED_ROTATE;
	return (true);
}
