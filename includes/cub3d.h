#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include "keys.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

//	temp
# include <stdio.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define COUNT_TEXTURES 4

# define CLEAR_PIXEL 0x0

# define EPSILON 1e-15

# define DEFAULT_DIR_X -1
# define DEFAULT_DIR_Y 0

# define DEFAULT_PLANE_X 0.f
# define DEFAULT_PLANE_Y 0.66f

# define SPEED_ROTATE M_PI / 20
# define SPEED_MOVE 0.5f
# define NORTH 0
# define SOUTH M_PI
# define WEST (M_PI / 2)
# define EAST -WEST
# define BUFFER_SIZE 1024

enum e_textures
{
	TEX_NORTH,
	TEX_EAST,
	TEX_SOUTH,
	TEX_WEST
};

typedef struct s_color_srgb
{
	int		data;
}	t_srgb;

typedef struct s_pixels
{
	int		width;
	int		height;
}	t_pixels;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_image
{
	int			width;
	int			height;
	t_data		data;
	t_srgb		**pixels;
}	t_image;

typedef struct s_mlx
{
	void	*ptr;
	int		width;
	int		height;
}		t_mlx;
typedef struct s_window
{
	void		*ptr;
	char		*name;
	t_image		canvas;
	int			width;
	int			height;
}	t_window;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_point_int
{
	int	x;
	int	y;
}	t_point_int;

typedef struct s_game
{
	t_point		pos;
	t_point		dir;
	t_point		ray_dir;
	t_point		plane;
	t_point_int	step;
	t_point_int	map;
	t_point_int	tex;
	double		frame_time;
	double		camera_x;
	double		perp_wall_dist;
	double		tex_pos;
	bool		side;
	int			keycode;
	int			curr_tex;
	int			line_height;
	int			start_y;
	int			end_y;
}	t_game;

typedef struct s_settings
{
	double	speed_rotate;
	double	speed_move;
	t_point	position;
	double	direction;
	t_srgb	floor;
	t_srgb	ceilling;
	char	*paths[COUNT_TEXTURES];
	int		**map;
	int		map_height;
	int		map_width;
}	t_setting;

typedef struct s_env
{
	t_mlx		mlx;
	t_window	win;
	t_image		images[COUNT_TEXTURES];
	t_game		game;
	t_setting	settings;
}	t_env;

//		action.c
void	ft_rotate(t_point *dir, t_point *plane, double speed);
void	ft_action_rotate(t_env *env);
void	ft_action_move(t_env *env);

//		draw.c
void	ft_draw_canvas(t_env	*env);

//		events.c
int		ft_event_key_press(int keycode, t_env	*env);
int		ft_event_key_release(int keycode, t_env	*env);

//		exit.c
int		ft_success(t_env	*env);

//		fill.c
bool	ft_fill(t_env	*env);

//		image_utilities.c
void	ft_set_data_image(t_data	*data);

//		init.c
bool	ft_init(t_env *env);

//		main.c
int		main(int argc, char	**argv);

//		mlx_utilities.c
bool	ft_create_mlx(t_mlx	*mlx);
bool	ft_create_window(const t_mlx *mlx, t_window	*win, char *name);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_get_pixel(char *data, int x, int opp, bool byte_order);
void	ft_set_color_pixels(void *ptr, t_image	*image);

//		point_utilities.c
void	ft_set_point(t_point *point, double x, double y);
void	ft_set_point_int(t_point_int *point, int x, int y);

//		render_utilities.c
void	ft_algorithm_dda(t_game *game, const int *const *map);

//		render.c
int		ft_render_next_frame(t_env	*env);

//		srgb_utilities.c
t_srgb	ft_srgb_create(int s, int r, int g, int b);
t_srgb	ft_srgb_create_raw(int raw_color);
void	ft_srgb_set_raw(t_srgb *color, int bits);

char	*get_next_line(int fd);

void	read_scene(char *map_path, t_setting *g);

int		ft_isspace(int c);
int		skip_ws(char **str);
void	go_to_sym(const char *string, int *skip, char s);
int		handle_quotes(char **string, int *len);

char	*ft_strjoin_with_free(char *str1, char *str2, int free_1, int free_2);
int		**allocate_map(const t_setting *g);

void	map_is_closed(t_setting *g, int *const *m);

int		ft_raise_error(char *str);
void	map_error(void);

int		set_path(char **path, char *string);
int		set_rgb(t_srgb *srgb, char *string_of_map);

int		fill_params(t_setting *g, char *str_of_map);
void	check_all_params_filled(t_setting *g, int *params_filled);

int		calc_map_width_height(t_setting *g, char *mapline);
void	fill_map(t_setting *g, char *ml, int **map);

void	initiate_color_params(char **tmp, char **c, int *len);
void	free_colors(char *const *c);

#endif