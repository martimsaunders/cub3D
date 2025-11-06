/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:27:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 18:29:35 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libraries/libft/libft.h"
# include "libraries/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/extensions/Xfixes.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MOUSE_HIDE 1
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 32
# define PI 3.14159265359
# define FOV 0.66

typedef enum e_mode
{
	MENU,
	CTRLS,
	LVLS,
	GAME_MENU,
	GAME,
	EVAL
}				t_mode;

typedef struct s_door
{
	int			x;
	int			y;
	int			state;
	float		distance;
}				t_door;

typedef struct s_sprite
{
	int			state;
	int			is_coin;
	int			direction;
	float		x;
	float		y;
	float		min_x;
	float		min_y;
	float		speed;
	float		distance;
}				t_sprite;

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
	int			mousex;
	int			mousey;
}				t_player;

typedef struct s_ray
{
	int			hit;
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

typedef struct s_menu
{
	int			bpp;
	int			floor;
	int			endian;
	int			ceiling;
	int			line_lenght;
	char		*addr;
	void		*image;
}				t_menu;

typedef struct s_image
{
	int			bpp;
	int			floor;
	int			endian;
	int			ceiling;
	int			line_lenght;
	char		*addr;
	void		*image;
	t_asset		coin[8];
	t_asset		door[2];
	t_asset		enemy;
	t_asset		wall_e;
	t_asset		wall_n;
	t_asset		wall_o;
	t_asset		wall_s;
	t_asset		menu[5];
	t_asset		game_m[3];
	t_asset		m_ctrls[2];
	t_asset		keys[2];
}				t_image;

typedef struct s_start
{
	t_player	player;
}				t_start;

typedef struct s_game
{
	int			argc;
	int			coin_count;
	int			coin_frame;
	int			door_count;
	int			enemy_count;
	int			mouse_in_win;
	int			coin_captured;
	int			coin_frame_counter;
	char		**map;
	char		**argv;
	void		*mlx;
	void		*win;
	t_door		*door;
	t_start		start;
	t_image		image;
	t_player	player;
	t_sprite	*coin;
	t_sprite	*enemies;
	t_buttons	button;
	t_mode		mode;
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
	int			p_count;
	int			ff_ret;
	int			ff_coin;
}				t_parse;

typedef struct s_map
{
	double		angle;
	double		world_x;
	double		world_y;
	double		frac_x;
	double		frac_y;
	double		rotx;
	double		roty;
	double		disx;
	double		disy;
	double		pxlx;
	double		pxly;
	int			mapdx;
	int			mapdy;
	int			mappx;
	int			mappy;
	int			mapx;
	int			mapy;
	int			relx;
	int			rely;
	int			map_radius;
}				t_map;

// cub_coins.c
int				find_coin_state(int x, int y);
void			check_coin_colision(void);

// cub_doors.c
int				find_door_index(int x, int y);
int				is_door_closed(int map_y, int map_x);
void			interact_door(void);
void			distance_door(t_door *door);

// cub_error.c
int				end_window(void);
void			free_array(void);
void			destroy_everything(int exit_status);

// cub_hook.c
int				draw_screen(void);
int				key_press(int keycode);
int				key_release(int keycode);
void			hook_and_loop(void);

// cub_move_enemy.c
int				iswall(float newx, float newy, t_sprite *enemy);
void			check_enemy_colision(void);
void			move_enemy(t_sprite *enemy);

// cub_init_everything.c
void			init_eval_images(void);
void			init_menu_images(void);
void			safe_image(char *str, t_asset *asset, t_image *image, int type);
void			init_images(void);
void			init_game(void);

// cub_move_player.c
int				is_blocked(int map_y, int map_x);
int				is_blocked_e(int map_y, int map_x);
void			move_player(void);
void			calculate_player_values(void);
void			check_collision(float newx, float newy);

// cub_draw_map.c
void			put_pixel(int x, int y, int color);

// cub_ray_cast_cf.c
int				put_brightness_cf(int color, float distance);
void			draw_ceiling_floor(t_ray ray, int x);

// cub_ray_cast_utils.c
void			find_steps(t_ray *ray);
void			check_wall(t_ray *ray);
void			draw_e_o_wall(t_ray *ray, t_tex *tex);
void			draw_n_s_wall(t_ray *ray, t_tex *tex);
void			put_brightness(t_ray *ray, t_tex *tex, t_rend *rend, int x);

// cub_ray_cast.c
void			ray_cast(void);
void			set_ray_values_hit(t_ray *ray, int x);
void			set_tex_values(t_ray *ray, t_tex *tex);
void			draw_line(t_ray *ray, t_tex *tex, int x);

// cub_sprite_rendering.c
int				set_rend_values(t_sprite *enemy, t_rend *rend);
void			sort_sprites(t_sprite **sprite, int size);
void			distance(t_sprite *enemy);
void			sprite_rendering(float *zbuffer, int size);
void			draw_sprite_columns(t_rend rend, t_tex tex, float *zbuffer,
					t_asset *sprite);

// cub3d.c
bool			avl_mode_init(int argc, char **argv);
void			init_eval_characters_values(void);
void			restart_level(void);
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
bool			characters_set_value(void);
bool			flood_fill_map(char **map, int x, int y);
char			**copy_matrix(char **src, int size);
bool			surounded_walls(void);

// map_parsing_utils.c
bool			coins_pos(void);
bool			check_door_pos(char chr, int x, int y);

// set_map.c
bool			fill_map(int fd, char *map_name);
bool			create_map(int fd, char *map_name);
bool			characters_count(char orientation);
bool			set_elements_values(char character, int x, int y);

// game_features
// mini_map.c
void			draw_mini_map(void);
void			draw_enemies(t_map *m);
void			draw_player(t_map *m);

// mouse_ctrl.c
int				mouse_move(int x, int y);
int				mouse_out(void);
int				mouse_click(int button, int x, int y);
void			mouse_cam_move(int x);
int				mouse_in(void);

// mouse_clicks.c
void			game_menu_click(int x, int y);
void			lvls_menu_click(int x, int y);
void			ctrls_menu_click(int x, int y);
void			main_menu_click(int x, int y);

// to organize

void			draw_game_menu(void);
void			draw_lvls_menu(void);
void			draw_ctrls_menu(void);
void			draw_main_menu(void);
void			draw_game_screen(void);
void			draw_eval_screen(void);

void			mouse_move_pause_menu(int x, int y);
void			mouse_move_lvls_menu(int x, int y);
void			mouse_move_ctrls_menu(int x, int y);
void			mouse_move_main_menu(int x, int y);

#endif