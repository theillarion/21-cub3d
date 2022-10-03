#ifndef CUB3D_HPP
# define CUB3D_HPP

# include "mlx.h"
# include "libft.h"

typedef struct s_window
{
	void	*mlx;
}	t_window;

typedef struct s_env
{
	t_window	win;
}	t_env;

//	main.c
int	main(void);

#endif