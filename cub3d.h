/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:07:57 by praders           #+#    #+#             */
/*   Updated: 2025/10/22 15:38:56 by mprazere         ###   ########.fr       */
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
    int map[6][6];
    int enemy_count;
    t_enemy *enemies;
    t_player player;
    t_image image;
	t_buttons button;
} t_game;

#endif