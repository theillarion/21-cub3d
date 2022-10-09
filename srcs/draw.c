#include "cub3d.h"

static void	ft_draw_buffer(t_image	*image)
{
	int	x;
	int	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			ft_mlx_pixel_put(&image->data, x, y, image->pixels[y][x].data);
			++y;
		}
		++x;
	}
}

void	ft_draw_canvas(t_env	*env)
{
	int	x;
	int	y;

	ft_draw_buffer(&env->win.canvas);
	mlx_put_image_to_window(env->mlx.ptr, env->win.ptr,
		env->win.canvas.data.img, 0, 0);
	x = 0;
	while (x < env->win.canvas.width)
	{
		y = 0;
		while (y < env->win.canvas.height)
		{
			env->win.canvas.pixels[y][x].data = CLEAR_PIXEL;
			++y;
		}
		++x;
	}
}
