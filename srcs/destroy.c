#include "cub3d.h"

#ifdef CURRENT_OS_LINUX

void	ft_destroy_display(void	**ptr)
{
	mlx_destroy_display(*ptr);
	*ptr = NULL;
}
#else

void	ft_destroy_display(void	**ptr)
{
	(void)ptr;
}
#endif

void ft_smart_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void ft_destroy_pixels(t_image	*image)
{
	int	i;

	if (!image || !image->pixels)
		return ;
	i = 0;
	while (i < image->height)
		ft_smart_free((void **)&image->pixels[i++]);
	ft_smart_free((void **)&image->pixels);
}

void	ft_destroy_images(t_env	*env)
{
	int	i;

	if (!env || !env->images)
		return ;
	i = 0;
	while (i < COUNT_TEXTURES)
	{
		mlx_destroy_image(env->mlx.ptr, env->images[i].data.img);
		ft_destroy_pixels(&env->images[i]);
		++i;
	}
}

void	ft_destroy(t_env	*env)
{
	if (!env || !env->mlx.ptr)
		return;
	ft_destroy_images(env);
	ft_destroy_pixels(&env->win.canvas);
	if (env->win.canvas.data.img)
		mlx_destroy_image(env->mlx.ptr, env->win.canvas.data.img);
	if (env->win.ptr)
		mlx_destroy_window(env->mlx.ptr, env->win.ptr);
	ft_destroy_display(&env->mlx.ptr);
}