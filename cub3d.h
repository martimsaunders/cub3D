/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:07:57 by praders           #+#    #+#             */
/*   Updated: 2025/10/29 17:59:21 by mprazere         ###   ########.fr       */
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

typedef struct s_enemy
{
	float		x;
	float		y;
	float		min_x;
	float		min_y;
	float		speed;
	int			direction;
}				t_enemy;

typedef struct s_buttons
{
	bool		A;
	bool		W;
	bool		S;
	bool		D;
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
	float		camerax;
	float		pctrx;
	float		pctry;
	int			mapx;
	int			mapy;
	float		raydirx;
	float		raydiry;
	float		ddistx;
	float		ddisty;
	int			stepx;
	int			stepy;
	float		sdistx;
	float		sdisty;
	float		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			side;
}				t_ray;

typedef struct s_tex
{
	float		wallx;
	int			texx;
	int			texy;
	float		step;
	float		texpos;
	int			index;
	int			color;
	float		brightness;
	int			darker_color;
}				t_tex;

typedef struct s_asset
{
	void		*image;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_lenght;
	int			endian;
}				t_asset;

typedef struct s_image
{
	void		*image;
	char		*addr;
	int			bpp;
	int			line_lenght;
	int			endian;
	t_asset		wall_n;
	t_asset		wall_s;
	t_asset		wall_e;
	t_asset		wall_o;
}				t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			enemy_count;
	t_enemy		*enemies;
	t_player	player;
	t_image		image;
	t_buttons	button;
}				t_game;

void			put_pixel(int x, int y, int color);
t_game			*pc(void);
int				key_press(int keycode);
int				key_release(int keycode);
int				end_window(void);
void			init_player_map(void);
void			draw_square(int x, int y, int size, int color);
void			move_player(void);
void			draw_map(void);
void			draw_checkered_square(int x, int y, int size, int color1,
					int color2);
void			draw_player_square(int pixel_x, int pixel_y, int size,
					int color);
void			find_player(void);
void			ray_cast(void);
int				draw_move(void);
void			init_images(void);
void			destroy_everything(int exit_status);
void			init_game(void);
void			hook_and_loop(void);
void			calculate_player_values(void);
void			check_collision(float newx, float newy);
void			set_ray_values_hit(t_ray *ray, int x);
void			check_wall(t_ray *ray, int hit);
void			set_tex_values(t_ray *ray, t_tex *tex);
void			put_brightness(t_ray *ray, t_tex *tex, int x);
void			draw_e_o_wall(t_ray *ray, t_tex *tex);
void			draw_n_s_wall(t_ray *ray, t_tex *tex);
void			draw_line(t_ray *ray, t_tex *tex, int x);
void			free_array(void);
void			find_steps(t_ray *ray);

#endif