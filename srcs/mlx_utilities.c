#include "cub3d.h"

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
	int i;

	if (!mlx || !win || win->width <= 0 || win->height <= 0)
		return (false);
	win->ptr = mlx_new_window(mlx->ptr, win->width, win->height, name);
	win->canvas.width = win->width;
	win->canvas.height = win->height;
	win->canvas.data.img = mlx_new_image(mlx->ptr, win->width, win->height);
	ft_set_data_image(&win->canvas.data);
	win->canvas.pixels = (t_srgb **)malloc(win->canvas.height
		* sizeof(*win->canvas.pixels));
	if (!win->ptr || !win->canvas.data.img || !win->canvas.data.addr
		|| !win->canvas.pixels)
		return (false);
	i = -1;
	while (++i < win->canvas.height)
	{
		win->canvas.pixels[i] = (t_srgb *)malloc(win->canvas.width * sizeof(**win->canvas.pixels));
		if (!win->canvas.pixels[i])
			return (false);
	}
	return (true);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_get_pixel(char *data, int x, int opp, bool byte_order)
{
	int	result;
	int	dec;

	result = 0;
	dec = opp;
	while (dec--)
	{
		if (byte_order)
			result |= ((((int)*(data + x * opp + dec)) & 0xFF)
				<<  (dec * 8));
		else
			result |= ((((int)*(data + x * opp + opp - dec - 1)) & 0xFF)
				<<  (opp - dec - 1) * 8);
	}
	return (result);
}

void	ft_set_color_pixels(void *ptr, t_image	*image)
{
	t_img		img;
	void		*data;
	int			i;
	int			j;

	img = *(t_img *)ptr;
	data = img.data;
	image->pixels = (t_srgb **)malloc(img.height * sizeof(*image->pixels));
	image->width = img.width;
	image->height = img.height;
	i = 0;
	while (i < img.height)
	{
		j = 0;
		image->pixels[i] = (t_srgb *)malloc(img.width
				* sizeof(**image->pixels));
		while (j < img.width)
		{
			ft_srgb_set_raw(&image->pixels[i][j],
				ft_get_pixel(data, j, img.bpp / 8, img.image->byte_order));
			++j;
		}
		data += img.size_line;
		++i;
	}
}
