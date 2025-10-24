/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:07:57 by praders           #+#    #+#             */
/*   Updated: 2025/10/24 15:41:28 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include "libraries/minilibx-linux/mlx.h"
#include "libraries/libft/libft.h"
#include <stdbool.h>

#define WIDTH 1280
#define HEIGHT 720
#define BLOCK 32
#define PI 3.14159265359

typedef struct s_enemy
{
    float x;
    float y;
    float min_x;
    float min_y;
    float speed;
    int direction;
}   t_enemy;

typedef struct s_buttons
{
	bool A;
	bool W;
	bool S;
	bool D;
    bool left;
    bool right;
}	t_buttons;

typedef struct s_player
{
    float x;
    float y;
    float dir_x;
    float dir_y;
    float plane_x;
    float plane_y;
    float move_speed;
    float rot_speed;
    float angle;
}   t_player;

typedef  struct s_image
{
    void *image;
    char *addr;
    int bpp;
    int line_lenght;
    int endian;
} t_image;

typedef struct s_game
{
    void *mlx;
    void *win;
    char **map;
    int enemy_count;
    t_enemy *enemies;
    t_player player;
    t_image image;
	t_buttons button;
} t_game;

void	put_pixel(int x, int y, int color);
t_game *pc();
int key_press(int keycode);
int key_release(int keycode);
int end_window();
void init_player_map();
void clear_image();
void draw_square(int x, int y, int size, int color);
void move_player();
void draw_map();
void draw_checkered_square(int x, int y, int size, int color1, int color2);
void draw_player_square(int pixel_x, int pixel_y, int size, int color);
void find_player();
void ray_cast();
void draw_line(int x1, int y1, int color);


#endif