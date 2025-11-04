/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:07:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/04 16:53:24 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_player_values(void)
{
	if (pc()->button.left)
		pc()->player.angle -= pc()->player.rot_speed;
	if (pc()->button.right)
		pc()->player.angle += pc()->player.rot_speed;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
}

int		is_blocked(int map_y, int map_x)
{
	if (pc()->map[map_y][map_x] == '1')
		return (1);
	if (pc()->map[map_y][map_x]== 'd' && is_door_closed(map_y, map_x))
		return (1);
	return (0);
}

int		is_blocked_e(int map_y, int map_x)
{
	if (pc()->map[map_y][map_x] == '1')
		return (1);
	if (pc()->map[map_y][map_x]== 'd')
		return (1);
	return (0);
}

void	check_collision(float newx, float newy)
{
	float	check;

	check = 0.5 - pc()->player.move_speed;
	if (!is_blocked((int)(pc()->player.y), (int)(newx))
		&& !is_blocked((int)(pc()->player.y + check), (int)(newx))
		&& !is_blocked((int)(pc()->player.y), (int)(newx + check))
		&& !is_blocked((int)(pc()->player.y + check), (int)(newx + check)))
		pc()->player.x = newx;
	if (!is_blocked((int)(newy), (int)(pc()->player.x))
		&& !is_blocked((int)(newy + check), (int)(pc()->player.x))
		&& !is_blocked((int)(newy), (int)(pc()->player.x + check))
		&& !is_blocked((int)(newy + check), (int)(pc()->player.x + check)))
		pc()->player.y = newy;
}

void	move_player(void)
{
	float	newx;
	float	newy;

	calculate_player_values();
	newx = pc()->player.x;
	newy = pc()->player.y;
	if (pc()->button.w)
	{
		newx += pc()->player.dir_x * pc()->player.move_speed;
		newy += pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.s)
	{
		newx -= pc()->player.dir_x * pc()->player.move_speed;
		newy -= pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.a)
	{
		newx += pc()->player.dir_y * pc()->player.move_speed;
		newy -= pc()->player.dir_x * pc()->player.move_speed;
	}
	if (pc()->button.d)
	{
		newx -= pc()->player.dir_y * pc()->player.move_speed;
		newy += pc()->player.dir_x * pc()->player.move_speed;
	}
	check_collision(newx, newy);
}
