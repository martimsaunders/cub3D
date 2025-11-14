/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:07:37 by praders           #+#    #+#             */
/*   Updated: 2025/11/14 13:59:18 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libraries/libft/libft.h"
# include "libraries/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define BONUS 0
# define MOUSE_HIDE 0
# define WIDTH 1280
# define HEIGHT 720
# define MINIMAP 120
# define HUD 70
# define BLOCK 32
# define PI 3.14159265359
# define FOV 1

typedef enum e_mode
{
	MENU,
	CTRLS,
	LVLS,
	LVLS_GAME,
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
	int			mov;
	int			state;
	int			is_coin;
	int			direction;
	int			mov_count;
	int			number_mov;
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
	t_asset		train[12];
	t_asset		m_ctrls[2];
	t_asset		hud_bar;
	t_asset		hud_bitmap;
	t_asset		compass;
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
	int			death_count;
	int			door_count;
	int			enemy_count;
	int			mouse_in_win;
	int			coin_captured;
	int			current_level;
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
	int			c_col;
	int			c_hex;
	int			f_col;
	int			f_hex;
	int			map_idx;
	int			coin_check;
	int			coin_count;
	int			door_count;
	int			line_count;
	int			enemy_count;
	char		*e_path;
	char		*n_path;
	char		*s_path;
	char		*w_path;
	char		**map;
	char		**file;
	char		**map_cpy;
}				t_parse;

typedef struct s_minimap
{
	int			imgx;
	int			imgy;
	int			mapx;
	int			mapy;
	int			map_h;
	int			radius;
	int			char_size;
	int			coin_count;
	int			enemy_count;
	char		**map;
	double		rotx;
	double		roty;
	double		angle;
	double		worldx;
	double		worldy;
	t_asset		compass;
	t_player	player;
	t_sprite	*coins;
	t_sprite	*enemies;
}				t_minimap;

typedef struct s_hud
{
	int			lvl;
	int			imgx;
	int			imgy;
	int			coins;
	int			width;
	int			deaths;
	int			height;
	int			lvl_px;
	int			radius;
	int			coin_px;
	int			death_px;
	double		angle;
	t_mode		mode;
	t_asset		bitmap;
	t_asset		compass;
	t_asset		hud_bar;

}				t_hud;

// cub_check_wall.c
int				find_hit(t_ray *ray);
void			check_wall(t_ray *ray);

// cub_coins.c
int				find_coin_state(int x, int y);
void			check_coin_colision(void);

// cub_doors.c
int				find_door_index(int x, int y);
int				is_door_closed(int map_y, int map_x);
void			interact_door(void);
void			distance_door(t_door *door);

// cub_draw_levels.c
void			draw_lvls_menu(void);

// cub_draw_screen.c
void			draw_game_menu(void);
void			draw_main_menu(void);
void			draw_ctrls_menu(void);
void			draw_game_screen(void);

// cub_error.c
int				end_window(void);
void			free_array(void);
void			destroy_everything(int exit_status);
void			safe_destroy(void **img, void **ptr);
void			destroy_asset(t_asset *asset, int size);

// cub_hook.c
int				is_mode(void);
int				draw_screen(void);
int				key_press(int keycode);
int				key_release(int keycode);
void			hook_and_loop(void);

// cub_move_enemy.c
int				iswall(float newx, float newy, t_sprite *enemy);
void			check_enemy_colision(void);
void			move_enemy(t_sprite *enemy);

// cub_init_everything.c
void			init_game(void);
void			init_images(void);
void			init_eval_images(void);
void			init_menu_images(void);
void			safe_image(char *str, t_asset *asset, t_image *image, int type);

// cub_move_player.c
int				is_blocked(int map_y, int map_x);
int				is_blocked_e(int map_y, int map_x, int type);
void			move_player(void);
void			check_collision(float newx, float newy);
void			calculate_player_values(float *newx, float *newy);

// cub_draw_map.c
void			put_pixel(int x, int y, int color);

// cub_ray_cast_cf.c
int				put_brightness_cf(int color, float distance);
int				get_floor_color(int mapx, int mapy, float distance, t_ray ray);
void			draw_ceiling_floor(t_ray ray, int x);

// cub_ray_cast_utils.c
void			find_steps(t_ray *ray);
void			draw_e_o_wall(t_ray *ray, t_tex *tex);
void			draw_n_s_wall(t_ray *ray, t_tex *tex);
void			put_brightness(t_ray *ray, t_tex *tex, t_rend *rend, int x);

// cub_ray_cast.c
void			ray_cast(void);
void			set_ray_values_hit(t_ray *ray, int x);
void			set_tex_values(t_ray *ray, t_tex *tex);
void			draw_line(t_ray *ray, t_tex *tex, int x);

// cub_sprite_rendering_utils.c
void			distance(t_sprite *enemy);
void			set_rend_values2(t_rend *rend);

// cub_sprite_rendering.c
int				set_rend_values(t_sprite *sprite, t_rend *rend);
void			sort_sprites(t_sprite **sprite, int size);
void			sprite_rendering(float *zbuffer, int size, int i);
void			draw_sprite_columns(t_rend rend, t_tex tex, float *zbuffer,
					t_asset *sprite);

// cub3d.c
t_game			*pc(void);

// parsing
// parse_file.c
bool			parse_file_fill(t_parse *f, const char *filepath);
bool			parse_file_load(t_parse *f, const char *filepath);
void			parse_file_destroy(t_parse *f, int error);

// parse_flood_fill.c
bool			parse_validate_map(t_parse *f);
bool			parse_validate_coins_pos(t_parse *f);
bool			parse_map_flood_fill(t_parse *f, int x, int y);
bool			parse_coin_flood_fill(t_parse *f, int x, int y);

// parse_header_utils
bool			parse_get_color(char *line, t_parse *f);
bool			parse_get_texture(char *line, t_parse *f);
bool			parse_check_texture(char *line, char **dst);
bool			parse_check_color(char *line, int *id, int *dst);
bool			parse_check_numbers(char **nums, int *id, int *dst);

// parse_header.c
bool			parse_header(t_parse *f);
bool			parse_check_all_infos(t_parse *f);

// parse_map_matrix.c
int				parse_map_height(char **map);
bool			parse_map_matrix(t_parse *f);
bool			parse_find_player(t_parse *f, int *px, int *py);
char			**parse_copy_matrix(char **src);
void			parse_free_array(char **arr);

// parse_map_utils.c
bool			parse_is_player(char c);
bool			parse_is_icon(char c);
bool			parse_is_map(char c);
bool			parse_out_of_bounds(char **map, int x, int y);

// parse_set_values.c
bool			parse_set_coins(t_parse *f);
bool			parse_set_doors(t_parse *f);
bool			parse_set_enemies(t_parse *f);
bool			parse_set_icons_values(t_parse *f);
void			parse_set_player(t_parse *f);

// parsing_utils.c
bool			parse_is_empty_line(const char *line);
bool			parse_is_space(char c);
bool			parse_is_map_line(const char *line);
bool			parse_is_texture(const char *line);
bool			parse_is_color(const char *line);

// parsing.c
char			parse_get_char(char *line);
void			parse_init_f(t_parse *f);
void			err_msg(char *msg, char var);
void			parse_map_file(const char *filepath);

// game_features
// lvls
// cub_initiate_lvl.c
bool			avl_mode_init(int argc, char **argv);
void			restart_level(void);
void			free_game_values(void);
void			init_eval_characters_values(void);

// cub_lev_1a5.c
void			set_lvl_1(void);
void			set_lvl_2(void);
void			set_lvl_3(void);
void			set_lvl_4(void);
void			set_lvl_5(void);

// cub_lev_6a10.c
void			set_lvl_6(void);
void			set_lvl_7(void);
void			set_lvl_8(void);
void			set_lvl_9(void);
void			set_lvl_10(void);

// cub_lvls_set_values.c
bool			characters_count(char chr);
bool			set_coin_value(int x, int y);
bool			set_door_value(int x, int y);
bool			set_enemy_value(int x, int y);
bool			set_elements_values(char c, int x, int y);

// cub_lvls_utils.c
int				is_player(int y, int x);
void			find_player(void);
void			init_player(void);
void			init_lvl_images(void);
void			fill_values(int x, int y);

// cub_lvls.c
char			**file_matrix_load(const char *filepath);
char			**file_matrix_fill(const char *filepath, char **matrix);
void			choose_level(void);
void			lvl_mode_init(void);

// minimap
// minimap_compass.c
void			minimap_draw_compass(t_minimap *mm);
// minimap_draws.c
void			minimap_draw_block(t_minimap *mm, int x, int y);
void			minimap_draw_floor(t_minimap *mm, int x, int y);
void			minimap_draw_outside(t_minimap *mm, int x, int y);

// minimap_icons.c
void			minimap_draw_player(t_minimap *mm);
void			minimap_draw_all_icons(t_minimap *mm);
void			minimap_draw_icon(t_minimap *mm, int color);
void			minimap_icon_coords(t_minimap *mm, t_sprite icon);

// minimap_utils.c
bool			minimap_is_map(t_minimap *mm);
bool			minimap_is_safe(t_minimap *mm);
bool			minimap_is_inside_map(t_minimap *mm);
bool			minimap_is_wall(t_minimap *mm, int x, int y);
bool			minimap_is_edge(int mapx, int mapy, t_minimap *mm);

// minimap.c
bool			minimap_is_inside_circle(int x, int y, int radius);
void			draw_minimap(void);
void			minimap_init(t_minimap *mm);
void			minimap_world_coords(t_minimap *mm, int x, int y);
void			minimap_put_pixel(t_minimap *mm, int x, int y, int color);

// mouse
// mouse_move.c
int				mouse_move(int x, int y);
void			mouse_cam_move(int x);

// mouse_clicks.c
int				mouse_click(int button, int x, int y);
void			game_menu_click(int x, int y);
void			ctrls_menu_click(int x, int y);
void			main_menu_click(int x, int y);

// mouse_click_lvls.c
void			lvls_menu_click(int x, int y);

// hud
// bitmap.c
void			draw_hud(void);
void			hud_init(t_hud *h);
void			hud_draw_background(t_hud *h);
unsigned int	hud_get_pixel_color(t_asset asset, int x, int y);

// bitmap_utils.c
int				hud_find_index(char c);
void			hud_draw_char(t_hud *h, char c, int px);
void			hud_draw_number(t_hud *h, int num, int px);

#endif