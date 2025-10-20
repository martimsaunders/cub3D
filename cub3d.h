/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:07:57 by praders           #+#    #+#             */
/*   Updated: 2025/10/20 13:27:20 by praders          ###   ########.fr       */
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

#define LENGHT 1280
#define WIDTH 720

typedef struct s_map
{
    void    *mlx;
    void    *win;
    int     x;
    int     y;
}   t_map;

#endif