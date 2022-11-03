/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: illarion <glashli@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:14:13 by illarion          #+#    #+#             */
/*   Updated: 2022/10/28 18:43:38 by illarion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx_int.h"

bool	ft_create_mlx(t_mlx	*mlx)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (false);
	mlx_get_screen_size(mlx->ptr, &width, &height);
	if (width == 0 || height == 0)
		return (false);
	mlx->width = width;
	mlx->height = height;
	return (true);
}

bool	ft_create_window(const t_mlx *mlx, t_window	*win, char *name)
{
	int	i;

	if (!mlx || !win || win->width <= 0 || win->height <= 0)
		return (false);
	win->ptr = mlx_new_window(mlx->ptr, win->width, win->height, name);
	win->canvas.width = win->width;
	win->canvas.height = win->height;
	win->canvas.data.img = mlx_new_image(mlx->ptr, win->width, win->height);
	ft_set_data_image(&win->canvas.data);
	win->canvas.pixels = (t_srgb **)malloc((win->canvas.height + 1)
			* sizeof(*win->canvas.pixels));
	if (!win->ptr || !win->canvas.data.img || !win->canvas.data.addr
		|| !win->canvas.pixels)
		return (false);
	i = -1;
	while (++i < win->canvas.height)
	{
		win->canvas.pixels[i] = (t_srgb *)malloc(win->canvas.width
				* sizeof(**win->canvas.pixels));
		if (!win->canvas.pixels[i])
			return (false);
	}
	win->canvas.pixels[i] = NULL;
	return (true);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_uint	ft_get_pixel(char *data, int x, int opp, bool byte_order)
{
	(void)byte_order;
	return (*((unsigned int *)(data + opp * x)));
}

void	ft_set_color_pixels(t_image	*image)
{
	void		*data;
	int			i;
	int			j;

	image->pixels = (t_srgb **)malloc((image->height + 1)
			* sizeof(*image->pixels));
	if (!image->pixels)
		return ;
	data = image->data.addr;
	i = -1;
	while (++i < image->height)
	{
		image->pixels[i] = (t_srgb *)malloc(image->width
				* sizeof(**image->pixels));
		j = -1;
		while (++j < image->width)
		{
			ft_srgb_set_raw(&image->pixels[i][j],
				ft_get_pixel(data, j, image->data.bits_per_pixel / 8, 1));
		}
		data += image->data.line_length;
	}
	image->pixels[i] = NULL;
}
