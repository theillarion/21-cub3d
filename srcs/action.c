#include "cub3d.h"

void	ft_rotate(t_point *dir, t_point *plane, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = dir->x;
	old_plane_x = plane->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = old_dir_x * sin(speed) + dir->y * cos(speed);
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = old_plane_x * sin(speed) + plane->y * cos(speed);
}

void	ft_action_rotate(t_env *env)
{
	if (env->game.keycode == KeyLeft)
		ft_rotate(&env->game.dir, &env->game.plane,
			env->settings.speed_rotate);
	else if (env->game.keycode == KeyRight)
		ft_rotate(&env->game.dir, &env->game.plane,
			-env->settings.speed_rotate);
	else
		return ;
	env->game.keycode = 0;
}

void	ft_action_move(t_env *env)
{
	if (env->game.keycode == KeyUp)
	{
		if (!env->settings.map.ptr[(int)(env->game.pos.x + env->game.dir.x
				* env->settings.speed_move)][(int)env->game.pos.y])
			env->game.pos.x += env->game.dir.x * env->settings.speed_move;
		if (!env->settings.map.ptr[(int)env->game.pos.x][(int)(env->game.pos.y
			+ env->game.dir.y * env->settings.speed_move)])
			env->game.pos.y += env->game.dir.y * env->settings.speed_move;
	}
	else if (env->game.keycode == KeyDown)
	{
		if (!env->settings.map.ptr[(int)(env->game.pos.x - env->game.dir.x
				* env->settings.speed_move)][(int)env->game.pos.y])
			env->game.pos.x -= env->game.dir.x * env->settings.speed_move;
		if (!env->settings.map.ptr[(int)env->game.pos.x][(int)(env->game.pos.y
			- env->game.dir.y * env->settings.speed_move)])
			env->game.pos.y -= env->game.dir.y * env->settings.speed_move;
	}
	env->game.keycode = 0;
}
