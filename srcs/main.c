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

	if (argc != 2)
		ft_failure(&env, "wrong number of arguments");
	ft_init(&env);
	read_scene(argv[1], &env.settings);
	env.settings.speed_move = SPEED_MOVE;
	env.settings.speed_rotate = SPEED_ROTATE;
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
