/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:28:19 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 16:13:40 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mouse_move(int x, int y)
{
	if (pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME)
		mouse_cam_move(x);
	else
	{
		pc()->player.mousex = x;
		pc()->player.mousey = y;
	}
	return (0);
}

static bool mouse_cam_init()
{
	if (!pc()->mouse_in_win)
	{
		if (MOUSE_HIDE != 0)
			mlx_mouse_hide(pc()->mlx, pc()->win);
		mlx_mouse_move(pc()->mlx, pc()->win, WIDTH / 2, HEIGHT / 2);
		pc()->mouse_in_win = 1;
		return (true);
	}
	return (false);
}

static void mouse_cam_values_set(int dx, float sens)
{
	pc()->player.angle += dx * sens;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
}

void	mouse_cam_move(int x)
{
	int		dx;
	float	sens;

	sens = 0.0005;
	if (mouse_cam_init())
		return ;
	dx = x - WIDTH / 2;
	mlx_mouse_move(pc()->mlx, pc()->win, WIDTH / 2, HEIGHT / 2);
	if (dx == 0)
		return ;
	mouse_cam_values_set(dx, sens);
}

