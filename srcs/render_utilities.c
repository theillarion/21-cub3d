#include "cub3d.h"

//extern int env[MAP_WIDTH][MAP_HEIGHT];

static void	ft_algorithm_dda_preparation(t_game *game, t_point *side_dist,
				t_point	*delta_dist)
{
	delta_dist->x = fabs(1.f / game->ray_dir.x);
	delta_dist->y = fabs(1.f / game->ray_dir.y);
	if (game->ray_dir.x < 0)
	{
		game->step.x = -1;
		side_dist->x = (game->pos.x - game->map.x) * delta_dist->x;
	}
	else
	{
		game->step.x = 1;
		side_dist->x = (game->map.x + 1.0 - game->pos.x) * delta_dist->x;
	}
	if (game->ray_dir.y < 0)
	{
		game->step.y = -1;
		side_dist->y = (game->pos.y - game->map.y) * delta_dist->y;
	}
	else
	{
		game->step.y = 1;
		side_dist->y = (game->map.y + 1.0 - game->pos.y) * delta_dist->y;
	}
}

void	ft_algorithm_dda(t_game *game, const int *const *map)
{
	t_point	side_dist;
	t_point	delta_dist;

	ft_algorithm_dda_preparation(game, &side_dist, &delta_dist);
	while (true)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist.x;
			game->map.x += game->step.x;
			game->side = false;
		}
		else
		{
			side_dist.y += delta_dist.y;
			game->map.y += game->step.y;
			game->side = true;
		}
		if (map[game->map.x][game->map.y])
			break ;
	}	
	if (game->side == 0)
		game->perp_wall_dist = (side_dist.x - delta_dist.x);
	else
		game->perp_wall_dist = (side_dist.y - delta_dist.y);
}
