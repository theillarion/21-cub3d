#include "cub3d.h"

void	ft_set_data_image(t_data	*data)
{
	if (data && data->img)
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}
