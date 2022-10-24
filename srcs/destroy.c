/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:26:16 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:54:05 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef CURRENT_OS_LINUX

static void	ft_destroy_display(void	**ptr)
{
	mlx_destroy_display(*ptr);
	*ptr = NULL;
}
#else

static void	ft_destroy_display(void	**ptr)
{
	(void)ptr;
}
#endif

static void	ft_destroy_images(t_env	*env)
{
	int	i;

	if (!env)
		return ;
	i = -1;
	while (++i < COUNT_TEXTURES)
	{
		mlx_destroy_image(env->mlx.ptr, env->images[i].data.img);
		ft_foreach((void **)env->images[i].pixels, &free);
		ft_smart_free((void **)&env->images[i].pixels);
	}
}

static void	ft_destroy_paths(t_setting	*settings)
{
	int	i;

	i = -1;
	while (++i < COUNT_TEXTURES)
		ft_smart_free((void **)&settings->paths[i]);
}

void	ft_destroy(t_env	*env)
{
	if (!env || !env->mlx.ptr)
		return ;
	ft_destroy_images(env);
	ft_foreach((void **)env->win.canvas.pixels, &free);
	ft_smart_free((void **)&env->win.canvas.pixels);
	ft_foreach((void **)env->settings.map, &free);
	ft_smart_free((void **)&env->settings.map);
	ft_destroy_paths(&env->settings);
	if (env->win.canvas.data.img)
		mlx_destroy_image(env->mlx.ptr, env->win.canvas.data.img);
	if (env->win.ptr)
		mlx_destroy_window(env->mlx.ptr, env->win.ptr);
	ft_destroy_display(&env->mlx.ptr);
}
