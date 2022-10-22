#include "cub3d.h"

#define POS_X 22
#define POS_Y 12

extern int temp_map[MAP_WIDTH][MAP_HEIGHT];

// TEMP FILL ALL SETTINGS FROM FILE
bool ft_temp_fill_settings(t_setting	*settings)
{
	int i;
	int width;
	int height;
	if (settings == NULL)
		return (false);
	settings->speed_move = SPEED_MOVE;
	settings->speed_rotate = SPEED_ROTATE;
	ft_set_point(&settings->position, POS_X, POS_Y);
	settings->direction = NORTH;
	settings->floor = ft_srgb_create(0x0, 0xAB, 0x9F, 0x00);
	settings->ceilling = ft_srgb_create(0x0, 0x0, 0x73, 0xBF);
	settings->paths[TEX_NORTH] = ft_strdup("textures/greystone.xpm");
	settings->paths[TEX_EAST] = ft_strdup("textures/bluestone.xpm");
	settings->paths[TEX_SOUTH] = ft_strdup("textures/redbrick.xpm");
	settings->paths[TEX_WEST] = ft_strdup("textures/colorstone.xpm");
	width = MAP_WIDTH;
	height = MAP_HEIGHT;
	settings->map = (int **)malloc(height * sizeof(*settings->map));
	i = -1;
	while (++i < height)
	{
		settings->map[i] = (int *)malloc(width * sizeof(**settings->map));
		ft_memcpy((void *)settings->map[i], (void *)temp_map[i], width * sizeof(**settings->map));
	}
	return (true);
}

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
