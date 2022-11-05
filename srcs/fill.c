/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:06 by illarion          #+#    #+#             */
/*   Updated: 2022/10/28 17:42:52 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	ft_fill_images(t_env	*env)
{
	int	i;

	i = 0;
	while (i < COUNT_TEXTURES)
	{
		env->images[i].data.img = mlx_xpm_file_to_image(env->mlx.ptr,
				env->settings.paths[i], &env->images[i].width,
				&env->images[i].height);
		if (!env->images[i].data.img || env->images[i].width <= 0
			|| env->images[i].height <= 0)
			return (false);
		ft_set_data_image(&env->images[i].data);
		ft_set_color_pixels(&env->images[i]);
		if (!env->images[i].data.addr || !env->images[i].pixels)
			return (false);
		++i;
	}
	return (true);
}

bool	ft_fill(t_env	*env)
{
	if (!env)
		return (false);
	if (!ft_create_mlx(&env->mlx))
		return (false);
	env->win.width = env->mlx.width / 2;
	env->win.height = env->mlx.height / 2;
	if (!ft_create_window(&env->mlx, &env->win, "Cub3D")
		|| !ft_fill_images(env))
		return (false);
	env->game.pos.x = env->settings.position.x;
	env->game.pos.y = env->settings.position.y;
	ft_set_point(&env->game.dir, DEFAULT_DIR_X, DEFAULT_DIR_Y);
	ft_set_point(&env->game.plane, DEFAULT_PLANE_X, DEFAULT_PLANE_Y);
	ft_rotate(&env->game.dir, &env->game.plane, env->settings.direction);
	return (true);
}
