/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:56:18 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/03 16:51:53 by mateferr         ###   ########.fr       */
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
# define FOV 0.66
# define BONUS_CHAR_LIMIT 10

typedef struct s_enemy
{
	int			direction;
	float		x;
	float		y;
	float		min_x;
	float		min_y;
	float		speed;
	float		distance;
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

typedef struct s_rend
{
	int			draw_end_x;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_start_y;
	int			sprite_width;
	int			sprite_height;
	int			sprite_screen_x;
	float		spritex;
	float		spritey;
	float		invdet;
	float		transform_x;
	float		transform_y;
}				t_rend;

typedef struct s_tex
{
	int			x;
	int			y;
	int			texx;
	int			texy;
	int			color;
	int			index;
	int			sprite_y_pos;
	float		step;
	float		wallx;
	float		texpos;
	float		brightness;
}				t_tex;

typedef struct s_asset
{
	char		*path;
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
	t_asset		enemy;
	t_asset		wall_e;
	t_asset		wall_n;
	t_asset		wall_o;
	t_asset		wall_s;
}				t_image;

typedef struct s_start
{
	t_enemy		enemies[BONUS_CHAR_LIMIT];
	t_player	player;
}				t_start;

typedef struct s_game
{
	int			enemy_count;
	char		**map;
	void		*mlx;
	void		*win;
	t_enemy		enemies[BONUS_CHAR_LIMIT];
	t_image		image;
	t_player	player;
	t_buttons	button;
	t_start		start;
}				t_game;

typedef struct s_parse
{
	int			n_tex;
	int			s_tex;
	int			e_tex;
	int			o_tex;
	int			c_floor;
	int			c_ceil;
	int			map_h;
	int			x;
	int			y;
	int			map_start_in_fd;
	int			bonus;
}				t_parse;

typedef struct s_mmap
{
	double		angle;
	double		world_x;
	double		world_y;
	double		frac_x;
	double		frac_y;
	double		rotx;
	double		roty;
	int			mapx;
	int			mapy;
	int			relx;
	int			rely;
	int			map_radius;
}				t_mmap;

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

// cub_move_enemy.c
int				iswall(float newx, float newy, t_enemy *enemy);
void			check_enemy_colision(void);
void			move_enemy(t_enemy *enemy);

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
void			put_brightness(t_ray *ray, t_tex *tex, t_rend *rend, int x);

// cub_ray_cast.c
void			ray_cast(void);
void			set_ray_values_hit(t_ray *ray, int x);
void			set_tex_values(t_ray *ray, t_tex *tex);
void			draw_line(t_ray *ray, t_tex *tex, int x);
void			setup_wall_texture(t_ray *ray, t_tex *tex);

// cub_sprite_rendering.c
int				set_rend_values(t_enemy *enemy, t_rend *rend);
void			sort_enemies(void);
void			distance(t_enemy *enemy);
void			sprite_rendering(float zbuffer[WIDTH]);
void			draw_sprite_columns(t_rend rend, t_tex tex,
					float zbuffer[WIDTH]);

// cub3d.c
void			restart_level(void);
void			init_caracters_values(void);
t_game			*pc(void);

// parsing
// file_parsing.c
bool			map_file_parsing(char *map_name);
void			err_msg(char *msg, char var);
void			free_cpy(char **array);
t_parse			*ps(void);

// info_parse_utils.c
int				get_hex_num(char *line, int *dst, int *info);
bool			valid_color_nums(int i, char **nums, int rgb[3]);
int				get_tex_path(char *line, char **dst, int *info);

// info_parsing.c
int				find_tex_info(char *line);
int				find_map_info(char *line);
bool			check_missing_infos(void);
bool			valid_map_info(int fd, char *map_name);

// map_parsing.c
bool			valid_map_characters(void);
bool			characters_check(void);
bool			flood_fill_map(char **map, int x, int y);
char			**copy_matrix(char **src, int size);
bool			surounded_walls(void);

// set_map.c
bool			fill_map(int fd, char *map_name);
bool			create_map(int fd, char *map_name);
bool			set_characters_values(char orientation, int x, int y);
void			set_start_values(void);

// game_features
// mini_map.c
void			draw_mini_map(void);

#endif