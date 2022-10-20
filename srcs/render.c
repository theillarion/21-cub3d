#include "cub3d.h"

static void	ft_calc_line(t_game *game, t_window *win)
{
	game->line_height = (int)(win->height / game->perp_wall_dist);
	game->start_y = -game->line_height / 2 + win->height / 2;
	if (game->start_y < 0 || game->start_y >= win->height)
		game->start_y = 0;
	game->end_y = game->line_height / 2 + win->height / 2;
	if (game->end_y < 0 || game->end_y >= win->height)
		game->end_y = win->height - 1;
}

static void	ft_select_texture(t_game *game)
{
	if (game->side == false && game->step.x == -1)
		game->curr_tex = TEX_NORTH;
	if (game->side == false && game->step.x == 1)
		game->curr_tex = TEX_SOUTH;
	else if (game->side == true && game->step.y == -1)
		game->curr_tex = TEX_WEST;
	else if (game->side == true && game->step.y == 1)
		game->curr_tex = TEX_EAST;
}

static void	ft_pre_fill_canvas(t_game *game, const t_image *img)
{
	double		wall_x;

	if (game->side == 0)
		wall_x = game->pos.y + game->perp_wall_dist * game->ray_dir.y;
	else
		wall_x = game->pos.x + game->perp_wall_dist * game->ray_dir.x;
	wall_x -= floor(wall_x);
	game->tex.x = (int)(wall_x * (double)(img[game->curr_tex].width));
	if (game->side == 0 && game->ray_dir.x > 0)
		game->tex.x = img[game->curr_tex].width - game->tex.x - 1;
	if (game->side == 1 && game->ray_dir.y < 0)
		game->tex.x = img[game->curr_tex].width - game->tex.x - 1;
}

static void	ft_fill_canvas(t_env	*env, int x)
{
	double	step;
	int		y;

	ft_pre_fill_canvas(&env->game, env->images);
	step = 1.0 * (double)env->images[env->game.curr_tex].height
		/ (double)env->game.line_height;
	env->game.tex_pos = (env->game.start_y - env->win.height
			/ 2 + env->game.line_height / 2) * step;
	y = 0;
	while (y < env->game.start_y)
		env->win.canvas.pixels[y++][x].data = env->settings.ceilling.data;
	while (y < env->game.end_y)
	{
		env->game.tex.y = (int)env->game.tex_pos
			& (env->images[env->game.curr_tex].height - 1);
		env->game.tex_pos += step;
		env->win.canvas.pixels[y++][x] = env->images[env->game.curr_tex]
			.pixels[env->game.tex.y][env->game.tex.x];
	}
	while (y < env->win.height)
		env->win.canvas.pixels[y++][x].data = env->settings.floor.data;
}

int	ft_render_next_frame(t_env	*env)
{
	int	x;

	x = -1;
	if (env->game.keycode == KeyLeft || env->game.keycode == KeyRight)
		ft_action_rotate(env);
	else if (env->game.keycode == KeyUp || env->game.keycode == KeyDown)
		ft_action_move(env);
	while (++x < env->win.width)
	{
		env->game.camera_x = 2 * x / (double)env->win.width - 1;
		ft_set_point(&env->game.ray_dir, env->game.dir.x + env->game.plane.x
			* env->game.camera_x, env->game.dir.y + env->game.plane.y
			* env->game.camera_x);
		ft_set_point_int(&env->game.map, env->game.pos.x, env->game.pos.y);
		ft_algorithm_dda(&env->game, (const int *const *)env->settings.map);
		ft_calc_line(&env->game, &env->win);
		ft_select_texture(&env->game);
		ft_fill_canvas(env, x);
	}
	ft_draw_canvas(env);
	return (1);
}
