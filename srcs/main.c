/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:10 by illarion          #+#    #+#             */
/*   Updated: 2022/10/22 20:19:28 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char	**argv)
{
	t_env	env;

	(void)argc;
	(void)argv;
	ft_init(&env);
	if (!ft_temp_fill_settings(&env.settings))
		ft_failure(&env, "temp filling settings");
	if (!ft_fill(&env))
		ft_failure(&env, "filling");
	mlx_hook(env.win.ptr, KeyPress,
		KeyPressMask, &ft_event_key_press, (void *)&env);
	mlx_hook(env.win.ptr, KeyRelease,
		KeyReleaseMask, &ft_event_key_release, (void *)&env);
	mlx_hook(env.win.ptr, DestroyNotify,
		ButtonReleaseMask, &ft_event_exit, (void *)&env);
	mlx_loop_hook(env.mlx.ptr, &ft_render_next_frame, (void *)&env);
	mlx_loop(env.mlx.ptr);
	return (0);
}
