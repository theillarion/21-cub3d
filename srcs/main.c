#include "cub3d.h"

int	main(int argc, char	**argv)
{
	t_env	env;

	if (argc != 2)
	{
		printf("Error: wrong number of arguments\n");
		return (EXIT_FAILURE);
	}
	ft_init(&env);
	read_scene(argv[1], &env.settings);
	env.settings.speed_move = SPEED_MOVE;
	env.settings.speed_rotate = SPEED_ROTATE;
	if (!ft_fill(&env))
	{
		printf("Filling error\n");
		ft_success(&env);
	}
	mlx_hook(env.win.ptr, KeyPress,
		KeyPressMask, ft_event_key_press, (void *)&env);
	mlx_hook(env.win.ptr, KeyRelease,
		KeyReleaseMask, ft_event_key_release, NULL);
	mlx_hook(env.win.ptr, DestroyNotify,
		ButtonReleaseMask, ft_success, NULL);
	mlx_loop_hook(env.mlx.ptr, &ft_render_next_frame, (void *)&env);
	mlx_loop(env.mlx.ptr);
	return (0);
}
