/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:35:23 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/30 11:38:02 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libraries/libft/libft.h"
# include "libraries/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 32
# define PI 3.14159265359
# define FOV 1
# define MAP_RADIUS 720 / 6

typedef struct s_enemy
{
	int			direction;
	float		x;
	float		y;
	float		min_x;
	float		min_y;
	float		speed;
}				t_enemy;

typedef struct s_buttons
{
	bool		a;
	bool		d;
	bool		s;
	bool		w;
	bool		left;
	bool		right;
}				t_buttons;

typedef struct s_player
{
	float		x;
	float		y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		move_speed;
	float		rot_speed;
	float		angle;
}				t_player;

typedef struct s_ray
{
	int			mapx;
	int			mapy;
	int			side;
	int			stepx;
	int			stepy;
	int			drawend;
	int			drawstart;
	int			lineheight;
	float		pctrx;
	float		pctry;
	float		ddistx;
	float		ddisty;
	float		sdistx;
	float		sdisty;
	float		raydirx;
	float		raydiry;
	float		camerax;
	float		perpwalldist;
}				t_ray;

typedef struct s_tex
{
	int			texx;
	int			texy;
	int			color;
	int			index;
	int			darker_color;
	float		step;
	float		wallx;
	float		texpos;
	float		brightness;
}				t_tex;

typedef struct s_asset
{
	char *path;
	int			bpp;
	int			width;
	int			endian;
	int			height;
	int			line_lenght;
	char		*addr;
	void		*image;
}				t_asset;

typedef struct s_image
{
	int			bpp;
	int			floor;
	int			endian;
	int			ceiling;
	int			line_lenght;
	char		*addr;
	void		*image;
	t_asset		wall_e;
	t_asset		wall_n;
	t_asset		wall_o;
	t_asset		wall_s;
}				t_image;

typedef struct s_game
{
	int			enemy_count;
	char		**map;
	void		*mlx;
	void		*win;
	t_enemy		*enemies;
	t_image		image;
	t_player	player;
	t_buttons	button;
}				t_game;

typedef struct s_parse
{
	int n_tex;
	int s_tex;
	int e_tex;
	int o_tex;
	int c_floor;
	int c_ceil;
	int map_h;
	int x;
	int y;
	int map_start_in_fd;
} t_parse;

// cub_draw_map.c
void			draw_map(void);
void			put_pixel(int x, int y, int color);
void			draw_square(int x, int y, int size, int color);
void			draw_player_square(int pixel_x, int pixel_y, int size,
					int color);
void			draw_checkered_square(int x, int y, int size, int color1,
					int color2);

// cub_error.c
int				end_window(void);
void			free_array(void);
void			destroy_everything(int exit_status);

// cub_hook.c
int				draw_move(void);
int				key_press(int keycode);
int				key_release(int keycode);
void			hook_and_loop(void);

// cub_init_everything.c
void			safe_image(char *str, t_asset *asset, t_image *image, int type);
void			safe_address(t_asset *asset, t_image *image, int type);
void			init_images(void);
void			init_game(void);

// cub_move_player.c
void			move_player(void);
void			calculate_player_values(void);
void			check_collision(float newx, float newy);

// cub_ray_cast_cf.c
int				put_brightness_cf(int color, float distance);
void			draw_ceiling_floor(t_ray ray, int x);

// cub_ray_cast_utils.c
void			find_steps(t_ray *ray);
void			check_wall(t_ray *ray, int hit);
void			draw_e_o_wall(t_ray *ray, t_tex *tex);
void			draw_n_s_wall(t_ray *ray, t_tex *tex);
void			put_brightness_wall(t_ray *ray, t_tex *tex, int x);

// cub_ray_cast.c
void			ray_cast(void);
void			set_ray_values_hit(t_ray *ray, int x);
void			set_tex_values(t_ray *ray, t_tex *tex);
void			draw_line(t_ray *ray, t_tex *tex, int x);

// cub3d.c
void			init_player_values(void);
t_game			*pc(void);

//parsing
//file_parsing.c
bool	map_file_parsing(char *map_name);
void	err_msg(char *msg, char *var);
void	free_cpy(char **array);
t_parse	*ps(void);

//info_parse_utils.c
int	get_hex_num(char *line, int *dst, int *info);
bool	valid_color_nums(int i, char **nums, int rgb[3]);
int	get_tex_path(char *line, char **dst, int *info);

//info_parsing.c
int find_tex_info(char *line);
int	find_map_info(char *line);
bool	check_missing_infos(void);
bool	valid_map_info(int fd, char *map_name);

//map_parsing.c
bool	valid_map_characters(void);
bool	player_check(void);
bool	flood_fill_map(char **map, int x, int y);
char	**copy_matrix(char **src, int size);
bool	surounded_walls(void);

//set_map.c
bool	fill_map(int fd, char *map_name);
bool	create_map(int fd, char *map_name);
void	player_set(char orientation, int x, int y);

//game_features
//mini_map.c
void draw_mini_map();

#endif