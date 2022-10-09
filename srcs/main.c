#include "cub3d.h"

#define POS_X 22
#define POS_Y 12

extern int temp_map[MAP_WIDTH][MAP_HEIGHT];

// TEMP FILL ALL SETTINGS FROM FILE
bool ft_temp_fill_settings(t_setting	*settings)
{
	int i;

	if (settings == NULL)
		return (false);
	settings->speed_move = SPEED_MOVE;
	settings->speed_rotate = SPEED_ROTATE;
	settings->position.x = POS_X;
	settings->position.y = POS_Y;
	settings->direction = NORTH;
	settings->floor = ft_srgb_create(0x0, 0xAB, 0x9F, 0x00);
	settings->ceilling = ft_srgb_create(0x0, 0x0, 0x73, 0xBF);
	settings->paths[TEX_NORTH] = ft_strdup("textures/greystone.xpm");
	settings->paths[TEX_EAST] = ft_strdup("textures/bluestone.xpm");
	settings->paths[TEX_SOUTH] = ft_strdup("textures/redbrick.xpm");
	settings->paths[TEX_WEST] = ft_strdup("textures/colorstone.xpm");
	settings->map.width = MAP_WIDTH;
	settings->map.height = MAP_HEIGHT;
	settings->map.ptr = (int **)malloc(settings->map.height * sizeof(*settings->map.ptr));
	i = -1;
	while (++i < settings->map.height)
	{
		settings->map.ptr[i] = (int *)malloc(settings->map.width * sizeof(**settings->map.ptr));
		ft_memcpy((void *)settings->map.ptr[i], (void *)temp_map[i], settings->map.width * sizeof(**settings->map.ptr));
	}
	return (true);
}

int	main(int argc, char	**argv)
{
	t_env	env;

	(void)argc;
	(void)argv;
	ft_init(&env);
	if (!ft_temp_fill_settings(&env.settings) || !ft_fill(&env))
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
